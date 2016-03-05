/*
 * Copyright (c) 2015 Pavel Vainerman.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 2.1.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
// -------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <cc++/socket.h>
#include "modbus/ModbusTCPSession.h"
#include "modbus/ModbusTCPCore.h"
#include "UniSetTypes.h"
// glibc..
#include <netinet/tcp.h>
// -------------------------------------------------------------------------
using namespace std;
using namespace ModbusRTU;
using namespace UniSetTypes;
// -------------------------------------------------------------------------
ModbusTCPSession::~ModbusTCPSession()
{
	cancelled = true;

	if( isRunning() )
		ost::Thread::join();
}
// -------------------------------------------------------------------------
ModbusTCPSession::ModbusTCPSession(ost::TCPSocket& server, const std::unordered_set<ModbusAddr>& a, timeout_t timeout ):
	TCPSession(server),
	vaddr(a),
	timeout(timeout),
	peername(""),
	caddr(""),
	cancelled(false),
	askCount(0)
{
	setCRCNoCheckit(true);

	timeout_t tout = timeout / 1000;

	if( tout <= 0 )
		tout = 3;

	setKeepAlive(true);
	setLinger(true);
	setKeepAliveParams(tout);
}
// -------------------------------------------------------------------------
unsigned int ModbusTCPSession::getAskCount()
{
	uniset_rwmutex_rlock l(mAsk);
	return askCount;
}
// -------------------------------------------------------------------------
void ModbusTCPSession::setKeepAliveParams( timeout_t timeout_sec, int keepcnt, int keepintvl )
{
	SOCKET fd = TCPSession::so;
	int enable = 1;
	(void)setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void*)&enable, sizeof(enable));
	(void)setsockopt(fd, SOL_TCP, TCP_KEEPCNT, (void*) &keepcnt, sizeof(keepcnt));
	(void)setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, (void*) &keepintvl, sizeof (keepintvl));
	(void)setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, (void*) &timeout_sec, sizeof (timeout_sec));
}
// -------------------------------------------------------------------------
void ModbusTCPSession::run()
{
	if( cancelled )
		return;

	{
		ost::tpport_t p;
		ost::InetAddress iaddr = getIPV4Peer(&p);

		// resolve..
		caddr = string( iaddr.getHostname() );

		ostringstream s;
		s << iaddr << ":" << p;
		peername = s.str();

		//      struct in_addr a = iaddr.getAddress();
		//      cerr << "**************** CREATE SESS FOR " << string( inet_ntoa(a) ) << endl;
	}

	if( dlog->is_info() )
		dlog->info() << peername << "(run): run thread of sessions.." << endl;

	ModbusRTU::mbErrCode res = erTimeOut;
	cancelled = false;

	char pbuf[3];

	while( !cancelled && isPending(Socket::pendingInput, timeout) )
	{
		ssize_t n = peek( pbuf, sizeof(pbuf) );

		// кажется сервер закрыл канал
		if( n == 0 )
			break;

		res = receive(vaddr, timeout);

		if( res == erSessionClosed )
			break;

		/*        if( res == erBadReplyNodeAddress )
		            break;*/

		if( res != erTimeOut )
		{
			uniset_rwmutex_wrlock l(mAsk);
			askCount++;
		}
	}

	if( dlog->is_info() )
		dlog->info() << peername << "(run): stop thread of sessions..disconnect.." << endl;

	disconnect();

	if( dlog->is_info() )
		dlog->info() << peername << "(run): thread stopping..." << endl;

	cancelled = true;
}
// -------------------------------------------------------------------------
ModbusRTU::mbErrCode ModbusTCPSession::receive( const std::unordered_set<ModbusAddr>& vmbaddr, timeout_t msec )
{
	ModbusRTU::mbErrCode res = erTimeOut;
	ptTimeout.setTiming(msec);

	{
		memset(&curQueryHeader, 0, sizeof(curQueryHeader));
		res = tcp_processing( static_cast<ost::TCPStream&>(*this), curQueryHeader);

		if( res != erNoError )
			return res;

		if( msec != UniSetTimer::WaitUpTime )
		{
			msec = ptTimeout.getLeft(msec);

			if( msec == 0 ) // времени для ответа не осталось..
				return erTimeOut;
		}

		if( qrecv.empty() )
			return erTimeOut;

		unsigned char q_addr = qrecv.front();

		if( cancelled )
			return erSessionClosed;

		memset(&buf, 0, sizeof(buf));
		res = recv( vmbaddr, buf, msec );

		if( cancelled )
			return erSessionClosed;

		if( res != erNoError ) // && res!=erBadReplyNodeAddress )
		{
			if( res < erInternalErrorCode )
			{
				ErrorRetMessage em( q_addr, buf.func, res );
				buf = em.transport_msg();
				send(buf);
				printProcessingTime();
			}
			else if( aftersend_msec > 0 )
				msleep(aftersend_msec);

			return res;
		}

		if( msec != UniSetTimer::WaitUpTime )
		{
			msec = ptTimeout.getLeft(msec);

			if( msec == 0 )
				return erTimeOut;
		}

		if( cancelled )
			return erSessionClosed;

		// processing message...
		res = processing(buf);
	}

	return res;
}
// -------------------------------------------------------------------------
void ModbusTCPSession::final()
{
	slFin(this);
}
// -------------------------------------------------------------------------
mbErrCode ModbusTCPSession::sendData( unsigned char* buf, int len )
{
	return ModbusTCPCore::sendData(this, buf, len);
}
// -------------------------------------------------------------------------
int ModbusTCPSession::getNextData( unsigned char* buf, int len )
{
	return ModbusTCPCore::getNextData(this, qrecv, buf, len);
}
// --------------------------------------------------------------------------------

mbErrCode ModbusTCPSession::tcp_processing( ost::TCPStream& tcp, ModbusTCP::MBAPHeader& mhead )
{
	if( !isConnected() )
		return erTimeOut;

	// чистим очередь
	while( !qrecv.empty() )
		qrecv.pop();

	unsigned int len = getNextData((unsigned char*)(&mhead), sizeof(mhead));

	if( len < sizeof(mhead) )
	{
		if( len == 0 )
			return erSessionClosed;

		return erInvalidFormat;
	}

	mhead.swapdata();

	if( dlog->is_info() )
	{
		dlog->info() << peername << "(tcp_processing): recv tcp header(" << len << "): ";
		mbPrintMessage( dlog->info(), (ModbusByte*)(&mhead), sizeof(mhead));
		dlog->info() << endl;
	}

	// check header
	if( mhead.pID != 0 )
		return erUnExpectedPacketType; // erTimeOut;

	if( mhead.len > ModbusRTU::MAXLENPACKET )
	{
		if( dlog->is_info() )
			dlog->info() << "(ModbusTCPServer::tcp_processing): len(" << (int)mhead.len
						 << ") < MAXLENPACKET(" << ModbusRTU::MAXLENPACKET << ")" << endl;

		return erInvalidFormat;
	}

	len = ModbusTCPCore::readNextData(&tcp, qrecv, mhead.len);

	if( len < mhead.len )
	{
		if( dlog->is_info() )
			dlog->info() << peername << "(tcp_processing): len(" << (int)len
						 << ") < mhead.len(" << (int)mhead.len << ")" << endl;

		return erInvalidFormat;
	}

	return erNoError;
}
// -------------------------------------------------------------------------
ModbusRTU::mbErrCode ModbusTCPSession::post_send_request( ModbusRTU::ModbusMessage& request )
{
	*tcp() << endl;
	return erNoError;
}
// -------------------------------------------------------------------------
mbErrCode ModbusTCPSession::pre_send_request( ModbusMessage& request )
{
	if( !isConnected() )
		return erTimeOut;

	curQueryHeader.len = request.len + szModbusHeader;

	if( crcNoCheckit )
		curQueryHeader.len -= szCRC;

	curQueryHeader.swapdata();

	if( dlog->is_info() )
	{
		dlog->info() << peername << "(pre_send_request): send tcp header: ";
		mbPrintMessage( dlog->info(), (ModbusByte*)(&curQueryHeader), sizeof(curQueryHeader));
		dlog->info() << endl;
	}

	*tcp() << curQueryHeader;

	curQueryHeader.swapdata();

	return erNoError;
}
// -------------------------------------------------------------------------
void ModbusTCPSession::cleanInputStream()
{
	unsigned char buf[100];
	int ret = 0;

	do
	{
		ret = getNextData(buf, sizeof(buf));
	}
	while( ret > 0);
}
// -------------------------------------------------------------------------
void ModbusTCPSession::terminate()
{
	ModbusServer::terminate();

	if( dlog->is_info() )
		dlog->info() << peername << "(terminate)..." << endl;

	cancelled = true;

	if( isConnected() )
		disconnect();

	//    if( isRunning() )
	//        ost::Thread::join();
}
// -------------------------------------------------------------------------
mbErrCode ModbusTCPSession::readCoilStatus( ReadCoilMessage& query,
		ReadCoilRetMessage& reply )
{
	if( !slReadCoil )
		return erOperationFailed;

	return slReadCoil(query, reply);
}

// -------------------------------------------------------------------------
mbErrCode ModbusTCPSession::readInputStatus( ReadInputStatusMessage& query,
		ReadInputStatusRetMessage& reply )
{
	if( !slReadInputStatus )
		return erOperationFailed;

	return slReadInputStatus(query, reply);
}

// -------------------------------------------------------------------------

mbErrCode ModbusTCPSession::readOutputRegisters( ReadOutputMessage& query,
		ReadOutputRetMessage& reply )
{
	if( !slReadOutputs )
		return erOperationFailed;

	return slReadOutputs(query, reply);
}

// -------------------------------------------------------------------------
mbErrCode ModbusTCPSession::readInputRegisters( ReadInputMessage& query,
		ReadInputRetMessage& reply )
{
	if( !slReadInputs )
		return erOperationFailed;

	return slReadInputs(query, reply);
}

// -------------------------------------------------------------------------
mbErrCode ModbusTCPSession::forceMultipleCoils( ForceCoilsMessage& query,
		ForceCoilsRetMessage& reply )
{
	if( !slForceCoils )
		return erOperationFailed;

	return slForceCoils(query, reply);
}

// -------------------------------------------------------------------------

mbErrCode ModbusTCPSession::writeOutputRegisters( WriteOutputMessage& query,
		WriteOutputRetMessage& reply )
{
	if( !slWriteOutputs )
		return erOperationFailed;

	return slWriteOutputs(query, reply);
}

// -------------------------------------------------------------------------
mbErrCode ModbusTCPSession::diagnostics( DiagnosticMessage& query,
		DiagnosticRetMessage& reply )
{
	if( !slDiagnostics )
		return erOperationFailed;

	return slDiagnostics(query, reply);
}
// -------------------------------------------------------------------------
ModbusRTU::mbErrCode ModbusTCPSession::read4314( ModbusRTU::MEIMessageRDI& query,
		ModbusRTU::MEIMessageRetRDI& reply )
{
	if( !slMEIRDI )
		return erOperationFailed;

	return slMEIRDI(query, reply);
}
// -------------------------------------------------------------------------
mbErrCode ModbusTCPSession::forceSingleCoil( ForceSingleCoilMessage& query,
		ForceSingleCoilRetMessage& reply )
{
	if( !slForceSingleCoil )
		return erOperationFailed;

	return slForceSingleCoil(query, reply);
}

// -------------------------------------------------------------------------
mbErrCode ModbusTCPSession::writeOutputSingleRegister( WriteSingleOutputMessage& query,
		WriteSingleOutputRetMessage& reply )
{
	if( !slWriteSingleOutputs )
		return erOperationFailed;

	return slWriteSingleOutputs(query, reply);
}

// -------------------------------------------------------------------------
mbErrCode ModbusTCPSession::journalCommand( JournalCommandMessage& query,
		JournalCommandRetMessage& reply )
{
	if( !slJournalCommand )
		return erOperationFailed;

	return slJournalCommand(query, reply);
}
// -------------------------------------------------------------------------
ModbusRTU::mbErrCode ModbusTCPSession::setDateTime( ModbusRTU::SetDateTimeMessage& query,
		ModbusRTU::SetDateTimeRetMessage& reply )
{
	if( !slSetDateTime )
		return erOperationFailed;

	return slSetDateTime(query, reply);
}
// -------------------------------------------------------------------------
ModbusRTU::mbErrCode ModbusTCPSession::remoteService( ModbusRTU::RemoteServiceMessage& query,
		ModbusRTU::RemoteServiceRetMessage& reply )
{
	if( !slRemoteService )
		return erOperationFailed;

	return slRemoteService(query, reply);
}
// -------------------------------------------------------------------------
ModbusRTU::mbErrCode ModbusTCPSession::fileTransfer( ModbusRTU::FileTransferMessage& query,
		ModbusRTU::FileTransferRetMessage& reply )
{
	if( !slFileTransfer )
		return erOperationFailed;

	return slFileTransfer(query, reply);
}
// -------------------------------------------------------------------------
void ModbusTCPSession::setChannelTimeout( timeout_t msec )
{
	setTimeout(msec);
}
// -------------------------------------------------------------------------
void ModbusTCPSession::connectFinalSession( FinalSlot sl )
{
	slFin = sl;
}
// -------------------------------------------------------------------------

/* This file is part of the UniSet project
 * Copyright (c) 2002 Free Software Foundation, Inc.
 * Copyright (c) 2002 Pavel Vainerman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
// --------------------------------------------------------------------------
/*! \file
 *  \author Pavel Vainerman
*/
//----------------------------------------------------------------------------
#ifndef SQLiteInterface_H_
#define SQLiteInterface_H_
// ---------------------------------------------------------------------------
#include <string>
#include <deque>
#include <vector>
#include <iostream>
#include <sqlite3.h>
#include "PassiveTimer.h"
#include <DBInterface.h>
// ----------------------------------------------------------------------------
/*!  \page SQLiteIntarface  Интерфейс к SQLite

   Пример использования:
\code
    try
    {
        SQLiteInterface db;
        if( !db.connect("test.db") )
        {
            cerr << "db connect error: " << db.error() << endl;
            return 1;
        }

        stringstream q;
        q << "SELECT * from main_history";

        DBResult r = db.query(q.str());
        if( !r )
        {
            cerr << "db connect error: " << db.error() << endl;
            return 1;
        }

        for( DBResult::iterator it=r.begin(); it!=r.end(); it++ )
        {
            cout << "ROW: ";
            DBResult::COL col(*it);
            for( DBResult::COL::iterator cit = it->begin(); cit!=it->end(); cit++ )
				cout << DBResult::as_string(cit) << "(" << DBResult::as_double(cit) << ")  |  ";
            cout << endl;
        }

        db.close();
    }
    catch(Exception& ex)
    {
        cerr << "(test): " << ex << endl;
    }
    catch(...)
    {
        cerr << "(test): catch ..." << endl;
    }
\endcode
*/
// ----------------------------------------------------------------------------
// Памятка:
// Включение режима для журнала - "вести в памяти" (чтобы поберечь CompactFlash)
// PRAGMA journal_mode = MEMORY
// При этом конечно есть риск потерять данные при выключении..
// ----------------------------------------------------------------------------
class SQLiteInterface:
	public DBInterface
{
	public:

		SQLiteInterface();
		~SQLiteInterface();

		virtual bool connect( const std::string& param ) override;
		bool connect( const std::string& dbfile, bool create );
		virtual bool close() override;
		virtual bool isConnection() override;
		virtual bool ping() override; // проверка доступности БД

		void setOperationTimeout( timeout_t msec );
		inline timeout_t getOperationTimeout()
		{
			return opTimeout;
		}

		inline void setOperationCheckPause( timeout_t msec )
		{
			opCheckPause = msec;
		}
		inline timeout_t getOperationCheckPause()
		{
			return opCheckPause;
		}

		virtual DBResult query( const std::string& q ) override;
		virtual const std::string lastQuery() override;

		virtual bool insert( const std::string& q ) override;
		virtual double insert_id() override;

		virtual const std::string error() override;

	protected:

		bool wait( sqlite3_stmt* stmt, int result );
		static bool checkResult( int rc );

	private:

		void makeResult(DBResult& dbres, sqlite3_stmt* s, bool finalize = true );
		sqlite3* db;
		// sqlite3_stmt* curStmt;

		std::string lastQ;
		std::string lastE;
		bool queryok;    // успешность текущего запроса
		bool connected;

		timeout_t opTimeout;
		timeout_t opCheckPause;
};
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif
// ----------------------------------------------------------------------------------

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
// --------------------------------------------------------------------------
/*! \file
 * \brief Реализация базового(фундаментального) класса для объектов системы
 * (процессов управления, элементов графического интерфейса и т.п.)
 * \author Pavel Vainerman
 */
//---------------------------------------------------------------------------
#ifndef UniSetObject_H_
#define UniSetObject_H_
//--------------------------------------------------------------------------
#include <condition_variable>
#include <thread>
#include <mutex>
#include <atomic>
#include <unistd.h>
#include <sys/time.h>
#include <queue>
#include <ostream>
#include <memory>
#include <string>
#include <list>

#include "UniSetTypes.h"
#include "MessageType.h"
#include "PassiveTimer.h"
#include "Exceptions.h"
#include "UInterface.h"
#include "UniSetObject_i.hh"
#include "ThreadCreator.h"
#include "LT_Object.h"

//---------------------------------------------------------------------------
//#include <omnithread.h>
//---------------------------------------------------------------------------
class UniSetActivator;
class UniSetManager;

//---------------------------------------------------------------------------
class UniSetObject;
typedef std::list< std::shared_ptr<UniSetObject> > ObjectsList;     /*!< Список подчиненных объектов */
//---------------------------------------------------------------------------
/*! \class UniSetObject
 *    Класс задает такие свойства объекта как: получение сообщений, помещение сообщения в очередь и т.п.
 *    Для ожидания сообщений используется функция waitMessage(), основанная на таймере.
 *    Ожидание прерывается либо по истечении указанного времени, либо по приходу сообщения, при помощи функциии
 *    termWaiting() вызываемой из push().
 *     \note Если не будет задан ObjectId(-1), то поток обработки запущен не будет.
 *    Также создание потока можно принудительно отключить при помощи функции void thread(). Ее необходимо вызвать до активации объекта
 *    (например в конструкторе). При этом ответственность за вызов receiveMessage() и processingMessage() возлагается
 *    на разработчика.
*/
class UniSetObject:
	public std::enable_shared_from_this<UniSetObject>,
	public POA_UniSetObject_i,
	public LT_Object
{
	public:
		UniSetObject(const std::string& name, const std::string& section);
		UniSetObject(UniSetTypes::ObjectId id);
		UniSetObject();
		virtual ~UniSetObject();

		std::shared_ptr<UniSetObject> get_ptr()
		{
			return shared_from_this();
		}

		// Функции объявленные в IDL
		virtual CORBA::Boolean exist() override;

		virtual UniSetTypes::ObjectId getId() override
		{
			return myid;
		}
		inline const UniSetTypes::ObjectId getId() const
		{
			return myid;
		}
		inline std::string getName()
		{
			return myname;
		}

		virtual UniSetTypes::ObjectType getType() override
		{
			return UniSetTypes::ObjectType("UniSetObject");
		}
		virtual UniSetTypes::SimpleInfo* getInfo( ::CORBA::Long userparam = 0 ) override;
		friend std::ostream& operator<<(std::ostream& os, UniSetObject& obj );

		//! поместить сообщение в очередь
		virtual void push( const UniSetTypes::TransportMessage& msg ) override;

		/*! получить ссылку (на себя) */
		inline UniSetTypes::ObjectPtr getRef() const
		{
			UniSetTypes::uniset_rwmutex_rlock lock(refmutex);
			return (UniSetTypes::ObjectPtr)CORBA::Object::_duplicate(oref);
		}

		virtual timeout_t askTimer( UniSetTypes::TimerId timerid, timeout_t timeMS, clock_t ticks = -1,
									UniSetTypes::Message::Priority p = UniSetTypes::Message::High ) override;

	protected:
		/*! обработка приходящих сообщений */
		virtual void processingMessage( const UniSetTypes::VoidMessage* msg );
		virtual void sysCommand( const UniSetTypes::SystemMessage* sm ) {}
		virtual void sensorInfo( const UniSetTypes::SensorMessage* sm ) {}
		virtual void timerInfo( const UniSetTypes::TimerMessage* tm ) {}

		/*! Получить сообщение */
		bool receiveMessage( UniSetTypes::VoidMessage& vm );

		/*! текущее количесво сообщений в очереди */
		unsigned int countMessages();

		/*! прервать ожидание сообщений */
		void termWaiting();

		std::shared_ptr<UInterface> ui; /*!< универсальный интерфейс для работы с другими процессами */
		std::string myname;
		std::string section;

		//! Дизактивизация объекта (переопределяется для необходимых действий перед деактивацией)
		virtual bool deactivateObject()
		{
			return true;
		}
		//! Активизация объекта (переопределяется для необходимых действий после активизации)
		virtual bool activateObject()
		{
			return true;
		}

		/*! запрет(разрешение) создания потока для обработки сообщений */
		inline void thread(bool create)
		{
			threadcreate = create;
		}
		/*! отключение потока обработки сообщений */
		inline void offThread()
		{
			threadcreate = false;
		}
		/*! включение потока обработки сообщений */
		inline void onThread()
		{
			threadcreate = true;
		}

		/*! функция вызываемая из потока */
		virtual void callback();

		/*! Функция вызываемая при приходе сигнала завершения или прерывания процесса. Переопределив ее можно
		 *    выполнять специфичные для процесса действия по обработке сигнала.
		 *    Например переход в безопасное состояние.
		 *  \warning В обработчике сигналов \b ЗАПРЕЩЕНО вызывать функции подобные exit(..), abort()!!!!
		*/
		virtual void sigterm( int signo );

		inline void terminate()
		{
			deactivate();
		}

		/*! Ожидать сообщения timeMS */
		virtual bool waitMessage(UniSetTypes::VoidMessage& msg, timeout_t timeMS = UniSetTimer::WaitUpTime);

		void setID(UniSetTypes::ObjectId id);

		void setMaxSizeOfMessageQueue( size_t s )
		{
			SizeOfMessageQueue = s;
		}

		inline unsigned int getMaxSizeOfMessageQueue()
		{
			return SizeOfMessageQueue;
		}

		void setMaxCountRemoveOfMessage( size_t m )
		{
			MaxCountRemoveOfMessage = m;
		}

		inline unsigned int getMaxCountRemoveOfMessage()
		{
			return MaxCountRemoveOfMessage;
		}

		// функция определения приоритетного сообщения для обработки
		struct PriorVMsgCompare:
			public std::binary_function<UniSetTypes::VoidMessage, UniSetTypes::VoidMessage, bool>
		{
			bool operator()(const UniSetTypes::VoidMessage& lhs,
							const UniSetTypes::VoidMessage& rhs) const;
		};
		typedef std::priority_queue<UniSetTypes::VoidMessage, std::vector<UniSetTypes::VoidMessage>, PriorVMsgCompare> MessagesQueue;


		/*! Вызывается при переполнеии очереди сообщений (в двух местах push и receive)
		    для очитски очереди.
		    \warning По умолчанию удаляет из очереди все повторяющиеся
		     - SensorMessage
		     - TimerMessage
		     - SystemMessage
		 Если не помогло удаляет из очереди UniSetObject::MaxCountRemoveOfMessage
		\note Для специфичной обработки может быть переопределена
		\warning Т.к. при фильтровании SensorMessage не смотрится значение, то
		при удалении сообщений об изменении аналоговых датчиков очистка может привести
		к некорректной работе фильрующих алгоритмов работающих с "выборкой" последних N значений.
		(потому-что останется одно последнее)
		*/
		virtual void cleanMsgQueue( MessagesQueue& q );

		inline bool isActive()
		{
			return active;
		}
		inline void setActive( bool set )
		{
			active = set;
		}

		UniSetTypes::VoidMessage msg;
		std::weak_ptr<UniSetManager> mymngr;

		void setThreadPriority( int p );

		// ------- Статистика -------
		/*! максимальное количество которое было в очереди сообщений */
		inline size_t getMaxQueueMessages()
		{
			return stMaxQueueMessages;
		}

		/*! сколько раз очередь переполнялась */
		inline size_t getCountOfQueueFull()
		{
			return stCountOfQueueFull;
		}

	private:

		friend class UniSetManager;
		friend class UniSetActivator;

		inline pid_t getMsgPID()
		{
			return msgpid;
		}

		/*! функция потока */
		void work();
		//! Инициализация параметров объекта
		bool init( const std::weak_ptr<UniSetManager>& om );
		//! Прямая деактивизация объекта
		bool deactivate();
		//! Непосредственная активизация объекта
		bool activate();
		/* регистрация в репозитории объектов */
		void registered();
		/* удаление ссылки из репозитория объектов     */
		void unregister();

		void init_object();

		pid_t msgpid; // pid потока обработки сообщений
		bool regOK = { false };
		std::atomic_bool active;

		bool threadcreate;
		std::shared_ptr<UniSetTimer> tmr;
		UniSetTypes::ObjectId myid;
		CORBA::Object_var oref;

		std::shared_ptr< ThreadCreator<UniSetObject> > thr;

		/*! очередь сообщений для объекта */
		MessagesQueue queueMsg;

		/*! замок для блокирования совместного доступа к очереди */
		UniSetTypes::uniset_rwmutex qmutex;

		/*! замок для блокирования совместного доступа к очереди */
		mutable UniSetTypes::uniset_rwmutex refmutex;

		/*! размер очереди сообщений (при превышении происходит очистка) */
		size_t SizeOfMessageQueue;
		/*! сколько сообщений удалять при очисте */
		size_t MaxCountRemoveOfMessage;

		// статистическая информация
		size_t stMaxQueueMessages = { 0 };    /*!< Максимальное число сообщений хранившихся в очереди */
		size_t stCountOfQueueFull = { 0 };    /*!< количество переполнений очереди сообщений */

		std::atomic_bool a_working;
		std::mutex    m_working;
		std::condition_variable cv_working;
		//            timeout_t workingTerminateTimeout; /*!< время ожидания завершения потока */
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

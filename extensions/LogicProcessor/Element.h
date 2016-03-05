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
#ifndef Element_H_
#define Element_H_
// --------------------------------------------------------------------------
#include <memory>
#include <string>
#include <list>
#include <ostream>
#include "Exceptions.h"
// --------------------------------------------------------------------------

class LogicException:
	public UniSetTypes::Exception
{
	public:
		LogicException(): UniSetTypes::Exception("LogicException") {}
		explicit LogicException( const std::string& err): UniSetTypes::Exception(err) {}
};


class Element
{
	public:

		typedef std::string ElementID;
		static const ElementID DefaultElementID;

		enum InputType
		{
			unknown,
			external,
			internal
		};

		explicit Element( const ElementID& id ): myid(id) {};
		virtual ~Element() {};


		/*!< функция вызываемая мастером для элементов, которым требуется
		    работа во времени.
		    По умолчанию ничего не делает.
		*/
		virtual void tick() {}

		virtual void setIn( int num, bool state ) = 0;
		virtual bool getOut() = 0;

		inline ElementID getId()
		{
			return myid;
		}
		virtual std::string getType()
		{
			return "?type?";
		}

		virtual std::shared_ptr<Element> find( const ElementID& id );

		virtual void addChildOut( std::shared_ptr<Element> el, int in_num );
		virtual void delChildOut( std::shared_ptr<Element> el );
		inline int outCount()
		{
			return outs.size();
		}

		virtual void addInput( int num, bool state = false );
		virtual void delInput( int num );
		inline  int inCount()
		{
			return ins.size();
		}

		friend std::ostream& operator<<(std::ostream& os, Element& el )
		{
			return os << "[" << el.getType() << "]" << el.getId();
		}

		friend std::ostream& operator<<(std::ostream& os, std::shared_ptr<Element> el )
		{
			if( el )
				return os << (*(el.get()));

			return os;
		}

	protected:
		Element(): myid(DefaultElementID) {}; // нельзя создать элемент без id

		struct ChildInfo
		{
			ChildInfo(std::shared_ptr<Element> e, int n):
				el(e), num(n) {}
			ChildInfo(): el(0), num(0) {}

			std::shared_ptr<Element> el;
			int num;
		};

		typedef std::list<ChildInfo> OutputList;
		OutputList outs;
		virtual void setChildOut();


		struct InputInfo
		{
			InputInfo(): num(0), state(false), type(unknown) {}
			InputInfo(int n, bool s): num(n), state(s), type(unknown) {}
			int num;
			bool state;
			InputType type;
		};

		typedef std::list<InputInfo> InputList;
		InputList ins;

		ElementID myid;

	private:


};
// ---------------------------------------------------------------------------
class TOR:
	public Element
{

	public:
		TOR( ElementID id, unsigned int numbers = 0, bool st = false );
		virtual ~TOR();

		virtual void setIn( int num, bool state ) override;
		virtual bool getOut() override
		{
			return myout;
		}

		virtual std::string getType() override
		{
			return "OR";
		}

	protected:
		TOR(): myout(false) {}
		bool myout;


	private:
};
// ---------------------------------------------------------------------------
class TAND:
	public TOR
{

	public:
		TAND( ElementID id, int numbers = 0, bool st = false );
		virtual ~TAND();

		virtual void setIn( int num, bool state ) override;
		virtual std::string getType() override
		{
			return "AND";
		}

	protected:
		TAND() {}

	private:
};

// ---------------------------------------------------------------------------
// элемент с одним входом и выходом
class TNOT:
	public Element
{

	public:
		TNOT( ElementID id, bool out_default );
		virtual ~TNOT();

		virtual bool getOut() override
		{
			return myout;
		}

		/* num игнорируется, т.к. элемент с одним входом
		 */
		virtual void setIn( int num, bool state ) override ;
		virtual std::string getType() override
		{
			return "NOT";
		}
		virtual void addInput( int num, bool state = false ) override {}
		virtual void delInput( int num ) override {}

	protected:
		TNOT(): myout(false) {}
		bool myout;

	private:
};

// ---------------------------------------------------------------------------
#endif

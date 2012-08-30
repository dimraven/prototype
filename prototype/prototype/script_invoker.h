#ifndef _PROTOTYPE_SCRIPT_INVOKER_H_
#define _PROTOTYPE_SCRIPT_INVOKER_H_

#include "script_reference.h"
#include <iostream>

namespace prototype
{
	class ScriptInvoker : public ScriptReference
	{
	public:
		ScriptInvoker();
		virtual ~ScriptInvoker();

		//
		// Invokes a script method for this instance
		void invokeMethod(const char* methodName);

		//
		// Checks if a method is defined in a script file
		// @param methodName the name of the method
		// @return TRUE if the method is defined in a script file; FALSE otherwise
		bool isMethodDefined(const char* methodName);

		template<typename P1>
		void invokeMethod(const char* methodName, P1 p1)
		{
			if(!findAndPushMethod(methodName))
				return;

			// Push parameters
			script_value<P1>::push(mCurrentState, p1);

			// Call script
			if(lua_pcall(mCurrentState, 2, 0, NULL) != 0)
			{
				std::cerr << "ERROR " << lua_tostring(mCurrentState, -1) << std::endl;
				lua_pop(mCurrentState, 1);
			}

			// Pop the table that's left on the stack
			lua_pop(mCurrentState, 1);
		}
		
		template<typename P1, typename P2>
		void invokeMethod(const char* methodName, P1 p1, P2 p2)
		{
			if(!findAndPushMethod(methodName))
				return;
			
			// Push parameters
			script_value<P1>::push(mCurrentState, p1);
			script_value<P2>::push(mCurrentState, p2);

			// Call script
			if(lua_pcall(mCurrentState, 3, 0, NULL) != 0)
			{
				std::cerr << "ERROR " << lua_tostring(mCurrentState, -1) << std::endl;
				lua_pop(mCurrentState, 1);
			}

			// Pop the table that's left on the stack
			lua_pop(mCurrentState, 1);
		}
		
		template<typename P1, typename P2, typename P3>
		void invokeMethod(const char* methodName, P1 p1, P2 p2, P3 p3)
		{
			if(!findAndPushMethod(methodName))
				return;
			
			// Push parameters
			script_value<P1>::push(mCurrentState, p1);
			script_value<P2>::push(mCurrentState, p2);
			script_value<P3>::push(mCurrentState, p3);

			// Call script
			if(lua_pcall(mCurrentState, 4, 0, NULL) != 0)
			{
				std::cerr << "ERROR " << lua_tostring(mCurrentState, -1) << std::endl;
				lua_pop(mCurrentState, 1);
			}

			// Pop the table that's left on the stack
			lua_pop(mCurrentState, 1);
		}

		template<typename P1, typename P2, typename P3, typename P4>
		void invokeMethod(const char* methodName, P1 p1, P2 p2, P3 p3, P4 p4)
		{
			if(!findAndPushMethod(methodName))
				return;
			
			// Push parameters
			script_value<P1>::push(mCurrentState, p1);
			script_value<P2>::push(mCurrentState, p2);
			script_value<P3>::push(mCurrentState, p3);
			script_value<P4>::push(mCurrentState, p4);

			// Call script
			if(lua_pcall(mCurrentState, 5, 0, NULL) != 0)
			{
				std::cerr << "ERROR " << lua_tostring(mCurrentState, -1) << std::endl;
				lua_pop(mCurrentState, 1);
			}

			// Pop the table that's left on the stack
			lua_pop(mCurrentState, 1);
		}
	private:
		//
		// Uses the script objects reference id to find the table representation of the object on the script side.
		// No values are on the stack if this method returns false; Otherwise both the table and the function is on the stack. (2)
		// @param self
		// @param methodName
		bool findAndPushMethod(const char* methodName);
	};
}

#endif

#ifndef _PROTOTYPE_SCRIPT_H_
#define _PROTOTYPE_SCRIPT_H_

#include "class_definition.h"
#include "wrapper_for_functions.h"

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	extern lua_State* gLuaState;

	//
	//
	class Script
	{
	public:
		//
		// Initializes the script engine.
		static void initialize();

		//
		// Releases the 
		static void release();

		//
		// Load and execute a script file.
		// @param pathToFile the path to the script file.
		static void loadFile(const char* pathToFile);
		
		//
		// Evaluates a string inside the current lua state
		// @param fmt the execution string
		static void evaluatef(const char* fmt, ...);

		//
		// Function used to bind a class to the script 
		template<class Clazz>
		static ClassDefinitionImpl<Clazz>& bind()
		{
			// If an error occures here then make sure to make it integrateable using the defines:
			// DEFINE_SCRIPT_CLASS and IMPLEMENT_SCRIPT_CLASS
			Clazz::getStaticClassDef()->registerClass(gLuaState);
			return *Clazz::getStaticClassDef();
		}

		//
		// Binds a function which has no parameters
		static void bind(const char *funcName, void (*funcPtr)());

		template<typename P1>
		static void bind(const char* funcName, void (*funcPtr)(P1))
		{
			lua_pushlightuserdata(gLuaState, funcPtr);
			lua_pushcclosure(gLuaState, &lua_function_void_1args<P1>, 1);
			lua_setglobal(gLuaState, funcName);
		}
		
		template<typename P1, typename P2>
		static void bind(const char* funcName, void (*funcPtr)(P1, P2))
		{
			lua_pushlightuserdata(gLuaState, funcPtr);
			lua_pushcclosure(gLuaState, &lua_function_void_2args<P1, P2>, 1);
			lua_setglobal(gLuaState, funcName);
		}
		
		template<typename P1, typename P2, typename P3>
		static void bind(const char* funcName, void (*funcPtr)(P1, P2, P3))
		{
			lua_pushlightuserdata(gLuaState, funcPtr);
			lua_pushcclosure(gLuaState, &lua_function_void_3args<P1, P2, P3>, 1);
			lua_setglobal(gLuaState, funcName);
		}
		
		template<typename P1, typename P2, typename P3, typename P4>
		static void bind(const char* funcName, void (*funcPtr)(P1, P2, P3, P4))
		{
			lua_pushlightuserdata(gLuaState, funcPtr);
			lua_pushcclosure(gLuaState, &lua_function_void_4args<P1, P2, P3, P4>, 1);
			lua_setglobal(gLuaState, funcName);
		}

		template<typename R>
		static void bind(const char* funcName, R (*funcPtr)())
		{
			lua_pushlightuserdata(gLuaState, funcPtr);
			lua_pushcclosure(gLuaState, &lua_function_R_0args<R>, 1);
			lua_setglobal(gLuaState, funcName);
		}
		
		template<typename R, typename P1>
		static void bind(const char* funcName, R (*funcPtr)(P1))
		{
			lua_pushlightuserdata(gLuaState, funcPtr);
			lua_pushcclosure(gLuaState, &lua_function_R_1args<R, P1>, 1);
			lua_setglobal(gLuaState, funcName);
		}
		
		template<typename R, typename P1, typename P2>
		static void bind(const char* funcName, R (*funcPtr)(P1, P2))
		{
			lua_pushlightuserdata(gLuaState, funcPtr);
			lua_pushcclosure(gLuaState, &lua_function_R_2args<R, P1, P2>, 1);
			lua_setglobal(gLuaState, funcName);
		}

		template<typename R, typename P1, typename P2, typename P3>
		static void bind(const char* funcName, R (*funcPtr)(P1, P2, P3))
		{
			lua_pushlightuserdata(gLuaState, funcPtr);
			lua_pushcclosure(gLuaState, &lua_function_R_3args<R, P1, P2, P3>, 1);
			lua_setglobal(gLuaState, funcName);
		}
		
		template<typename R, typename P1, typename P2, typename P3, typename P4>
		static void bind(const char* funcName, R (*funcPtr)(P1, P2, P3, P4))
		{
			lua_pushlightuserdata(gLuaState, funcPtr);
			lua_pushcclosure(gLuaState, &lua_function_R_4args<R, P1, P2, P3, P4>, 1);
			lua_setglobal(gLuaState, funcName);
		}
	};

}

#endif

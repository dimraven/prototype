#include "script.h"
#include "script_object.h"
#include <iostream>
#include <stdarg.h>

namespace prototype
{
	lua_State* gLuaState = NULL;

	int lua_delete(lua_State* L)
	{
		int numobjects = lua_gettop(L);
		for(int i = 0; i < numobjects; ++i) {
			ScriptObject* self;
			if(script_value<ScriptObject*>::pop(L, self))
			{
				self->unregisterObject();
				delete self;
			}
			else
			{
				std::cerr << "Cannot delete an instance that isn't a ScriptObject*" << std::endl;
			}
		}

		return 0;
	}

	void Script::initialize()
	{
		gLuaState = luaL_newstate();
		luaL_openlibs(gLuaState);

		// Make sure that delete is available in lua
		lua_register(gLuaState, "delete", lua_delete);

		// Register script object
		bind<ScriptObject>();
	}

	void Script::release()
	{
		int top = lua_gettop(gLuaState);
		assert(top == 0 && "Lua Stack isn't 0 which means that we have a memory leak somewhere");

		lua_close(gLuaState);
		gLuaState = NULL;
	}

	void lua_hook_function(lua_State *L, lua_Debug *ar)
	{
	}

	void Script::evaluatef(const char* fmt, ...)
	{
		char buffer[1024];
		va_list args;
		va_start(args, fmt); 
		vsprintf(buffer, fmt, args);
		va_end(args);

		if(luaL_loadstring(gLuaState, buffer) != 0)
		{
			std::string err = lua_tostring(gLuaState, -1);
			std::cerr << "Could not evaluate string \"" << buffer << "\": " << std::endl << err.c_str() << std::endl;
			lua_pop(gLuaState, 1);
		}
	}
	
	void Script::loadFile(const char* pathToFile)
	{
		int res = luaL_loadfile(gLuaState, pathToFile);
		if(res != 0)
		{
			std::string err = lua_tostring(gLuaState, -1);
			std::cerr << "Could not load file: " << err.c_str() << std::endl;
			lua_pop(gLuaState, 1);
		}
		else
		{
			res = lua_pcall(gLuaState, 0, 0, NULL);
			if(res != 0)
			{
				std::string err = lua_tostring(gLuaState, -1);
				std::cerr << "Could not compile supplied script file: " << err.c_str() << std::endl;
				lua_pop(gLuaState, 1);
			}
		}
	}

	void Script::bind(const char *funcName, void (*funcPtr)())
	{
		lua_pushlightuserdata(gLuaState, funcPtr);
		lua_pushcclosure(gLuaState, &lua_function_void_0args, 1);
		lua_setglobal(gLuaState, funcName);
	}
}

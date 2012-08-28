#include "script.h"
#include "script_object.h"
#include <iostream>

namespace prototype
{
	lua_State* gLuaState = NULL;

	int lua_delete(lua_State* L)
	{
		int numobjects = lua_gettop(L);
		for(int i = 0; i < numobjects; ++i) {
			ScriptObject* self;
			if(script_value<ScriptObject*>::pop(L, self, i + 1))
			{
				self->unregisterObject();
				delete self;
			}
			else
			{
				std::cerr << "Cannot delete an instance that isn't a ScriptObject*" << std::endl;
			}
		}

		lua_pop(L, numobjects);
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
}

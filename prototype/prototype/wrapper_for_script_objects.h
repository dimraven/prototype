#ifndef _PROTOTYPE_WRAPPER_FOR_SCRIPT_OBJECTS_H_
#define _PROTOTYPE_WRAPPER_FOR_SCRIPT_OBJECTS_H_

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	//
	// Function that represents the __call function used to "simulate" a class in Lua.
	template<class Clazz>
	int lua_ScriptObject_call(lua_State* L)
	{
		// If the compiler fails here then the there isn't any default constructor available
		// The class itself must inherit from ScriptObject
		Clazz* obj = new Clazz();
		if(!obj->registerObject()) {
			//log_error("Object could not be registered");
			delete obj;
			return 0;
		}
		
		lua_rawgeti(L, LUA_REGISTRYINDEX, obj->getId());
		return 1;
	}

	//
	// Function called when a user calls the Clazz.init(self) inside script code. This is used when
	// a user inherits from a C++ class from Script.
	template<class Clazz>
	int lua_ScriptObject_init(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 1 && "Only 'self' is allowed as input to the init method");
		
		int scriptRef = luaL_ref(L, LUA_REGISTRYINDEX);
		Clazz* obj = new Clazz();
		if(!obj->registerObject(scriptRef)) {
			//log_error("Object could not be registered");
			delete obj;
		}
		return 0;
	}
}

#endif

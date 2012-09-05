#ifndef _PROTOTYPE_SCRIPT_PTR_H_
#define _PROTOTYPE_SCRIPT_PTR_H_

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	extern lua_State* gLuaState;
}

#endif

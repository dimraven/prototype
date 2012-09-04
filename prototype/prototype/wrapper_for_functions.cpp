#include "wrapper_for_functions.h"

namespace prototype
{
	int lua_function_void_0args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params != 0)
		{
			std::cerr << "Invalid num parameters" << std::endl;
			lua_pop(L, params);
			return 0;
		}

		typedef void (*F)(void);
		F func = (F)lua_touserdata(L, lua_upvalueindex(1));
		(*func)();
		return 0;
	}

}

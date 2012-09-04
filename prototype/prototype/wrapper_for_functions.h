#ifndef _PROTOTYPE_WRAPPER_FOR_FUNCTIONS_H_
#define _PROTOTYPE_WRAPPER_FOR_FUNCTIONS_H_

#include "script_value.h"
#include <cassert>

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	int lua_function_void_0args(lua_State* L);

	template<typename P1>
	int lua_function_void_1args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params == 0)
		{
			std::cerr << "Invalid num parameters" << std::endl;
			return 0;
		}

		P1 p1;

		bool ok = true;
		ok &= script_value<P1>::pop(L, p1);

		if(ok)
		{
			typedef void (*F)(P1);
			F func = (F)lua_touserdata(L, lua_upvalueindex(1));
			(*func)(p1);
		}

		return 0;
	}

	template<typename P1, typename P2>
	int lua_function_void_2args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params < 2)
		{
			std::cerr << "Invalid num parameters" << std::endl;
			lua_pop(L, params);
			return 0;
		}

		P1 p1;
		P2 p2;

		bool ok = true;
		ok &= script_value<P2>::pop(L, p2);
		ok &= script_value<P1>::pop(L, p1);

		if(ok)
		{
			typedef void (*F)(P1, P2);
			F func = (F)lua_touserdata(L, lua_upvalueindex(1));
			(*func)(p1, p2);
		}

		return 0;
	}

	template<typename P1, typename P2, typename P3>
	int lua_function_void_3args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params < 3)
		{
			std::cerr << "Invalid num parameters" << std::endl;
			lua_pop(L, params);
			return 0;
		}

		P1 p1;
		P2 p2;
		P3 p3;

		bool ok = true;
		ok &= script_value<P3>::pop(L, p3);
		ok &= script_value<P2>::pop(L, p2);
		ok &= script_value<P1>::pop(L, p1);

		if(ok)
		{
			typedef void (*F)(P1, P2, P3);
			F func = (F)lua_touserdata(L, lua_upvalueindex(1));
			(*func)(p1, p2, p3);
		}

		return 0;
	}

	template<typename P1, typename P2, typename P3, typename P4>
	int lua_function_void_4args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params < 4)
		{
			std::cerr << "Invalid num parameters" << std::endl;
			lua_pop(L, params);
			return 0;
		}

		P1 p1;
		P2 p2;
		P3 p3;
		P4 p4;

		bool ok = true;
		ok &= script_value<P4>::pop(L, p4);
		ok &= script_value<P3>::pop(L, p3);
		ok &= script_value<P2>::pop(L, p2);
		ok &= script_value<P1>::pop(L, p1);

		if(ok)
		{
			typedef void (*F)(P1, P2, P3, P4);
			F func = (F)lua_touserdata(L, lua_upvalueindex(1));
			(*func)(p1, p2, p3, p4);
		}

		return 0;
	}

	
	template<typename R>
	int lua_function_R_0args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params == 0)
		{
			std::cerr << "Invalid num parameters" << std::endl;
			lua_pushnil(L);
			return 1;
		}

		typedef R (*F)();
		F func = (F)lua_touserdata(L, lua_upvalueindex(1));
		R ret = (*func)();
		script_value<R>::push(L, ret);
		return 1;
	}
	
	template<typename R, typename P1>
	int lua_function_R_1args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params > 0)
		{
			P1 p1;

			bool ok = script_value<P1>::pop(L, p1);

			if(ok)
			{
				typedef R (*F)(P1);
				F func = (F)lua_touserdata(L, lua_upvalueindex(1));
				R ret = (*func)(p1);
				script_value<R>::push(L, ret);
			}
			else
			{
				lua_pushnil(L);
			}
		}
		else
		{
			std::cerr << "Invalid num parameters" << std::endl;
			lua_pushnil(L);
		}

		return 1;
	}

	template<typename R, typename P1, typename P2>
	int lua_function_R_2args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params > 1)
		{
			P1 p1;
			P2 p2;

			bool ok = true;
			ok &= script_value<P2>::pop(L, p2);
			ok &= script_value<P1>::pop(L, p1);

			if(ok)
			{
				typedef R (*F)(P1, P2);
				F func = (F)lua_touserdata(L, lua_upvalueindex(1));
				R ret = (*func)(p1, p2);
				script_value<R>::push(L, ret);
			}
			else
			{
				lua_pushnil(L);
			}
		}
		else
		{
			std::cerr << "Invalid num parameters" << std::endl;
			lua_pop(L, params);
			lua_pushnil(L);
		}

		return 1;
	}
	
	template<typename R, typename P1, typename P2, typename P3, typename P4>
	int lua_function_R_3args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params > 3)
		{
			P1 p1;
			P2 p2;
			P3 p3;

			bool ok = true;
			ok &= script_value<P3>::pop(L, p3);
			ok &= script_value<P2>::pop(L, p2);
			ok &= script_value<P1>::pop(L, p1);

			if(ok)
			{
				typedef R (*F)(P1, P2, P3);
				F func = (F)lua_touserdata(L, lua_upvalueindex(1));
				R ret = (*func)(p1, p2, p3);
				script_value<R>::push(L, ret);
			}
			else
			{
				lua_pushnil(L);
			}
		}
		else
		{
			std::cerr << "Invalid num parameters" << std::endl;
			lua_pop(L, params);
			lua_pushnil(L);
		}

		return 1;
	}

	template<typename R, typename P1, typename P2, typename P3>
	int lua_function_R_4args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params > 2)
		{
			P1 p1;
			P2 p2;
			P3 p3;
			P4 p4;

			bool ok = true;
			ok &= script_value<P4>::pop(L, p4);
			ok &= script_value<P3>::pop(L, p3);
			ok &= script_value<P2>::pop(L, p2);
			ok &= script_value<P1>::pop(L, p1);

			if(ok)
			{
				typedef R (*F)(P1, P2, P3, P4);
				F func = (F)lua_touserdata(L, lua_upvalueindex(1));
				R ret = (*func)(p1, p2, p3, p4);
				script_value<R>::push(L, ret);
			}
			else
			{
				lua_pushnil(L);
			}
		}
		else
		{
			std::cerr << "Invalid num parameters" << std::endl;
			lua_pop(L, params);
			lua_pushnil(L);
		}

		return 1;
	}
	
}

#endif

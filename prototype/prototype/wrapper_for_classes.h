#ifndef _PROTOTYPE_WRAPPER_FOR_CLASSES_H_
#define _PROTOTYPE_WRAPPER_FOR_CLASSES_H_

#include "script_value.h"
#include "wrapper_for_methods.h"
#include <cassert>

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	//
	// Method used to wrap method calls
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz>
	int lua_method_void_0args(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 1 && "Only the 'self' parameter are allowed as a parameter for this function");

		Clazz* self;
		if(script_value<Clazz*>::pop(L, self, 1))
		{
			method_pointer_wrapper_void_0args<Clazz>* wrapper = 
				(method_pointer_wrapper_void_0args<Clazz>*)lua_touserdata(L, lua_upvalueindex(1));
			(self->*wrapper->methodPtr)();
		}
		lua_pop(L, params);
		return 0;
	}

	//
	// Method used to wrap method calls with 1 parameter
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz, typename P1>
	int lua_method_void_1args(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 2 && "Only the 'self' + P1 is allowed as parameter for this function");
		
		Clazz* self;
		P1 p1;
		if(script_value<Clazz*>::pop(L, self, 1) && script_value<P1>::pop(L, p1, 2))
		{
			method_pointer_wrapper_void_1args<Clazz, P1>* wrapper = 
				(method_pointer_wrapper_void_1args<Clazz, P1>*)lua_touserdata(L, lua_upvalueindex(1));
			(self->*wrapper->methodPtr)(p1);
		}
		
		lua_pop(L, params);
		return 0;
	}
	
	//
	// Method used to wrap method calls with 2 parameter
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz, typename P1, typename P2>
	int lua_method_void_2args(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 3 && "Only the 'self' + P1 + P2 is allowed as parameter for this function");

		Clazz* self;
		P1 p1;
		P2 p2;
		if(script_value<Clazz*>::pop(L, self, 1) && script_value<P1>::pop(L, p1, 2) && 
			script_value<P2>::pop(L, p2, 3))
		{
			method_pointer_wrapper_void_2args<Clazz, P1, P2>* wrapper = 
				(method_pointer_wrapper_void_2args<Clazz, P1, P2>*)lua_touserdata(L, lua_upvalueindex(1));
			(self->*wrapper->methodPtr)(p1, p2);
		}

		lua_pop(L, params);
		return 0;
	}
	
	//
	// Method used to wrap method calls with 3 parameter
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz, typename P1, typename P2, typename P3>
	int lua_method_void_3args(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 4 && "Only the 'self' + P1 + P2 is allowed as parameter for this function");

		Clazz* self;
		P1 p1;
		P2 p2;
		P3 p3;
		if(script_value<Clazz*>::pop(L, self, 1) && script_value<P1>::pop(L, p1, 2) && 
			script_value<P2>::pop(L, p2, 3) && script_value<P3>::pop(L, p3, 4))
		{
			method_pointer_wrapper_void_3args<Clazz, P1, P2, P3>* wrapper = 
				(method_pointer_wrapper_void_3args<Clazz, P1, P2, P3>*)lua_touserdata(L, lua_upvalueindex(1));
			(self->*wrapper->methodPtr)(p1, p2, p3);
		}

		lua_pop(L, params);
		return 0;
	}

	//
	// Method used to wrap method calls with 4 parameter
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz, typename P1, typename P2, typename P3, typename P4>
	int lua_method_void_3args(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 5 && "Only the 'self' + P1 + P2 is allowed as parameter for this function");

		Clazz* self;
		P1 p1;
		P2 p2;
		P3 p3;
		P4 p4;
		if(script_value<Clazz*>::pop(L, self, 1) && script_value<P1>::pop(L, p1, 2) && 
			script_value<P2>::pop(L, p2, 3) && script_value<P3>::pop(L, p3, 4) &&
			script_value<P4>::pop(L, p4, 5))
		{
			method_pointer_wrapper_void_4args<Clazz, P1, P2, P3, P4>* wrapper = 
				(method_pointer_wrapper_void_4args<Clazz, P1, P2, P3, P4>*)lua_touserdata(L, lua_upvalueindex(1));
			(self->*wrapper->methodPtr)(p1, p2, p3, p4);
		}

		lua_pop(L, params);
		return 0;
	}







	//
	// Method used to wrap method calls
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz, typename R>
	int lua_method_R_0args(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 1 && "Only the 'self' parameter are allowed as a parameter for this function");

		Clazz* self;
		if(script_value<Clazz*>::pop(L, self, 1))
		{
			method_pointer_wrapper_R_0args<Clazz, R>* wrapper = 
				(method_pointer_wrapper_R_0args<Clazz, R>*)lua_touserdata(L, lua_upvalueindex(1));
			R ret = (self->*wrapper->methodPtr)();
			lua_pop(L, params);
			script_value<R>::push(L, ret);
			return 1;
		}
		lua_pop(L, params);
		return 0;
	}

	//
	// Method used to wrap method calls with 1 parameter
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz, typename R, typename P1>
	int lua_method_R_1args(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 2 && "Only the 'self' + P1 is allowed as parameter for this function");
		
		Clazz* self;
		P1 p1;
		if(script_value<Clazz*>::pop(L, self, 1) && script_value<P1>::pop(L, p1, 2))
		{
			method_pointer_wrapper_R_1args<Clazz, R, P1>* wrapper = 
				(method_pointer_wrapper_R_1args<Clazz, R, P1>*)lua_touserdata(L, lua_upvalueindex(1));
			R ret = (self->*wrapper->methodPtr)(p1);
			lua_pop(L, params);
			script_value<R>::push(L, ret);
			return 1;
		}
		
		lua_pop(L, params);
		return 0;
	}
	
	//
	// Method used to wrap method calls with 2 parameter
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz, typename R, typename P1, typename P2>
	int lua_method_R_2args(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 3 && "Only the 'self' + P1 + P2 is allowed as parameter for this function");

		Clazz* self;
		P1 p1;
		P2 p2;
		if(script_value<Clazz*>::pop(L, self, 1) && script_value<P1>::pop(L, p1, 2) && 
			script_value<P2>::pop(L, p2, 3))
		{
			method_pointer_wrapper_R_2args<Clazz, R, P1, P2>* wrapper = 
				(method_pointer_wrapper_R_2args<Clazz, R, P1, P2>*)lua_touserdata(L, lua_upvalueindex(1));
			R ret = (self->*wrapper->methodPtr)(p1, p2);
			lua_pop(L, params);
			script_value<R>::push(L, ret);
			return 1;
		}

		lua_pop(L, params);
		return 0;
	}
	
	//
	// Method used to wrap method calls with 3 parameter
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz, typename R, typename P1, typename P2, typename P3>
	int lua_method_R_3args(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 4 && "Only the 'self' + P1 + P2 is allowed as parameter for this function");

		Clazz* self;
		P1 p1;
		P2 p2;
		P3 p3;
		if(script_value<Clazz*>::pop(L, self, 1) && script_value<P1>::pop(L, p1, 2) && 
			script_value<P2>::pop(L, p2, 3) && script_value<P3>::pop(L, p3, 4))
		{
			method_pointer_wrapper_R_3args<Clazz, R, P1, P2, P3>* wrapper = 
				(method_pointer_wrapper_R_3args<Clazz, R, P1, P2, P3>*)lua_touserdata(L, lua_upvalueindex(1));
			R ret = (self->*wrapper->methodPtr)(p1, p2, p3);
			lua_pop(L, params);
			script_value<R>::push(L, ret);
			return 1;
		}

		lua_pop(L, params);
		return 0;
	}

	//
	// Method used to wrap method calls with 4 parameter
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz, typename R, typename P1, typename P2, typename P3, typename P4>
	int lua_method_R_3args(lua_State* L)
	{
		int params = lua_gettop(L);
		assert(params == 5 && "Only the 'self' + P1 + P2 is allowed as parameter for this function");

		Clazz* self;
		P1 p1;
		P2 p2;
		P3 p3;
		P4 p4;
		if(script_value<Clazz*>::pop(L, self, 1) && script_value<P1>::pop(L, p1, 2) && 
			script_value<P2>::pop(L, p2, 3) && script_value<P3>::pop(L, p3, 4) &&
			script_value<P4>::pop(L, p4, 5))
		{
			method_pointer_wrapper_R_4args<Clazz, R, P1, P2, P3, P4>* wrapper = 
				(method_pointer_wrapper_R_4args<Clazz, R, P1, P2, P3, P4>*)lua_touserdata(L, lua_upvalueindex(1));
			R ret = (self->*wrapper->methodPtr)(p1, p2, p3, p4);
			lua_pop(L, params);
			script_value<R>::push(L, ret);
			return 1;
		}

		lua_pop(L, params);
		return 0;
	}
}

#endif

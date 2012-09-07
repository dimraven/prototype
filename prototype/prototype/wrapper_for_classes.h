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
		if(params <= 0)
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid num parameters for method with name: " << name << std::endl;
			return 0;
		}

		Clazz* self;

		bool ok = script_value<Clazz*>::pop(L, self);

		if(ok)
		{
			method_pointer_wrapper_void_0args<Clazz>* wrapper = 
				(method_pointer_wrapper_void_0args<Clazz>*)lua_touserdata(L, lua_upvalueindex(1));
			(self->*wrapper->methodPtr)();
		}
		else
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid parameters to method with name: " << name << std::endl;
		}

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
		if(params < 2)
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid num parameters for method with name: " << name << std::endl;
			lua_pop(L, params);
			return 0;
		}

		Clazz* self;
		P1 p1;

		bool ok = true;
		ok &= script_value<P1>::pop(L, p1);
		ok &= script_value<Clazz*>::pop(L, self);

		if(ok)
		{
			method_pointer_wrapper_void_1args<Clazz, P1>* wrapper = 
				(method_pointer_wrapper_void_1args<Clazz, P1>*)lua_touserdata(L, lua_upvalueindex(1));
			(self->*wrapper->methodPtr)(p1);
		}
		else
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid parameters to method with name: " << name << std::endl;
		}
		
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
		if(params < 3)
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid num parameters for method with name: " << name << std::endl;
			lua_pop(L, params);
			return 0;
		}

		Clazz* self;
		P1 p1;
		P2 p2;

		bool ok = true;
		ok &= script_value<P2>::pop(L, p2);
		ok &= script_value<P1>::pop(L, p1);
		ok &= script_value<Clazz*>::pop(L, self);

		if(ok)
		{
			method_pointer_wrapper_void_2args<Clazz, P1, P2>* wrapper = 
				(method_pointer_wrapper_void_2args<Clazz, P1, P2>*)lua_touserdata(L, lua_upvalueindex(1));
			(self->*wrapper->methodPtr)(p1, p2);
		}
		else
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid parameters to method with name: " << name << std::endl;
		}

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
		if(params < 4)
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid num parameters for method with name: " << name << std::endl;
			lua_pop(L, params);
			return 0;
		}

		Clazz* self;
		P1 p1;
		P2 p2;
		P3 p3;
		
		bool ok = true;
		ok &= script_value<P3>::pop(L, p3);
		ok &= script_value<P2>::pop(L, p2);
		ok &= script_value<P1>::pop(L, p1);
		ok &= script_value<Clazz*>::pop(L, self);

		if(ok)
		{
			method_pointer_wrapper_void_3args<Clazz, P1, P2, P3>* wrapper = 
				(method_pointer_wrapper_void_3args<Clazz, P1, P2, P3>*)lua_touserdata(L, lua_upvalueindex(1));
			(self->*wrapper->methodPtr)(p1, p2, p3);
		}
		else
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid parameters to method with name: " << name << std::endl;
		}

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
		if(params < 5)
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid num parameters for method with name: " << name << std::endl;
			lua_pop(L, params);
			return 0;
		}

		Clazz* self;
		P1 p1;
		P2 p2;
		P3 p3;
		P4 p4;
		
		bool ok = true;
		ok &= script_value<P4>::pop(L, p4);
		ok &= script_value<P3>::pop(L, p3);
		ok &= script_value<P2>::pop(L, p2);
		ok &= script_value<P1>::pop(L, p1);
		ok &= script_value<Clazz*>::pop(L, self);

		if(ok)
		{
			method_pointer_wrapper_void_4args<Clazz, P1, P2, P3, P4>* wrapper = 
				(method_pointer_wrapper_void_4args<Clazz, P1, P2, P3, P4>*)lua_touserdata(L, lua_upvalueindex(1));
			(self->*wrapper->methodPtr)(p1, p2, p3, p4);
		}
		else
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid parameters to method with name: " << name << std::endl;
		}

		lua_pop(L, params);
		return 0;
	}

	template<class Clazz, typename R>
	int lua_method_R_0args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params > 0)
		{
			Clazz* self;

			bool ok = script_value<Clazz*>::pop(L, self);

			if(ok)
			{
				method_pointer_wrapper_R_0args<Clazz, R>* wrapper = 
					(method_pointer_wrapper_R_0args<Clazz, R>*)lua_touserdata(L, lua_upvalueindex(1));
				R ret = (self->*wrapper->methodPtr)();
				script_value<R>::push(L, ret);
			}
			else
			{
				const char* name = lua_tostring(L, lua_upvalueindex(2));
				std::cerr << "Invalid parameters to method with name: " << name << std::endl;
				lua_pushnil(L);
			}
		}
		else
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid num parameters for method with name: " << name << std::endl;
			lua_pop(L, params);
			lua_pushnil(L);
		}

		return 1;
	}

	template<class Clazz, typename R, typename P1>
	int lua_method_R_1args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params > 1)
		{
			Clazz* self;
			P1 p1;

			bool ok = true;
			ok &= script_value<P1>::pop(L, p1);
			ok &= script_value<Clazz*>::pop(L, self);

			if(ok)
			{
				method_pointer_wrapper_R_1args<Clazz, R, P1>* wrapper = 
					(method_pointer_wrapper_R_1args<Clazz, R, P1>*)lua_touserdata(L, lua_upvalueindex(1));
				R ret = (self->*wrapper->methodPtr)(p1);
				script_value<R>::push(L, ret);
			}
			else
			{
				const char* name = lua_tostring(L, lua_upvalueindex(2));
				std::cerr << "Invalid parameters to method with name: " << name << std::endl;
				lua_pushnil(L);
			}
		}
		else
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid num parameters for method with name: " << name << std::endl;
			lua_pop(L, params);
			lua_pushnil(L);
		}

		return 1;
	}
	
	template<class Clazz, typename R, typename P1, typename P2>
	int lua_method_R_2args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params > 2)
		{
			Clazz* self;
			P1 p1;
			P2 p2;
		
			bool ok = true;
			ok &= script_value<P2>::pop(L, p2);
			ok &= script_value<P1>::pop(L, p1);
			ok &= script_value<Clazz*>::pop(L, self);

			if(ok)
			{
				method_pointer_wrapper_R_2args<Clazz, R, P1, P2>* wrapper = 
					(method_pointer_wrapper_R_2args<Clazz, R, P1, P2>*)lua_touserdata(L, lua_upvalueindex(1));
				R ret = (self->*wrapper->methodPtr)(p1, p2);
				script_value<R>::push(L, ret);
			}
			else
			{
				const char* name = lua_tostring(L, lua_upvalueindex(2));
				std::cerr << "Invalid parameters to method with name: " << name << std::endl;
				lua_pushnil(L);
			}
		}
		else
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid num parameters for method with name: " << name << std::endl;
			lua_pop(L, params);
			lua_pushnil(L);
		}

		return 1;
	}
	
	//
	// Method used to wrap method calls with 3 parameter
	// @param L the current lua state
	// @return Number of parameters returned.
	template<class Clazz, typename R, typename P1, typename P2, typename P3>
	int lua_method_R_3args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params > 3)
		{
			Clazz* self;
			P1 p1;
			P2 p2;
			P3 p3;
		
			bool ok = true;
			ok &= script_value<P3>::pop(L, p3);
			ok &= script_value<P2>::pop(L, p2);
			ok &= script_value<P1>::pop(L, p1);
			ok &= script_value<Clazz*>::pop(L, self);

			if(ok)
			{
				method_pointer_wrapper_R_3args<Clazz, R, P1, P2, P3>* wrapper = 
					(method_pointer_wrapper_R_3args<Clazz, R, P1, P2, P3>*)lua_touserdata(L, lua_upvalueindex(1));
				R ret = (self->*wrapper->methodPtr)(p1, p2, p3);
				script_value<R>::push(L, ret);
			}
			else
			{
				const char* name = lua_tostring(L, lua_upvalueindex(2));
				std::cerr << "Invalid parameters to method with name: " << name << std::endl;
				lua_pushnil(L);
			}
		}
		else
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid num parameters for method with name: " << name << std::endl;
			lua_pop(L, params);
			lua_pushnil(L);
		}

		return 1;
	}

	template<class Clazz, typename R, typename P1, typename P2, typename P3, typename P4>
	int lua_method_R_3args(lua_State* L)
	{
		int params = lua_gettop(L);
		if(params > 4)
		{
			Clazz* self;
			P1 p1;
			P2 p2;
			P3 p3;
			P4 p4;

			bool ok = true;
			ok &= script_value<P4>::pop(L, p4);
			ok &= script_value<P3>::pop(L, p3);
			ok &= script_value<P2>::pop(L, p2);
			ok &= script_value<P1>::pop(L, p1);
			ok &= script_value<Clazz*>::pop(L, self);

			if(ok)
			{
				method_pointer_wrapper_R_4args<Clazz, R, P1, P2, P3, P4>* wrapper = 
					(method_pointer_wrapper_R_4args<Clazz, R, P1, P2, P3, P4>*)lua_touserdata(L, lua_upvalueindex(1));
				R ret = (self->*wrapper->methodPtr)(p1, p2, p3, p4);
				script_value<R>::push(L, ret);
			}
			else
			{
				const char* name = lua_tostring(L, lua_upvalueindex(2));
				std::cerr << "Invalid parameters to method with name: " << name << std::endl;
				lua_pushnil(L);
			}
		}
		else
		{
			const char* name = lua_tostring(L, lua_upvalueindex(2));
			std::cerr << "Invalid num parameters for method with name: " << name << std::endl;
			lua_pop(L, params);
			lua_pushnil(L);
		}

		return 1;
	}
}

#endif

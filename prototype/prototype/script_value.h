#ifndef _PROTOTYPE_SCRIPT_VALUE_H_
#define _PROTOTYPE_SCRIPT_VALUE_H_

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <map>
#include "script_reference.h"
#include "dictionary.h"

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	template<class T> class ScriptObjectPtr;

	template<typename value_type>
	struct script_value
	{
		static bool pop(lua_State* L, value_type& value)
		{
			std::cerr << "Cannot pop unknown type: " << typeid(value_type).name() << std::endl;
			lua_pop(L, 1);
			return true;
		}

		static void push(lua_State* L, value_type& value)
		{
			std::cerr << "Cannot push unknown type: " << typeid(value_type).name() << std::endl;
			lua_pushnil(L);
		}
	};


	template<>
	struct script_value<int>
	{
		static bool pop(lua_State* L, int& value)
		{
			bool ok = lua_isnumber(L, -1) == 1;
			if(ok)
				value = (int)lua_tointeger(L, -1);

			lua_pop(L, 1);
			return ok;
		}

		static void push(lua_State* L, int& value)
		{
			lua_pushinteger(L, (lua_Integer)value);
		}

	};

	template<>
	struct script_value<std::string>
	{
		static bool pop(lua_State* L, std::string& value)
		{
			bool ok = lua_isstring(L, -1) == 1;
			if(ok)
				value = std::string(lua_tostring(L, -1));

			lua_pop(L, 1);
			return ok;
		}
	
		static void push(lua_State* L, std::string& value)
		{
			lua_pushstring(L, value.c_str());
		}
	};

	template<>
	struct script_value<double>
	{
		static bool pop(lua_State* L, double& value)
		{
			bool ok = lua_isnumber(L, -1) == 1;
			if(ok)
				value = (double)lua_tonumber(L, -1);
			
			lua_pop(L, 1);
			return ok;
		}

		static void push(lua_State* L, double& value)
		{
			lua_pushnumber(L, (lua_Number)value);
		}
	};

	template<class Clazz>
	struct script_value<Clazz*>
	{
		static bool pop(lua_State* L, Clazz*& value)
		{
			bool ok = lua_istable(L, -1);
			if(ok)
			{
				lua_pushstring(L, "_instance");
				lua_gettable(L, -2);

				ok = lua_isuserdata(L, -1) == 1;
				if(ok)
				{
					void* userdata = lua_touserdata(L, -1);
					ScriptReference* refValue = reinterpret_cast<ScriptReference*>(userdata);
					value = dynamic_cast<Clazz*>(refValue);
					ok = value != NULL;
				}
				lua_pop(L, 1);
			}

			lua_pop(L, 1);
			return ok;
		}

		static void push(lua_State* L, Clazz*& value)
		{
			if(value == NULL || value->getId() == 0)
			{
				lua_pushnil(L);
				return;
			}

			lua_rawgeti(L, LUA_REGISTRYINDEX, value->getId());
		}
	};

	template<class Clazz>
	struct script_value< ScriptObjectPtr<Clazz> >
	{
		static bool pop(lua_State* L, ScriptObjectPtr<Clazz>& value)
		{
			bool ok = lua_istable(L, -1);
			if(ok)
			{
				lua_pushstring(L, "_instance");
				lua_gettable(L, -2);

				ok = lua_isuserdata(L, -1) == 1;
				if(ok)
				{
					void* userdata = lua_touserdata(L, -1);
					ScriptReference* refValue = reinterpret_cast<ScriptReference*>(userdata);
					value = dynamic_cast<Clazz*>(refValue);
					ok = value.exists();
				}
				lua_pop(L, 1);
			}

			lua_pop(L, 1);
			return ok;
		}

		static void push(lua_State* L, ScriptObjectPtr<Clazz>& value)
		{
			if(!value.exists() || value->getId() == 0)
			{
				lua_pushnil(L);
				return;
			}

			lua_rawgeti(L, LUA_REGISTRYINDEX, value->getId());
			lua_getref(L, value->getId());
		}
	};

	template<>
	struct script_value<float>
	{
		static bool pop(lua_State* L, float& value)
		{
			bool ok = lua_isnumber(L, -1) == 1;
			if(ok)
				value = (float)lua_tonumber(L, -1);

			lua_pop(L, 1);
			return ok;
		}
		
		static void push(lua_State* L, float& value)
		{
			lua_pushnumber(L, (lua_Number)value);
		}
	};

	template<>
	struct script_value<bool>
	{
		static bool pop(lua_State* L, bool& value)
		{
			bool ok = lua_isboolean(L, -1);
			if(ok)
				value = lua_toboolean(L, -1) != 0;

			lua_pop(L, 1);
			return false;
		}

		static void push(lua_State* L, bool& value)
		{
			lua_pushboolean(L, value ? 1 : 0);
		}
	};

	template<>
	struct script_value< Dictionary >
	{
		static bool pop(lua_State* L, Dictionary& value)
		{
			bool ok = lua_istable(L, -1);
			if(ok)
			{
				int ref = luaL_ref(L, LUA_REGISTRYINDEX);
				value = Dictionary(L, ref);
			}
			return ok;
		}

		static void push(lua_State* L, Dictionary& value)
		{
			std::cerr << "Cannot push a Dictionary back to LUA at the moment" << std::endl;
			lua_pushnil(L);
		}
	};

	template<typename item_type>
	struct script_value< std::vector<item_type> >
	{
		static bool pop(lua_State* L, std::vector<item_type>& value)
		{
#ifdef _DEBUG
			int top1 = lua_gettop(L);
#endif
			bool ok = lua_istable(L, -1);
			if(ok)
			{
				lua_pushnil(L);
				while(lua_next(L, -2) != 0)
				{
					item_type item;
					if(script_value<item_type>::pop(L, item))
					{
						value.push_back(item);
					}
				}
			}

			lua_pop(L, 1);
			return false;
		}

		static void push(lua_State* L, std::vector<item_type>& value)
		{
			std::cerr << "Cannot push a std::vector type back to LUA at the moment" << std::endl;
			lua_pushnil(L);
		}
	};
}

#endif

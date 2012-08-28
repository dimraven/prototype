#ifndef _PROTOTYPE_SCRIPT_VALUE_H_
#define _PROTOTYPE_SCRIPT_VALUE_H_

#include <exception>
#include <string>
#include <vector>
#include <map>
#include "script_reference.h"

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	template<typename value_type>
	struct script_value
	{
		static bool pop(lua_State* L, value_type& value, int idx)
		{
			throw std::exception("Un-supported type");
		}

		static void push(lua_State* L, value_type& value)
		{
			throw std::exception("Un-supported type");
		}
	};


	template<>
	struct script_value<int>
	{
		static bool pop(lua_State* L, int& value, int idx)
		{
			if(lua_isnumber(L, idx))
			{
				lua_Integer integer = lua_tointeger(L, idx);
				//lua_pop(L, 1);
				value = (int)integer;
				return true;
			}
		
			//lua_pop(L, 1);
			return false;
		}

		static void push(lua_State* L, int& value)
		{
			lua_pushinteger(L, (lua_Integer)value);
		}

	};

	template<>
	struct script_value<std::string>
	{
		static bool pop(lua_State* L, std::string& value, int idx)
		{
			if(lua_isstring(L, idx))
			{
				const char* str = lua_tostring(L, idx);
				value = std::string(str);
				//lua_pop(L, 1);
				return true;
			}
		
			//lua_pop(L, 1);
			return false;
		}
	
		static void push(lua_State* L, std::string& value)
		{
			lua_pushstring(L, value.c_str());
		}
	};

	template<>
	struct script_value<double>
	{
		static bool pop(lua_State* L, double& value, int idx)
		{
			if(lua_isnumber(L, idx))
			{
				lua_Number number = lua_tonumber(L, idx);
				value = (double)number;
				//lua_pop(L, 1);
				return true;
			}
		
			//lua_pop(L, 1);
			return false;
		}

		static void push(lua_State* L, double& value)
		{
			lua_pushnumber(L, (lua_Number)value);
		}
	};

	template<class Clazz>
	struct script_value<Clazz*>
	{
		static bool pop(lua_State* L, Clazz*& value, int idx)
		{
			if(lua_istable(L, idx))
			{
				lua_pushstring(L, "_instance");
				lua_gettable(L, idx);
				if(lua_isuserdata(L, -1))
				{
					void* userdata = lua_touserdata(L, -1);
					ScriptReference* refValue = reinterpret_cast<ScriptReference*>(userdata);
					value = dynamic_cast<Clazz*>(refValue);
					lua_pop(L, 1);
					return value != NULL;
				}
				lua_pop(L, 1);
				return false;
			}

			return false;
		}

		static void push(lua_State* L, Clazz*& value)
		{
			if(value == NULL || value->getScriptRef() == 0)
			{
				lua_pushnil(L);
				return;
			}

			lua_getref(L, value->getScriptRef());
		}
	};

	template<>
	struct script_value<float>
	{
		static bool pop(lua_State* L, float& value, int idx)
		{
			if(lua_isnumber(L, idx))
			{
				lua_Number number = lua_tonumber(L, idx);
				value = (float)number;
				//lua_pop(L, 1);
				return true;
			}
		
			//lua_pop(L, 1);
			return false;
		}
		
		static void push(lua_State* L, float& value)
		{
			lua_pushnumber(L, (lua_Number)value);
		}
	};

	template<>
	struct script_value<bool>
	{
		static bool pop(lua_State* L, bool& value, int idx)
		{
			if(lua_isboolean(L, idx))
			{
				int boolean = lua_toboolean(L, idx);
				value = boolean == 1;
				//lua_pop(L, 1);
				return true;
			}

			//lua_pop(L, 1);
			return false;
		}

		static void push(lua_State* L, bool& value)
		{
			lua_pushboolean(L, value ? 1 : 0);
		}
	};

	template<typename item_type>
	struct script_value< std::vector<item_type> >
	{
		static bool pop(lua_State* L, std::vector<item_type>& value, int idx)
		{
			if(lua_istable(L, idx))
			{
				// TODO: Implement
			}

			//lua_pop(L, 1);
			return false;
		}

		static int push(lua_State* L, std::vector<item_type>& value)
		{
			//lua_pushboolean(L, value ? 1 : 0);
			return 0;
		}
	};

	template<typename key_type, typename value_type>
	struct script_value< std::map<key_type, value_type> >
	{
		static bool pop(lua_State* L, std::map<key_type, value_type>& value, int idx)
		{
			if(lua_istable(L, idx))
			{
				// TODO: Implement
			}

			//lua_pop(L, 1);
			return false;
		}

		static int push(lua_State* L, std::map<key_type, value_type>& value)
		{
			//lua_pushboolean(L, value ? 1 : 0);
			return 0;
		}
	};
}

#endif

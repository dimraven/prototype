#include "dictionary.h"
#include "script_object.h"
#include "script_value.h"
#include "script.h"

namespace prototype
{
	namespace {
		std::string defaultString("");
	}

	Dictionary::Dictionary()
		: mCurrentState(NULL), mScriptRef(0)
	{
	}

	Dictionary::Dictionary(lua_State* L, int scriptRef)
		: mCurrentState(L), mScriptRef(scriptRef)
	{
	}

	Dictionary::Dictionary(const Dictionary& other)
		: mCurrentState(other.mCurrentState), mScriptRef(0)
	{
		if(other.mScriptRef != 0)
		{
			lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, other.mScriptRef);
			mScriptRef = luaL_ref(mCurrentState, LUA_REGISTRYINDEX);
		}
	}

	Dictionary::~Dictionary()
	{
		if(mScriptRef != 0)
		{
			luaL_unref(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
			mScriptRef = 0;
		}
	}

	std::string Dictionary::getString(const char* key) const
	{
		if(mScriptRef == 0 || key == NULL)
			return defaultString;

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		lua_pushstring(mCurrentState, key);
		lua_gettable(mCurrentState, -2);

		if(lua_isstring(mCurrentState, -1))
		{
			const char* str = lua_tostring(mCurrentState, -1);
			std::string result(str);
			lua_pop(mCurrentState, 2);
			return result;
		}

		lua_pop(mCurrentState, 2);
		return defaultString;
	}

	double Dictionary::getDouble(const char* key) const
	{
		if(mScriptRef == 0 || key == NULL)
			return 0.0;

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		lua_pushstring(mCurrentState, key);
		lua_gettable(mCurrentState, -2);

		double result = 0.0;

		if(lua_isnumber(mCurrentState, -1))
			result = lua_tonumber(mCurrentState, -1);

		lua_pop(mCurrentState, 2);
		return result;
	}
	
	float Dictionary::getFloat(const char* key) const
	{
		if(mScriptRef == 0 || key == NULL)
			return 0.0f;

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		lua_pushstring(mCurrentState, key);
		lua_gettable(mCurrentState, -2);

		float result = 0.0f;

		if(lua_isnumber(mCurrentState, -1))
			result = (float)lua_tonumber(mCurrentState, -1);

		lua_pop(mCurrentState, 2);
		return result;
	}

	bool Dictionary::getBool(const char* key) const
	{
		if(mScriptRef == 0 || key == NULL)
			return 0.0f;

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		lua_pushstring(mCurrentState, key);
		lua_gettable(mCurrentState, -2);

		bool result = false;

		if(lua_isboolean(mCurrentState, -1))
			result = lua_toboolean(mCurrentState, -1) != 0;

		lua_pop(mCurrentState, 2);
		return result;
	}
	
	int Dictionary::getInt(const char* key) const
	{
		if(mScriptRef == 0 || key == NULL)
			return 0;

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		lua_pushstring(mCurrentState, key);
		lua_gettable(mCurrentState, -2);

		int result = 0;

		if(lua_isnumber(mCurrentState, -1))
			result = lua_tointeger(mCurrentState, -1);

		lua_pop(mCurrentState, 2);
		return result;
	}
	
	ScriptObject* Dictionary::getPointer(const char* key) const
	{
		if(mScriptRef == 0 || key == NULL)
			return NULL;

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		lua_pushstring(mCurrentState, key);
		lua_gettable(mCurrentState, -2);

		ScriptObject* result = NULL;
		script_value<ScriptObject*>::pop(mCurrentState, result);
		lua_pop(mCurrentState, 1);
		return result;
	}

	Dictionary Dictionary::getDictionary(const char* key) const
	{
		if(mScriptRef == 0 || key == NULL)
			return Dictionary();

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		lua_pushstring(mCurrentState, key);
		lua_gettable(mCurrentState, -2);
		
		if(lua_istable(mCurrentState, -1))
		{
			Dictionary result(mCurrentState, luaL_ref(mCurrentState, LUA_REGISTRYINDEX));
			lua_pop(mCurrentState, 1);
			return result;
		}

		lua_pop(mCurrentState, 2);
		return Dictionary(mCurrentState, 0);
	}

	Dictionary& Dictionary::operator=(const Dictionary& other)
	{
		if(other.mScriptRef != 0)
		{
			mCurrentState = other.mCurrentState;
			lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, other.mScriptRef);
			mScriptRef = luaL_ref(mCurrentState, LUA_REGISTRYINDEX);
		}

		return *this;
	}
}

#include "script_result.h"
#include "script_object.h"
#include <cassert>

namespace prototype
{
	ScriptResult::ScriptResult()
		: mResultRef(0), mCurrentState(NULL)
	{
	}

	ScriptResult::ScriptResult(lua_State* L, int ref)
		: mResultRef(ref), mCurrentState(L)
	{
	}
	
	ScriptResult::ScriptResult(const ScriptResult& other)
		: mResultRef(0), mCurrentState(other.mCurrentState)
	{
		if(mCurrentState != NULL)
		{
#ifdef _DEBUG
			int top1 = lua_gettop(mCurrentState);
#endif
			lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mResultRef);
			mResultRef = luaL_ref(mCurrentState, LUA_REGISTRYINDEX);
			
#ifdef _DEBUG
			int top2 = lua_gettop(mCurrentState);
			assert(top1 == top2 && "Lua stack is corrupt");
#endif
		}
	}

	ScriptResult::~ScriptResult()
	{
		if(mCurrentState != NULL)
		{
			luaL_unref(mCurrentState, LUA_REGISTRYINDEX, mResultRef);
			mResultRef = 0;
			mCurrentState = NULL;
		}
	}

	int ScriptResult::getInt(int defaultVal) const
	{
		if(mCurrentState == NULL)
			return defaultVal;

#ifdef _DEBUG
		int top1 = lua_gettop(mCurrentState);
#endif

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mResultRef);

		int result = defaultVal;
		script_value<int>::pop(mCurrentState, result, -1);
		lua_pop(mCurrentState, 1);

#ifdef _DEBUG
		int top2 = lua_gettop(mCurrentState);
		assert(top1 == top2 && "Lua stack is corrupt");
#endif

		return defaultVal;
	}

	bool ScriptResult::getBool(bool defaultVal) const
	{
		if(mCurrentState == NULL)
			return defaultVal;

#ifdef _DEBUG
		int top1 = lua_gettop(mCurrentState);
#endif

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mResultRef);

		bool result = defaultVal;
		script_value<bool>::pop(mCurrentState, result, -1);
		lua_pop(mCurrentState, 1);

#ifdef _DEBUG
		int top2 = lua_gettop(mCurrentState);
		assert(top1 == top2 && "Lua stack is corrupt");
#endif

		return defaultVal;
	}

	float ScriptResult::getFloat(float defaultVal) const
	{
		if(mCurrentState == NULL)
			return defaultVal;

#ifdef _DEBUG
		int top1 = lua_gettop(mCurrentState);
#endif

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mResultRef);

		float result = defaultVal;
		script_value<float>::pop(mCurrentState, result, -1);
		lua_pop(mCurrentState, 1);

#ifdef _DEBUG
		int top2 = lua_gettop(mCurrentState);
		assert(top1 == top2 && "Lua stack is corrupt");
#endif

		return result;
	}

	double ScriptResult::getDouble(double defaultVal) const
	{
		if(mCurrentState == NULL)
			return defaultVal;

#ifdef _DEBUG
		int top1 = lua_gettop(mCurrentState);
#endif

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mResultRef);

		double result = defaultVal;
		script_value<double>::pop(mCurrentState, result, -1);
		lua_pop(mCurrentState, 1);

#ifdef _DEBUG
		int top2 = lua_gettop(mCurrentState);
		assert(top1 == top2 && "Lua stack is corrupt");
#endif

		return result;
	}

	ScriptObject* ScriptResult::getPointer() const
	{
		if(mCurrentState == NULL)
			return NULL;

#ifdef _DEBUG
		int top1 = lua_gettop(mCurrentState);
#endif

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mResultRef);

		ScriptObject* result = NULL;
		script_value<ScriptObject*>::pop(mCurrentState, result, -1);
		lua_pop(mCurrentState, 1);

#ifdef _DEBUG
		int top2 = lua_gettop(mCurrentState);
		assert(top1 == top2 && "Lua stack is corrupt");
#endif

		return result;
	}

	std::string ScriptResult::getString() const
	{
		if(mCurrentState == NULL)
			return NULL;

#ifdef _DEBUG
		int top1 = lua_gettop(mCurrentState);
#endif

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mResultRef);

		std::string result;
		script_value<std::string>::pop(mCurrentState, result, -1);
		lua_pop(mCurrentState, 1);

#ifdef _DEBUG
		int top2 = lua_gettop(mCurrentState);
		assert(top1 == top2 && "Lua stack is corrupt");
#endif

		return result;
	}

	bool ScriptResult::hasResult() const
	{
		if(mCurrentState == NULL)
			return false;
		
#ifdef _DEBUG
		int top1 = lua_gettop(mCurrentState);
#endif
		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mResultRef);
		bool isnil = lua_isnil(mCurrentState, -1);
		lua_pop(mCurrentState, 1);
		
#ifdef _DEBUG
		int top2 = lua_gettop(mCurrentState);
		assert(top1 == top2 && "Lua stack is corrupt");
#endif

		return isnil;
	}
}

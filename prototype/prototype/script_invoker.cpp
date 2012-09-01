#include "script_invoker.h"
#include <cassert>

namespace prototype
{
	ScriptInvoker::ScriptInvoker()
		: ScriptReference()
	{}

	ScriptInvoker::~ScriptInvoker()
	{}

	void ScriptInvoker::invoke(const char* method)
	{
#ifdef _DEBUG
		int top1 = lua_gettop(mCurrentState);
#endif
		if(!findAndPushMethod(method))
			return;

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		lua_pcall(mCurrentState, 1, 0, NULL);
		lua_pop(mCurrentState, 1);

#ifdef _DEBUG
		int currentStack = lua_gettop(mCurrentState);
		assert(top1 == currentStack && "The stack after the method call is corrupt");
#endif
	}

	bool ScriptInvoker::findAndPushMethod(const char* methodName)
	{
		if(methodName == NULL)
			return false;

		assert(mScriptRef != 0 && "You must register this instance before you can invoke any script methods on it");
				
		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		if(lua_istable(mCurrentState, -1))
		{
			lua_getfield(mCurrentState, -1, methodName);
			if(lua_isfunction(mCurrentState, -1)) {
				return true;
			}
			lua_pop(mCurrentState, 1);
		}
		lua_pop(mCurrentState, 1);
		return false;
	}

	bool ScriptInvoker::isMethodDefined(const char* methodName)
	{
		if(methodName == NULL)
			return false;

		assert(mScriptRef != 0 && "You must register this instance before you can invoke any script methods on it");

		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		if(lua_istable(mCurrentState, -1))
		{
			lua_getfield(mCurrentState, -1, methodName);
			if(lua_isfunction(mCurrentState, -1)) {
				lua_pop(mCurrentState, 2);
				return true;
			}
			lua_pop(mCurrentState, 1);
		}
		lua_pop(mCurrentState, 1);
		return false;
	}
}

#include "script_invoker.h"
#include <cassert>

namespace prototype
{
	ScriptInvoker::ScriptInvoker()
		: ScriptReference()
	{}

	ScriptInvoker::~ScriptInvoker()
	{}

	void ScriptInvoker::invokeMethod(const char* method)
	{
		if(!findAndPushMethod(method))
			return;

		lua_getref(mCurrentState, mScriptRef);
		lua_pcall(mCurrentState, 1, 0, NULL);
		lua_pop(mCurrentState, 1);
	}

	bool ScriptInvoker::findAndPushMethod(const char* methodName)
	{
		if(methodName == NULL)
			return false;

		assert(mScriptRef != 0 && "You must register this instance before you can invoke any script methods on it");
				
		lua_getref(mCurrentState, mScriptRef);
		if(lua_istable(mCurrentState, -1))
		{
			lua_getfield(mCurrentState, -1, methodName);
			if(lua_isfunction(mCurrentState, -1)) {
				lua_getref(mCurrentState, mScriptRef);
				return true;
			}
			lua_pop(mCurrentState, 1);
		}
		lua_pop(mCurrentState, 1);
		return false;
	}
}

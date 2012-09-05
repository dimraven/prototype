#include "script_reference.h"
#include "script_ptr.h"
#include <cassert>

namespace prototype
{
	ScriptReference::ScriptReference() : mScriptRef(0), mCurrentState(gLuaState)
	{
	}

	ScriptReference::~ScriptReference()
	{
		assert(mScriptRef == 0 && "Warning, you have deleted an instance without unregistering it");
	}

}

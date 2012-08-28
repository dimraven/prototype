#include "script_reference.h"
#include <cassert>

namespace prototype
{
	ScriptReference::ScriptReference() : mScriptRef(0), mCurrentState(NULL)
	{
	}

	ScriptReference::~ScriptReference()
	{
		assert(mScriptRef == 0 && "Warning, you have deleted an instance without unregistering it");
		assert(mCurrentState == NULL && "Warning, you have deleted an instance without unregistering it");
	}

}

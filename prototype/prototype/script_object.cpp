#include "script_object.h"

namespace prototype
{
	////////////////////////////////////////////////////////////////
	
	ClassDefinitionImpl<ScriptObject> ScriptObject::gClassDef("ScriptObject", NULL);

	ClassDefinition* ScriptObject::getClassDef() const
	{
		return &gClassDef;
	}

	ClassDefinitionImpl<ScriptObject>* ScriptObject::getStaticClassDef()
	{
		return &ScriptObject::gClassDef;
	}

	////////////////////////////////////////////////////////////////

	ScriptObject::ScriptObject()
		: ScriptInvoker(), mScriptObjectPtrLastEntry(NULL)
	{}

	ScriptObject::~ScriptObject()
	{
	}

	bool ScriptObject::registerObject()
	{
		assert(mScriptRef == 0 && "You are trying to register the same object twice");

		// Get the global lua state
		mScriptRef = getClassDef()->instantiate(mCurrentState, this);
		
		if(!onAdd())
		{
			unregisterObject();
			return false;
		}

		return true;
	}

	bool ScriptObject::registerObject(int refId)
	{
		assert(mScriptRef == 0 && "You are trying to register the same object twice");

		mScriptRef = refId;
		
		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		lua_pushstring(mCurrentState, "_instance");
		lua_pushlightuserdata(mCurrentState, this);
		lua_settable(mCurrentState, -3);
		
		lua_pop(mCurrentState, 1);

		if(!onAdd())
		{
			unregisterObject();
			return false;
		}

		return true;
	}

	void ScriptObject::unregisterObject()
	{
		assert(mScriptRef != 0 && "You are trying to unregister the same object twice");
		
		onRemove();
		
		// Set _instance to nil
		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		lua_pushstring(mCurrentState, "_instance");
		lua_pushnil(mCurrentState);
		lua_rawset(mCurrentState, -3);
		lua_pop(mCurrentState, 1);

		luaL_unref(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);

		mScriptRef = 0;

		releasePointers();
	}

	bool ScriptObject::onAdd()
	{
		invoke("onAdd");
		return true;
	}

	void ScriptObject::onRemove()
	{
		invoke("onRemove", 10);
	}
	
	void ScriptObject::detachPointer(ScriptObjectEntry* entry)
	{
		ScriptObjectEntry* prev = entry->prev;
		ScriptObjectEntry* next = entry->next;

		if(prev != NULL)
		{
			prev->next = next;
			if(next != NULL)
			{
				next->prev = prev;
			}

			if(entry == mScriptObjectPtrLastEntry) {
				mScriptObjectPtrLastEntry = entry->prev;
			}
		}
		else
		{
			if(next != NULL)
			{
				next->prev = NULL;
			}
		}

		free(entry);
	}

	ScriptObjectEntry* ScriptObject::attachPointer(ScriptObject** ptr)
	{
		if(mScriptObjectPtrLastEntry == NULL)
		{
			mScriptObjectPtrLastEntry = reinterpret_cast<ScriptObjectEntry*>(malloc(sizeof(ScriptObjectEntry)));
			memset(mScriptObjectPtrLastEntry, 0, sizeof(ScriptObjectEntry));
		}
		else
		{
			ScriptObjectEntry* next = reinterpret_cast<ScriptObjectEntry*>(malloc(sizeof(ScriptObjectEntry)));
			memset(next, 0, sizeof(ScriptObjectEntry));
			mScriptObjectPtrLastEntry->next = next;
			next->prev = mScriptObjectPtrLastEntry;
			mScriptObjectPtrLastEntry = next;
		}

		mScriptObjectPtrLastEntry->ptr = ptr;
		return mScriptObjectPtrLastEntry;
	}

	void ScriptObject::releasePointers()
	{
		if(mScriptObjectPtrLastEntry == NULL)
			return;

		ScriptObjectEntry* entry = mScriptObjectPtrLastEntry;
		while(entry != NULL) {
			ScriptObjectEntry* prev = entry->prev;

			ScriptObject** ptr = entry->ptr;
			*ptr = NULL;
			free(entry);

			entry = prev;
		}

		mScriptObjectPtrLastEntry = NULL;
	}

}

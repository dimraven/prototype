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
		: ScriptInvoker()
	{}

	ScriptObject::~ScriptObject()
	{
	}

	bool ScriptObject::registerObject()
	{
		assert(mScriptRef == 0 && "You are trying to register the same object twice");
		assert(mCurrentState == NULL && "You are trying to unregister the same object twice");

		mCurrentState = gLuaState;
		
		// Get the global lua state
		mScriptRef = getClassDef()->createScriptRepresentation(mCurrentState);
		
		// Set _instacne 
		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		//lua_getref(mCurrentState, mScriptRef);
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

	bool ScriptObject::registerObject(int refId)
	{
		assert(mScriptRef == 0 && "You are trying to register the same object twice");
		assert(mCurrentState == NULL && "You are trying to unregister the same object twice");

		mScriptRef = refId;
		mCurrentState = gLuaState;
		
		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		//lua_getref(mCurrentState, mScriptRef);
		lua_pushstring(mCurrentState, "_instance");
		lua_pushlightuserdata(mCurrentState, this);
		lua_settable(mCurrentState, -3);
		
		// Assign the _className to this classes name. Used for type validation when receiving
		// this object from script.
		lua_pushstring(mCurrentState, "_className");
		lua_pushstring(mCurrentState, getClassDef()->getClassName().c_str());
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
		assert(mCurrentState != NULL && "You are trying to unregister the same object twice");

		onRemove();
		
		// Set _instance to nil
		lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		//lua_getref(mCurrentState, mScriptRef);
		lua_pushstring(mCurrentState, "_instance");
		lua_pushnil(mCurrentState);
		lua_rawset(mCurrentState, -3);
		lua_pop(mCurrentState, 1);

		luaL_unref(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
		//lua_unref(mCurrentState, mScriptRef);

		mScriptRef = 0;
		mCurrentState = NULL;

		
		std::list<ScriptObject**>::iterator it = mSafePointerReferences.begin();
		std::list<ScriptObject**>::iterator end = mSafePointerReferences.end();
		for(; it != end; ++it) {
			ScriptObject** ptr = *it;
			*ptr = NULL;
		}
		mSafePointerReferences.clear();
	}

	bool ScriptObject::onAdd()
	{
		invokeMethod("onAdd");
		return true;
	}

	void ScriptObject::onRemove()
	{
		invokeMethod("onDelete", 10);
	}

	void ScriptObject::unreferencePointer(ScriptObject** ptr)
	{
		std::list<ScriptObject**>::iterator it = mSafePointerReferences.begin();
		std::list<ScriptObject**>::iterator end = mSafePointerReferences.end();
		for(; it != end; ++it) {
			if( (*it) == ptr ) {
				mSafePointerReferences.erase(it);
				return;
			}
		}
	}

	void ScriptObject::referencePointer(ScriptObject** ptr)
	{
		mSafePointerReferences.push_back(ptr);
	}
}

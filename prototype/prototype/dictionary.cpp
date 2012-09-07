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

	DictionaryIterator Dictionary::getIterator() const
	{
		return DictionaryIterator(mCurrentState, mScriptRef);
	}

	DictionaryIterator::DictionaryIterator()
		: mScriptRef(0), mCurrentState(NULL), mNumPopsRequired(0)
	{
	}
	
	DictionaryIterator::DictionaryIterator(lua_State* L, int scriptRef)
		: mScriptRef(scriptRef), mCurrentState(L), mNumPopsRequired(0)
	{
		if(mScriptRef > 0)
		{
			lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
			lua_pushnil(mCurrentState);
			mNumPopsRequired = 2;
		}
	}

	DictionaryIterator::DictionaryIterator(const DictionaryIterator& it)
		: mScriptRef(it.mScriptRef), mCurrentState(it.mCurrentState), mNumPopsRequired(0)
	{
		if(mScriptRef > 0)
		{
			lua_rawgeti(mCurrentState, LUA_REGISTRYINDEX, mScriptRef);
			lua_pushnil(mCurrentState);	
			mNumPopsRequired = 2;
		}
	}

	DictionaryIterator::~DictionaryIterator()
	{
		if(mScriptRef > 0)
		{
			lua_pop(mCurrentState, mNumPopsRequired);
			mScriptRef = 0;
		}
	}

	bool DictionaryIterator::hasNext()
	{
		if(mScriptRef <= 0)
			return false;

		if(mNumPopsRequired > 2)
			lua_pop(mCurrentState, 1);
		
		bool next = lua_next(mCurrentState, -2) != 0;
		if(next)
			mNumPopsRequired++;

		return next;
	}

	std::string DictionaryIterator::getKey() const
	{
		assert(mScriptRef > 0 && "This iterator instance is corrupter. Are you sure that hasNext() returned true?");
		std::string key = lua_tostring(mCurrentState, -2);
		return key;
	}

	std::string DictionaryIterator::getString()
	{
		assert(mScriptRef > 0 && "This iterator instance is corrupter. Are you sure that hasNext() returned true?");
		std::string val = lua_tostring(mCurrentState, -1);
		lua_pop(mCurrentState, 1);
		mNumPopsRequired--;
		return val;
	}

	double DictionaryIterator::getDouble()
	{
		assert(mScriptRef > 0 && "This iterator instance is corrupter. Are you sure that hasNext() returned true?");
		double val = lua_tonumber(mCurrentState, -1);
		lua_pop(mCurrentState, 1);
		mNumPopsRequired--;
		return val;
	}

	float DictionaryIterator::getFloat()
	{
		assert(mScriptRef > 0 && "This iterator instance is corrupter. Are you sure that hasNext() returned true?");
		float val = (float)lua_tonumber(mCurrentState, -1);
		lua_pop(mCurrentState, 1);
		mNumPopsRequired--;
		return val;
	}

	int DictionaryIterator::getInt()
	{
		assert(mScriptRef > 0 && "This iterator instance is corrupter. Are you sure that hasNext() returned true?");
		int val = lua_tointeger(mCurrentState, -1);
		lua_pop(mCurrentState, 1);
		mNumPopsRequired--;
		return val;
	}

	bool DictionaryIterator::getBool()
	{
		assert(mScriptRef > 0 && "This iterator instance is corrupter. Are you sure that hasNext() returned true?");
		bool val = lua_toboolean(mCurrentState, -1) != 0;
		lua_pop(mCurrentState, 1);
		mNumPopsRequired--;
		return val;
	}

	ScriptObject* DictionaryIterator::getPointer()
	{
		assert(mScriptRef > 0 && "This iterator instance is corrupter. Are you sure that hasNext() returned true?");
		ScriptObject* ptr = NULL;
		script_value<ScriptObject*>::pop(mCurrentState, ptr);
		mNumPopsRequired--;
		return ptr;
	}

	Dictionary DictionaryIterator::getDictionary()
	{
		assert(mScriptRef > 0 && "This iterator instance is corrupter. Are you sure that hasNext() returned true?");
		Dictionary dict;
		script_value<Dictionary>::pop(mCurrentState, dict);
		mNumPopsRequired--;
		return dict;
	}
}

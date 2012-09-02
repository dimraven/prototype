#ifndef _PROTOTYPE_DICTIONARY_H_
#define _PROTOTYPE_DICTIONARY_H_

#include <string>

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	class ScriptObject;

	//
	// Class which represents a script dictionary. Example:
	// {@code
	//	
	//	Dictionary dict = evaluateStringAndGet("return { value1="Hello World", value2=ScriptObject(), value3={value1=10.0}}");
	//	dict.getString("value1"); // == "Hello World"
	//	dict.getPointer("value2"); // == ScriptObject*
	//	dict.getDictionary("value3").getDouble("value1"); // == 10.0
	// }
	class Dictionary
	{
	public:
		Dictionary();
		Dictionary(lua_State* L, int scriptRef);
		Dictionary(const Dictionary& other);
		~Dictionary();

		//
		// @return A string representation of the value inside this dictionary based on the supplied key.
		//	//	//	If value isn't found or isn't convertable then returns "".
		std::string getString(const char* key) const;
		
		//
		// @return A double value from inside this dictionary based on the supplied key.
		//	//	If value isn't found or isn't convertable then returns "0.0".
		double getDouble(const char* key) const;

		//
		// @return A float value from inside this dictionary based on the supplied key.
		//	If value isn't found or isn't convertable then returns "0.0f".
		float getFloat(const char* key) const;
		
		//
		// @return A boolean value from inside this dictionary based on the supplied key. 
		//	If value isn't found or isn't convertable then returns "false".
		bool getBool(const char* key) const;
		
		//
		// @return A ScriptObject pointer from inside this dictionary based on the supplied key. 
		//	If value isn't found or isn't convertable then returns NULL.
		ScriptObject* getPointer(const char* key) const;
		
		//
		// @return A ScriptObject pointer from inside this dictionary based on the supplied key. 
		//	If value isn't found or isn't convertable then returns empty dictionary.
		Dictionary getDictionary(const char* key) const;

		//
		// @return The associated script-table reference ID. This is unique between all instances as long as it's alive.
		//		It might be recycled when released.
		inline int getId() const {
			return mScriptRef;
		}

	private:
		int mScriptRef;
		lua_State* mCurrentState;
	};

}

#endif

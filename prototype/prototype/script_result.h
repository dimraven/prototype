#ifndef _PROTOTYPE_SCRIPT_RESULT_H_
#define _PROTOTYPE_SCRIPT_RESULT_H_

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

	class ScriptResult
	{
	public:
		ScriptResult();
		ScriptResult(lua_State* L, int ref);
		ScriptResult(const ScriptResult& other);
		~ScriptResult();

		int getInt(int defaultVal = 0) const;

		bool getBool(bool defaultVal = false) const;

		float getFloat(float defaultVal = 0.0f) const;

		//
		// @param defaultVal The default value if the result type isn't a double (or convertable to double).
		// @return The double value; If no value is found then the default value is returned.
		double getDouble(double defaultVal = 0.0) const;

		//
		// @return A script object pointer; NULL if no pointer was found
		ScriptObject* getPointer() const;

		//
		// Retrieves a string value as the result if the result type is a string type or if it's convertable to string.
		// @return A string value; Empty string if no string was found.
		std::string getString() const;

		//
		// @return TRUE if the result contains anything; FALSE otherwise
		bool hasResult() const;

	private:
		int mResultRef;
		lua_State* mCurrentState;
	};

}

#endif

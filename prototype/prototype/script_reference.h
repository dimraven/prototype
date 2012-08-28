#ifndef _PROTOTYPE_SCRIPT_REFERENCE_H_
#define _PROTOTYPE_SCRIPT_REFERENCE_H_

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	//
	// Class containing the neccessary information for it to be able to connect to a script table.
	class ScriptReference
	{
	public:
		ScriptReference();
		virtual ~ScriptReference();

		//
		// @return The ID which connects this instance to a script-represented version of this class. 
		//		0 if it isn't connected (i.e. it isn't registered).
		inline int getScriptRef() const {
			return mScriptRef;
		}

		//
		// @return The state associated with this script reference object.
		inline lua_State* getCurrentState() const {
			return mCurrentState;
		}

	protected:
		int mScriptRef;
		lua_State* mCurrentState;
	};

}

#endif

#ifndef _PROTOTYPE_SCRIPT_H_
#define _PROTOTYPE_SCRIPT_H_

#include "class_definition.h"

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	extern lua_State* gLuaState;

	//
	//
	class Script
	{
	public:
		//
		// Initializes the script engine.
		static void initialize();

		//
		// Releases the 
		static void release();

		//
		// Load and execute a script file.
		// @param pathToFile the path to the script file.
		static void loadFile(const char* pathToFile);

		//
		// Function used to bind a class to the script 
		template<class Clazz>
		static ClassDefinitionImpl<Clazz>& bind()
		{
			// If an error occures here then make sure to make it integrateable using the defines:
			// DEFINE_SCRIPT_CLASS and IMPLEMENT_SCRIPT_CLASS
			Clazz::getStaticClassDef()->registerClass(gLuaState);
			return *Clazz::getStaticClassDef();
		}

		//
		// Binds a function which has no parameters
		static void bind(const char *funcName, void (*funcPtr)());

		template<typename P1>
		static void bind(const char* funcName, void (*funcPtr)(P1))
		{
		}
	};

}

#endif

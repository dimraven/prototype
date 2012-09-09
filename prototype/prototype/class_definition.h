#ifndef _PROTOTYPE_CLASS_DEFINITION_H_
#define _PROTOTYPE_CLASS_DEFINITION_H_

#include <map>
#include <string>
#include <cassert>
#include "wrapper_for_script_objects.h"
#include "wrapper_for_classes.h"
#include "wrapper_for_methods.h"

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	class ScriptObject;


	class ClassDefinition
	{
	public:
		//
		// Creates a script table wrapper based on a specific class definition.
		// @return A reference ID used to identify the table on the script-side.
		virtual int instantiate(lua_State* L, ScriptObject* ptr) = 0;
		
		//
		// @return The name of the class
		virtual const std::string& getClassName() const = 0;

		//
		// @return The name of the metatable
		virtual const std::string& getMetaTableName() const = 0;

		//
		// You can use this method to gather all the methods bound to this class. This
		// is primarily used when handling inheritance between scriptable objects.
		//
		// @return a list with all the methods bound to this class definition.
		virtual std::map<std::string, method_pointer_wrapper*> getMethods() const = 0;
	};

	template<class Clazz>
	class ClassDefinitionImpl : public ClassDefinition
	{
	public:
		ClassDefinitionImpl(const char* className, const ClassDefinition* parent)
			: mClassName(className), mParent(parent)
		{
			mMetaTableName = std::string("Prototype.") + mClassName;
		}

		virtual ~ClassDefinitionImpl()
		{
		}

		virtual int instantiate(lua_State* L, ScriptObject* ptr)
		{
			int scriptRef = 0;
#ifdef _DEBUG
			int top3 = lua_gettop(L);
#endif
			// Create a new instance and set the variable _instance = <this>;
			lua_newtable(L); 
			scriptRef = luaL_ref(L, LUA_REGISTRYINDEX);
		
			
			lua_rawgeti(L, LUA_REGISTRYINDEX, scriptRef);
			//lua_getref(L, scriptRef);
			lua_pushvalue(L, -1);
			lua_setfield(L, -2, "__index");
			luaL_getmetatable(L, mMetaTableName.c_str());
			lua_setmetatable(L, -2);

			// Assigns the value: _instance to this object
			lua_pushstring(L, "_instance");
			lua_pushlightuserdata(L, ptr);
			lua_settable(L, -3);

			lua_pop(L, 1);
#ifdef _DEBUG
			int top4 = lua_gettop(L);
			assert(top3 == top4 && "Could not create lua table. Corrupted stack");
#endif
			return scriptRef;
		}

		virtual const std::string& getClassName() const
		{
			return mClassName;
		}

		virtual const std::string& getMetaTableName() const
		{
			return mMetaTableName;
		}

		virtual std::map<std::string, method_pointer_wrapper*> getMethods() const
		{
			return mMethods;
		}
		
		ClassDefinitionImpl<Clazz>& addMethod(const char* methodName, void (Clazz::*methodPtr)())
		{
			method_pointer_wrapper_void_0args<Clazz>* wrapper = 
				new method_pointer_wrapper_void_0args<Clazz>();
			wrapper->methodPtr = methodPtr;
			wrapper->func = &lua_method_void_0args<Clazz>;

			addMethod(mState, methodName, wrapper);
			return *this;
		}

		template<typename P1>
		ClassDefinitionImpl<Clazz>& addMethod(const char* methodName, void (Clazz::*methodPtr)(P1))
		{
			method_pointer_wrapper_void_1args<Clazz, P1>* wrapper = 
				new method_pointer_wrapper_void_1args<Clazz, P1>();
			wrapper->methodPtr = methodPtr;
			wrapper->func = &lua_method_void_1args<Clazz, P1>;

			addMethod(mState, methodName, wrapper);
			return *this;
		}

		template<typename P1, typename P2>
		ClassDefinitionImpl<Clazz>& addMethod(const char* methodName, void (Clazz::*methodPtr)(P1, P2))
		{
			method_pointer_wrapper_void_2args<Clazz, P1, P2>* wrapper = 
				new method_pointer_wrapper_void_2args<Clazz, P1, P2>();
			wrapper->methodPtr = methodPtr;
			wrapper->func = &lua_method_void_2args<Clazz, P1, P2>;
			
			addMethod(mState, methodName, wrapper);
			return *this;
		}
		
		template<typename P1, typename P2, typename P3>
		ClassDefinitionImpl<Clazz>& addMethod(const char* methodName, void (Clazz::*methodPtr)(P1, P2, P3))
		{
			method_pointer_wrapper_void_3args<Clazz, P1, P2, P3>* wrapper = 
				new method_pointer_wrapper_void_3args<Clazz, P1, P2, P3>();
			wrapper->methodPtr = methodPtr;
			wrapper->func = &lua_method_void_3args<Clazz, P1, P2, P3>;
			
			addMethod(mState, methodName, wrapper);
			return *this;
		}
		
		template<typename P1, typename P2, typename P3, typename P4>
		ClassDefinitionImpl<Clazz>& addMethod(const char* methodName, void (Clazz::*methodPtr)(P1, P2, P3, P4))
		{
			method_pointer_wrapper_void_4args<Clazz, P1, P2, P3, P4>* wrapper = 
				new method_pointer_wrapper_void_4args<Clazz, P1, P2, P3, P4>();
			wrapper->methodPtr = methodPtr;
			wrapper->func = &lua_method_void_4args<Clazz, P1, P2, P3>;
			
			addMethod(mState, methodName, wrapper);
			return *this;
		}

		// 

		template<typename R>
		ClassDefinitionImpl<Clazz>& addMethod(const char* methodName, R (Clazz::*methodPtr)())
		{
			method_pointer_wrapper_R_0args<Clazz, R>* wrapper = 
				new method_pointer_wrapper_R_0args<Clazz, R>();
			wrapper->methodPtr = methodPtr;
			wrapper->func = &lua_method_R_0args<Clazz, R>;

			addMethod(mState, methodName, wrapper);
			return *this;
		}

		template<typename R, typename P1>
		ClassDefinitionImpl<Clazz>& addMethod(const char* methodName, R (Clazz::*methodPtr)(P1))
		{
			method_pointer_wrapper_R_1args<Clazz, R, P1>* wrapper = 
				new method_pointer_wrapper_R_1args<Clazz, R, P1>();
			wrapper->methodPtr = methodPtr;
			wrapper->func = &lua_method_R_1args<Clazz, R, P1>;

			addMethod(mState, methodName, wrapper);
			return *this;
		}

		template<typename R, typename P1, typename P2>
		ClassDefinitionImpl<Clazz>& addMethod(const char* methodName, R (Clazz::*methodPtr)(P1, P2))
		{
			method_pointer_wrapper_R_2args<Clazz, R, P1, P2>* wrapper = 
				new method_pointer_wrapper_R_2args<Clazz, R, P1, P2>();
			wrapper->methodPtr = methodPtr;
			wrapper->func = &lua_method_R_2args<Clazz, R, P1, P2>;
			
			addMethod(mState, methodName, wrapper);
			return *this;
		}
		
		template<typename R, typename P1, typename P2, typename P3>
		ClassDefinitionImpl<Clazz>& addMethod(const char* methodName, R (Clazz::*methodPtr)(P1, P2, P3))
		{
			method_pointer_wrapper_R_3args<Clazz, R, P1, P2, P3>* wrapper = 
				new method_pointer_wrapper_R_3args<Clazz, R, P1, P2, P3>();
			wrapper->methodPtr = methodPtr;
			wrapper->func = &lua_method_R_3args<Clazz, R, P1, P2, P3>;
			
			addMethod(mState, methodName, wrapper);
			return *this;
		}
		
		template<typename R, typename P1, typename P2, typename P3, typename P4>
		ClassDefinitionImpl<Clazz>& addMethod(const char* methodName, R (Clazz::*methodPtr)(P1, P2, P3, P4))
		{
			method_pointer_wrapper_R_4args<Clazz, R, P1, P2, P3, P4>* wrapper = 
				new method_pointer_wrapper_R_4args<Clazz, R, P1, P2, P3, P4>();
			wrapper->methodPtr = methodPtr;
			wrapper->func = &lua_method_R_4args<Clazz, R, P1, P2, P3>;
			
			addMethod(mState, methodName, wrapper);
			return *this;
		}

		//
		// Method called when registering this class definition, exluding the methods - those are added using the
		// methods "addMethod".
		void registerClass(lua_State* L)
		{
			mState = L;

#ifdef _DEBUG
			int top = lua_gettop(L);
#endif
			luaL_Reg requiredFuncs[] = {
				{ "__call", lua_ScriptObject_call<Clazz> },
				{ "init", lua_ScriptObject_init<Clazz> },
				{ NULL, NULL }
			};
			
			luaL_newmetatable(L, mMetaTableName.c_str());
			lua_pushvalue(L, -1);
			lua_setfield(L, -2, "__index");
			lua_pop(L, 1);

			luaL_getmetatable(L, mMetaTableName.c_str());
			luaL_setfuncs(L, requiredFuncs, 0);
			lua_pop(L, 1);

			lua_newtable(L);
			luaL_getmetatable(L, mMetaTableName.c_str());
			lua_setmetatable(L, -2 );
			luaL_setfuncs(L, requiredFuncs, 0);
			lua_setglobal(L, mClassName.c_str());

			// Inheritance?
			if(mParent != NULL) {
				std::map<std::string, method_pointer_wrapper*> methods = mParent->getMethods();
				std::map<std::string, method_pointer_wrapper*>::iterator it = methods.begin();
				std::map<std::string, method_pointer_wrapper*>::iterator end = methods.end();
				for(; it != end; ++it) {
					addMethod(L, it->first.c_str(), it->second);
				}

				// The "funcs" map does now contain names and function pointers to the rest of the functions
				luaL_getmetatable(L, mMetaTableName.c_str());
				lua_pop(L, 1);
			}

#ifdef _DEBUG
			int top2 = lua_gettop(L);
			assert(top == top2 && "Could not create lua table. Corrupted stack");
#endif
		}

	private:
		void addMethod(lua_State* L, const char* methodName, method_pointer_wrapper* wrapper)
		{
			// Save the method pointer data in-case of inheritance.
			mMethods.insert(std::make_pair(std::string(methodName), wrapper));

#ifdef _DEBUG
			int top = lua_gettop(L);
#endif
			luaL_getmetatable(L, mMetaTableName.c_str());
			lua_pushlightuserdata(L, wrapper);
			lua_pushstring(L, methodName);
			lua_pushcclosure(L, wrapper->func, 2);
			lua_setfield(L, -2, methodName);
			lua_pop(L, 1);

			lua_getglobal(L, mClassName.c_str());
			lua_pushlightuserdata(L, wrapper);
			lua_pushstring(L, methodName);
			lua_pushcclosure(L, wrapper->func, 2);
			lua_setfield(L, -2, methodName);
			lua_pop(L, 1);

#ifdef _DEBUG
			int top2 = lua_gettop(L);
			assert(top == top2 && "Could not create lua table. Corrupted stack");
#endif
		}

	private:
		std::string mClassName;
		const ClassDefinition* mParent;
		std::string mMetaTableName;
		std::map<std::string, method_pointer_wrapper*> mMethods;
		lua_State* mState;
	};
}

#ifndef IMPLEMENT_SCRIPT_CLASS
#define IMPLEMENT_SCRIPT_CLASS(Clazz, Parent) \
	prototype::ClassDefinition* Clazz::getClassDef() const { return &Clazz::gClassDef; } \
	prototype::ClassDefinitionImpl<Clazz>* Clazz::getStaticClassDef() { return &Clazz::gClassDef; } \
	prototype::ClassDefinitionImpl<Clazz> Clazz::gClassDef(#Clazz, Parent::getStaticClassDef());
#endif

#ifndef IMPLEMENT_SCRIPT_CLASS_WITH_NAME
#define IMPLEMENT_SCRIPT_CLASS_WITH_NAME(Clazz, ClazzName, Parent) \
	prototype::ClassDefinition* Clazz::getClassDef() const { return &Clazz::gClassDef; } \
	prototype::ClassDefinitionImpl<Clazz>* Clazz::getStaticClassDef() { return &Clazz::gClassDef; } \
	prototype::ClassDefinitionImpl<Clazz> Clazz::gClassDef(ClazzName, Parent::getStaticClassDef());
#endif

#ifndef DEFINE_SCRIPT_CLASS
#define DEFINE_SCRIPT_CLASS(Clazz) \
	virtual prototype::ClassDefinition* getClassDef() const; \
	static prototype::ClassDefinitionImpl<Clazz>* getStaticClassDef(); \
	static prototype::ClassDefinitionImpl<Clazz> gClassDef;
#endif

#endif

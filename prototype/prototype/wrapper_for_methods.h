#ifndef _PROTOTYPE_WRAPPER_FOR_METHODS_H_
#define _PROTOTYPE_WRAPPER_FOR_METHODS_H_

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}

namespace prototype
{
	class method_pointer_wrapper
	{
	public:
		lua_CFunction func;
	};

	// Wrapper templates for methods which does NOT return something!

	template<class Clazz>
	class method_pointer_wrapper_void_0args : public method_pointer_wrapper
	{
	public:
		void (Clazz::*methodPtr)(void);
	};
	
	template<class Clazz, typename P1>
	class method_pointer_wrapper_void_1args : public method_pointer_wrapper
	{
	public:
		void (Clazz::*methodPtr)(P1);
	};
	
	template<class Clazz, typename P1, typename P2>
	class method_pointer_wrapper_void_2args : public method_pointer_wrapper
	{
	public:
		void (Clazz::*methodPtr)(P1, P2);
	};

	template<class Clazz, typename P1, typename P2, typename P3>
	class method_pointer_wrapper_void_3args : public method_pointer_wrapper
	{
	public:
		void (Clazz::*methodPtr)(P1, P2, P3);
	};
	
	template<class Clazz, typename P1, typename P2, typename P3, typename P4>
	class method_pointer_wrapper_void_4args : public method_pointer_wrapper
	{
	public:
		void (Clazz::*methodPtr)(P1, P2, P3, P4);
	};

	template<class Clazz, typename R>
	class method_pointer_wrapper_R_0args : public method_pointer_wrapper
	{
	public:
		R (Clazz::*methodPtr)(void);
	};
	
	template<class Clazz, typename R, typename P1>
	class method_pointer_wrapper_R_1args : public method_pointer_wrapper
	{
	public:
		R (Clazz::*methodPtr)(P1);
	};
	
	template<class Clazz, typename R, typename P1, typename P2>
	class method_pointer_wrapper_R_2args : public method_pointer_wrapper
	{
	public:
		R (Clazz::*methodPtr)(P1, P2);
	};

	template<class Clazz, typename R, typename P1, typename P2, typename P3>
	class method_pointer_wrapper_R_3args : public method_pointer_wrapper
	{
	public:
		R (Clazz::*methodPtr)(P1, P2, P3);
	};
	
	template<class Clazz, typename R, typename P1, typename P2, typename P3, typename P4>
	class method_pointer_wrapper_R_4args : public method_pointer_wrapper
	{
	public:
		R (Clazz::*methodPtr)(P1, P2, P3, P4);
	};
}

#endif

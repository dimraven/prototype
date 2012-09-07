#include <iostream>
#include <stdio.h>
#include <dos.h>

#include <prototype/script.h>
#include <prototype/script_object.h>
using namespace prototype;

int cMax(int val1, int val2)
{
	return val1 > val2 ? val1 : val2;
}

float cRound(float val1, float val2)
{
	return (val1 + val2) * 0.5f;
}

void printDictionary(Dictionary dict)
{
	DictionaryIterator it = dict.getIterator();
	while(it.hasNext())
	{
		std::string key = it.getKey();
		std::string val = it.getString();
		
		std::cout << key.c_str() << " = " << val.c_str() << std::endl;
	}
}

class BaseClass : public ScriptObject
{
public:
	DEFINE_SCRIPT_CLASS(BaseClass);

public:
	BaseClass() : ScriptObject() {
	}

	virtual ~BaseClass() {
	}
	
	virtual void sayHello() {
		std::cout << "Hello from BaseClass" << std::endl;
	}

	virtual void identify(BaseClass* ptr) {
		invoke("onIdentified", ptr);
	}

};
IMPLEMENT_SCRIPT_CLASS(BaseClass, ScriptObject);

class SubClass1 : public BaseClass
{
public:
	DEFINE_SCRIPT_CLASS(SubClass1);

public:
	SubClass1() : BaseClass() {
	}

	virtual ~SubClass1() {
	}

	virtual void sayHello() {
		std::cout << "Hello from SubClass1" << std::endl;
	}
	
	virtual void identify(BaseClass* ptr) {
		BaseClass::identify(ptr);
		std::cout << "SubClass1 does nothing with this instance" << std::endl;
	}
};
IMPLEMENT_SCRIPT_CLASS(SubClass1, BaseClass);

class SubClass2 : public BaseClass
{
public:
	DEFINE_SCRIPT_CLASS(SubClass2);

public:
	SubClass2() : BaseClass() {
	}

	virtual ~SubClass2() {
	}

	virtual void sayHello() {
		std::cout << "Hello from SubClass2" << std::endl;
	}
	
	virtual void identify(BaseClass* ptr) {
		BaseClass::identify(ptr);
		std::cout << "SubClass2 does nothing with this instance" << std::endl;
	}
};
IMPLEMENT_SCRIPT_CLASS(SubClass2, BaseClass);

void tryCallingMethodWithBaseClass(BaseClass* ptr)
{
	std::cout << "Call to tryCallingMethodWithBaseClass was successful" << std::endl;
}

void tryCallingMethodWithSubClass1(SubClass1* ptr)
{
	std::cout << "Call to tryCallingMethodWithSubClass1 was successful" << std::endl;
}

int main()
{
	// Initialize the script engine
	Script::initialize();

	// 1. Bind functions
	Script::bind("cMax", &cMax);
	Script::bind("cRound", &cRound);
	Script::bind("printDictionary", &printDictionary);
	Script::bind("tryCallingMethodWithBaseClass", &tryCallingMethodWithBaseClass);
	Script::bind("tryCallingMethodWithSubClass1", &tryCallingMethodWithSubClass1);

	// 3. Bind classes and methods
	Script::bind<BaseClass>()
		.addMethod("sayHello", &BaseClass::sayHello)
		.addMethod("identify", &BaseClass::identify);

	// 4. Bind inherited class. Example where we can re-use bound methods from the parent class.
	Script::bind<SubClass1>();
	Script::bind<SubClass2>();
	
	// Load and execute the lua main file
	Script::loadFile("main.lua");

	// Release all resources
	Script::release();

	std::cout << "Press [ENTER] to exit";
	std::cin.get();
	return 0;
}
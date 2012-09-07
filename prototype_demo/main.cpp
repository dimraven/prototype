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
};
IMPLEMENT_SCRIPT_CLASS(SubClass1, BaseClass);

int main()
{
	// 1. Initialize the script engine
	Script::initialize();

	// 2. Bind functions
	Script::bind("cMax", &cMax);
	Script::bind("cRound", &cRound);
	Script::bind("printDictionary", &printDictionary);

	// 3. Bind classes and methods
	Script::bind<BaseClass>()
		.addMethod("sayHello", &BaseClass::sayHello);
	Script::bind<SubClass1>();
	
	// 3. Load and execute the lua main file
	Script::loadFile("main.lua");

	// 4. Release all resources
	Script::release();

	return 0;
}
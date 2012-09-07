require "class"

print("==== Example using C++ functions ======")
print(cMax(10, 20))
print(cRound(20.0, 10.0))
print("")

print("==== Example using Dictionary iterators =====")
print("Note that most values are convertable to string, but")
print("not tables for example, lua_tostring returns NULL in those cases")
printDictionary({
	key1 = "value1",
	key2 = 10,
	key3 = 500.21,
})
print("")

print("==== Example using C++ bound classes with inheritance ====")
local instance1 = BaseClass()
instance1:sayHello()

local instance2 = SubClass1()
instance2:sayHello()

instance1:identify(instance1)
instance1:identify(instance2)
instance2:identify(instance1)
instance2:identify(instance2)

print("")
print("==== Example overriding C++ classes using Lua")
LuaClass = class(SubClass1, function(self)
	SubClass1.init(self)
end)

function LuaClass:onAdd()
	print("LuaClass - Method called when class is registered (instantiated)")
end

function LuaClass:onIdentified(ptr)
	print("LuaClass containing the following item: " .. ptr._instance)
end

function LuaClass:identify(ptr)
	print("LuaClass has overridden the identify method")
	SubClass1.identify(ptr, self)
end

local instance3 = LuaClass()
instance3:sayHello()
instance3:identify(instance2)

print("")
print("==== Example calling C++ functions with ScriptObject pointers ====")
tryCallingMethodWithBaseClass(instance1)
tryCallingMethodWithBaseClass(instance2)
tryCallingMethodWithSubClass1(instance1)
tryCallingMethodWithSubClass1(instance2)

local instance4 = SubClass2()
tryCallingMethodWithSubClass1(instance4)

print("")
print("==== Example calling C++ functions with classes inherited from Script ====")
tryCallingMethodWithSubClass1(instance3)

print("")
print("==== Example with trying to call functions with deleted pointers ====")
delete(instance1)
instance1:sayHello()
tryCallingMethodWithSubClass1(instance1)
prototype
=========
A library for prototyping c++ class using Lua (from Lua's point of view).

### Installation Notes ###

The installation notes and source projects are only available for Windows and for Visual Studio 2010 at the moment.
More will come soon (I've planned on making support for Dev-C++ and probably xcode). 

The script engine requires Lua 5.2.1. Read lib/lua/README.txt for information about this.
The demo application requires GLFW (A OpenGL wrapper library). Read lib/glfw/README.txt for information abou this.

### What is prototype ###

Although the name can be "slightly" missleading, it's purpose is straight on. The purpose of this library
is to enable the developer to prototype and extend exposed c++ class methods using the scripting language: Lua.

I've planned on using this library for a game engine that i've planned on developing layer on. Integration with
a scripting language is of course required when doing this. This project is in reality a self-learning project 
for myself so that I can learn how the Lua API works, but if some other developer can use this or learn something from
this then that would be awesome.

Note that this library doens't give you the power of replacing pure c++ classes and methods. What it does is
that it give you the power of extending methods "invoked" using a supplied interface (No - it does not solve the world-hunger problem). 
It gives us power of rapid development before the optimization stage (where we move our code from script to complied code) when developing a game.

### Features ###

* Unified interface for binding classes, methods and functions
* Inherit exposed C++ methods.
* Invokation of scripted methods.
* Support for extending exposed C++ classes with Script classes.
* Safe pointers

### Upcomming features ###

* Remote debugging 
* Replace std::list with memory_pool allocated linked list implementation for faster notification on deleted instances.

### Demo application ###

The project **prototype_demo** demonstrates how to use the following features:

* Binding of C/C++ functions.
* Binding of C++ classes with inheritance
* Creating new "classes" from script by inheriting C++ bound classes.
* Overloading bound C++ methods from script
* Handling dictionaries and iterators
* Error handling when trying to call deleted objects
* Error handling when trying to call functions with bad ScriptObject* parameters.

### Credits ###

http://www.lua.org - The Programming Language Lua.
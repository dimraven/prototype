#include <iostream>
#include <stdio.h>
#include <dos.h>

#include <prototype/script.h>
using namespace prototype;

#include "game.h"
#include "game_object.h"
#include "game_window.h"
#include "behaviour.h"

int main()
{
	// 1. Initialize the script engine
	Script::initialize();

	// 2. Bind our C++ classes
	Script::bind<Game>();
	Script::bind<GameWindow>()
		.addMethod("open", &GameWindow::open)
		.addMethod("close", &GameWindow::close);
	Script::bind<DrawableObject>();
	Script::bind<GameObject>()
		.addMethod("addBehaviour", &GameObject::addBehaviour)
		.addMethod("removeBehaviour", &GameObject::removeBehaviour);
	Script::bind<Behaviour>()
		.addMethod("getOwner", &Behaviour::getOwner);

	// 3. Load and execute the lua main file
	Script::loadFile("main.lua");

	// 4. Release all resources
	Script::release();

	return 0;
}
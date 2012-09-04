#include <iostream>
#include <stdio.h>
#include <dos.h>

#include <prototype/script.h>
using namespace prototype;

#include "game.h"
#include "game_object.h"
#include "game_window.h"
#include "behaviour.h"
#include "scene_definition.h"

int cRoundf(int val1, float val2)
{
	float res = (float)val1 + val2;
	return (int)(res + 0.5f);
}

void printDictionary(Dictionary dict)
{
	std::cout << "value1 = " << dict.getString("value1").c_str() << std::endl;
	std::cout << "value1 = " << dict.getInt("value1") << std::endl;
	std::cout << "value2 = " << dict.getInt("value2") << std::endl;
	std::cout << "value2 = " << dict.getFloat("value2") << std::endl;

}

int main()
{
	// 1. Initialize the script engine
	Script::initialize();

	// 2. Bind our C++ classes
	Script::bind<Game>()
		.addMethod("isRunning", &Game::isRunning);
	Script::bind<GameWindow>()
		.addMethod("open", &GameWindow::open)
		.addMethod("close", &GameWindow::close);
	Script::bind<DrawableObject>()
		.addMethod("setMetaData", &DrawableObject::setMetaData)
		.addMethod("addToScene", &DrawableObject::addToScene)
		.addMethod("removeFromScene", &DrawableObject::removeFromScene);
	Script::bind<GameObject>()
		.addMethod("addBehaviour", &GameObject::addBehaviour)
		.addMethod("removeBehaviour", &GameObject::removeBehaviour);
	Script::bind<Behaviour>()
		.addMethod("getOwner", &Behaviour::getOwner);
	Script::bind<SceneDefinition>()
		.addMethod("load", &SceneDefinition::load);

	// Bind functions
	Script::bind("cRoundf", &cRoundf);
	Script::bind("printDictionary", &printDictionary);

	// 3. Load and execute the lua main file
	Script::loadFile("main.lua");

	// 4. Release all resources
	Script::release();

	return 0;
}
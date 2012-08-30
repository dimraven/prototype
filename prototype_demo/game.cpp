#include "game.h"
#include <GL/glfw.h>
IMPLEMENT_SCRIPT_CLASS(Game, ScriptObject);

Game* GameInstance = NULL;

void GLFWCALL Game_Key_Callback(int key, int action)
{
	if(action == GLFW_PRESS)
	{
		GameInstance->onKeyDown(key);
	}
	else if(action == GLFW_RELEASE)
	{
		GameInstance->onKeyUp(key);
	}
}

Game::Game()
	: ScriptObject()
{
	GameInstance = this;
}

Game::~Game()
{
}

bool Game::onAdd()
{
	if(!ScriptObject::onAdd())
		return false;
	
	 if(!glfwInit())
		 return false;

	 glfwSetKeyCallback(Game_Key_Callback);
}

void Game::onRemove()
{
	glfwTerminate();
	ScriptObject::onRemove();
}

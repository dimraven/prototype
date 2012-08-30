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
	: ScriptObject(), KeyboardEventObserver()
{
	GameInstance = this;
}

Game::~Game()
{
	GameInstance = NULL;
}

bool Game::onAdd()
{
	if(!ScriptObject::onAdd())
		return false;
	
	 if(!glfwInit())
		 return false;

	glfwSetKeyCallback(Game_Key_Callback);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glfwSwapInterval(1); 		// Lock to vertical sync of monitor (normally 60Hz, so 60fps)

	glEnable(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(5.0f);
	glEnable(GL_LINE_SMOOTH);
	glPointSize(5.0f);
	glEnable(GL_POINT_SMOOTH);

	 return true;
}

void Game::onRemove()
{
	glfwTerminate();
	ScriptObject::onRemove();
}

bool Game::isRunning()
{
	glClear(GL_COLOR_BUFFER_BIT);
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glfwSwapBuffers();

	return glfwGetWindowParam(GLFW_OPENED);
}

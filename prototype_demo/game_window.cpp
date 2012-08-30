#include "game_window.h"
#include <GL/glfw.h>
IMPLEMENT_SCRIPT_CLASS(GameWindow, ScriptObject);

GameWindow::GameWindow()
	: ScriptObject()
{
}

GameWindow::~GameWindow()
{
}


bool GameWindow::onAdd()
{
	if(!ScriptObject::onAdd())
		return false;

	return glfwInit() != 0;
}

void GameWindow::onRemove()
{
	glfwTerminate();
	ScriptObject::onRemove();
}

void GameWindow::open(int width, int height)
{
	if(width == 0 || height == 0)
	{
		width = 1024;
		height = 768;
	}

	glfwOpenWindow(width, height, 0,0,0,0, 16,0, GLFW_WINDOW);
}

void GameWindow::close()
{
	glfwCloseWindow();
}

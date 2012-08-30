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

	return true;
}

void GameWindow::onRemove()
{
	ScriptObject::onRemove();
}

void GameWindow::open(int width, int height, std::string title)
{
	if(width == 0 || height == 0)
	{
		width = 1024;
		height = 768;
	}

	glfwOpenWindow(width, height, 0,0,0,0, 16,0, GLFW_WINDOW);
	glfwSetWindowTitle(title.c_str());
}

void GameWindow::close()
{
	glfwCloseWindow();
}

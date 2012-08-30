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

	if(!glfwOpenWindow(width, height, 8, 8, 8, 8, 0, 0, GLFW_WINDOW))
	{
	}

	glfwSetWindowTitle(title.c_str());

	// Setup our viewport to be the entire size of the window
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
 
	// Change to the projection matrix, reset the matrix and set up orthagonal projection (i.e. 2D)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, 1); // Paramters: left, right, bottom, top, near, far
}

void GameWindow::close()
{
	glfwCloseWindow();
}

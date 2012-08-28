#include "game.h"
IMPLEMENT_SCRIPT_CLASS(Game, ScriptObject)

Game::Game()
	: ScriptObject()
{
}

Game::~Game()
{
}

bool Game::onAdd()
{
	return true;
}

void Game::onRemove()
{
}

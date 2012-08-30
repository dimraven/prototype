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
	if(!ScriptObject::onAdd())
		return false;

	return true;
}

void Game::onRemove()
{
	ScriptObject::onRemove();
}

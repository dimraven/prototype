#include "behaviour.h"
#include "game.h"
IMPLEMENT_SCRIPT_CLASS(Behaviour, ScriptObject);

Behaviour::Behaviour()
	: ScriptObject(), mOwner(NULL)
{
}

Behaviour::~Behaviour()
{
}

bool Behaviour::onAdd()
{
	if(!ScriptObject::onAdd())
		return false;

	if(isMethodDefined("onKeyUp") ||
		isMethodDefined("onKeyDown"))
	{
		GameInstance->addKeyboardEventListener(this);
	}

	return true;
}

void Behaviour::onRemove()
{
	GameInstance->removeKeyboardEventListener(this);
	ScriptObject::onRemove();
}

void Behaviour::onUpdate(float dt)
{
	invoke("onUpdate", dt);
}

void Behaviour::onKeyDown(int key)
{
	invoke("onKeyDown", key);
}

void Behaviour::onKeyUp(int key)
{
	invoke("onKeyUp", key);
}

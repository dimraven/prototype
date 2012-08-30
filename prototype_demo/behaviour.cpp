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
	invokeMethod("onUpdate", dt);
}

void Behaviour::onKeyDown(int key)
{
	invokeMethod("onKeyDown", key);
}

void Behaviour::onKeyUp(int key)
{
	invokeMethod("onKeyUp", key);
}

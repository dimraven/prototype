#include "behaviour.h"
IMPLEMENT_SCRIPT_CLASS(Behaviour, ScriptObject);

Behaviour::Behaviour()
	: ScriptObject(), mOwner(NULL)
{
}

Behaviour::~Behaviour()
{
}

void Behaviour::onUpdate(float dt)
{
	invokeMethod("onUpdate", dt);
}
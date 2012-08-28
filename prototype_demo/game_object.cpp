#include "game_object.h"
#include <algorithm>
IMPLEMENT_SCRIPT_CLASS(GameObject, DrawableObject);

GameObject::GameObject()
	: DrawableObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::onUpdate(float dt)
{
	Behaviours::iterator it = mBehaviours.begin();
	Behaviours::iterator end = mBehaviours.end();
	for(; it != end; ++ it)
	{

	}

	invokeMethod("onUpdate", dt);
}

void GameObject::addBehaviour(Behaviour* behaviour)
{
	mBehaviours.push_back(behaviour);
}

void GameObject::removeBehaviour(Behaviour* behaviour)
{
	Behaviours::iterator it = std::find(mBehaviours.begin(), mBehaviours.end(), behaviour);
	if(it != mBehaviours.end())
		mBehaviours.erase(it);
}

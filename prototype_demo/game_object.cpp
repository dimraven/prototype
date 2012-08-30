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

void GameObject::onRemove()
{
	Behaviours::iterator it = mBehaviours.begin();
	Behaviours::iterator end = mBehaviours.end();
	for(; it != end; ++ it)
	{
		if(it->exists())
		{
			(*it)->unregisterObject();
			delete it->get();
		}
	}
	mBehaviours.clear();
}

void GameObject::onUpdate(float dt)
{
	Behaviours::iterator it = mBehaviours.begin();
	Behaviours::iterator end = mBehaviours.end();
	for(; it != end; ++ it)
		(*it)->onUpdate(dt);

	invokeMethod("onUpdate", dt);
}

void GameObject::addBehaviour(Behaviour* behaviour)
{
	if(behaviour == NULL)
		return;

	mBehaviours.push_back(behaviour);
	behaviour->setOwner(this);
}

void GameObject::removeBehaviour(Behaviour* behaviour)
{
	Behaviours::iterator it = std::find(mBehaviours.begin(), mBehaviours.end(), behaviour);
	if(it != mBehaviours.end())
		mBehaviours.erase(it);
}

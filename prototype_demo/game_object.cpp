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
	Behaviours::size_type size = mBehaviours.size();
	for(Behaviours::size_type i = 0; i < size; ++i)
	{
		if(mBehaviours[i].exists())
		{
			mBehaviours[i]->unregisterObject();
			delete mBehaviours[i].get();
		}
	}

	DrawableObject::onRemove();
}

void GameObject::onUpdate(float dt)
{
	if(!mUpdateBehaviours.empty())
	{
		Behaviours::size_type size = mUpdateBehaviours.size();
		for(Behaviours::size_type i = 0; i < size; ++i)
		{
			if(mUpdateBehaviours[i].exists())
			{
				mUpdateBehaviours[i]->onUpdate(dt);
			}
		}
	}
	
	invoke("onUpdate", dt);
}

void GameObject::addBehaviour(Behaviour* behaviour)
{
	if(behaviour == NULL)
		return;

	// TODO: Assert or process for moving the behaviour from one object to another(?)
	assert(behaviour->getOwner() == NULL && "Behaviour cannot have more than one owner at the same time");

	mBehaviours.push_back(behaviour);
	behaviour->setOwner(this);

	if(behaviour->isUpdateBehaviour())
		mUpdateBehaviours.push_back(behaviour);
}

void GameObject::removeBehaviour(Behaviour* behaviour)
{
	Behaviours::iterator it = std::find(mBehaviours.begin(), mBehaviours.end(), behaviour);
	if(it != mBehaviours.end())
		mBehaviours.erase(it);

	if(behaviour->isUpdateBehaviour())
	{
		it = std::find(mUpdateBehaviours.begin(), mUpdateBehaviours.end(), behaviour);
		if(it != mUpdateBehaviours.end())
			mUpdateBehaviours.erase(it);
	}
}

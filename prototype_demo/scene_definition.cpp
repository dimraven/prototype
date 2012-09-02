#include "scene_definition.h"
#include "game_object.h"
IMPLEMENT_SCRIPT_CLASS(SceneDefinition, ScriptObject);

SceneDefinition::SceneDefinition()
{
}

SceneDefinition::~SceneDefinition()
{
}

void SceneDefinition::onRemove()
{
	GameObjects::size_type size = mGameObjects.size();
	for(GameObjects::size_type i = 0; i < size; ++i)
	{
		if(mGameObjects[i].exists())
		{
			mGameObjects[i]->unregisterObject();
			delete mGameObjects[i].get();
		}
	}
	mGameObjects.clear();
	ScriptObject::onRemove();
}

void SceneDefinition::load()
{
	invokeAndGet("onLoad", mGameObjects);
}

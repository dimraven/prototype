#ifndef _SCENE_DEFINITION_H_
#define _SCENE_DEFINITION_H_

#include <prototype/script_object.h>
using namespace prototype;

class GameObject;

class SceneDefinition : public ScriptObject
{
	typedef std::vector< ScriptObjectPtr<GameObject> > GameObjects;

public:
	DEFINE_SCRIPT_CLASS(SceneDefinition);

public:
	SceneDefinition();
	virtual ~SceneDefinition();

	//
	// 
	virtual void onRemove();

	//
	// Method executed when the scene that this definition represent is loading.
	void load();

	//
	// @return A list of all game objects in this scene.
	inline std::vector< ScriptObjectPtr<GameObject> >& getGameObjects() {
		return mGameObjects;
	}

private:
	GameObjects mGameObjects;
};

#endif

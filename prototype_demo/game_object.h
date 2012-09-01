#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <list>
#include "drawable_object.h"
#include "behaviour.h"

//
// Base class for our game objects.
class GameObject : public DrawableObject
{
	typedef std::vector< ScriptObjectPtr<Behaviour> > Behaviours;

public:
	DEFINE_SCRIPT_CLASS(GameObject);

public:
	GameObject();
	virtual ~GameObject();

	virtual void onRemove();

	//
	// Method called every frame
	// @param dt the delta time.
	virtual void onUpdate(float dt);

	void addBehaviour(Behaviour* behaviour);
	void removeBehaviour(Behaviour* behaviour);

private:
	Behaviours mBehaviours;

	//
	Behaviours mUpdateBehaviours;
};


#endif

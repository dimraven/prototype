#ifndef _BEHAVIOUR_H_
#define _BEHAVIOUR_H_

#include <prototype/script_object.h>
using namespace prototype;

class GameObject;

//
// Base class for all behaviours
class Behaviour : public ScriptObject
{
public:
	DEFINE_SCRIPT_CLASS(Behaviour);

public:
	Behaviour();
	virtual ~Behaviour();

	//
	// Method called when updating
	virtual void onUpdate(float dt);

	//
	// Retrieves the owner of this behaviour
	inline GameObject* getOwner() {
		return mOwner;
	}

	//
	// Sets the owner of this behaviour
	// @param owner the owner of this behaviour
	inline void setOwner(GameObject* owner) {
		mOwner = owner;
	}

private:
	GameObject* mOwner;
};

#endif

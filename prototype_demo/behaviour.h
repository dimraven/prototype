#ifndef _BEHAVIOUR_H_
#define _BEHAVIOUR_H_

#include "input/keyboard_event_listener.h"

#include <prototype/script_object.h>
using namespace prototype;

class GameObject;

//
// Base class for all behaviours
class Behaviour : public ScriptObject, public KeyboardEventListener
{
public:
	DEFINE_SCRIPT_CLASS(Behaviour);

public:
	Behaviour();
	virtual ~Behaviour();

	//
	virtual bool onAdd();
	
	//
	virtual void onRemove();

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

	//
	// Method called when a keyboard key is pressed
	// @param key the key we are pressing
	virtual void onKeyDown(int key);

	//
	// Method called when a keyboard key is released
	// @param key the key we released
	virtual void onKeyUp(int key);

private:
	GameObject* mOwner;
};

#endif

#ifndef _GAME_H_
#define _GAME_H_

#include <list>
#include <prototype/script_object.h>
using namespace prototype;

#include "input/keyboard_event_listener.h"
#include "input/keyboard_event_observer.h"

class GameObject;

//
// Base class for the game we are creating
class Game : public ScriptObject, public KeyboardEventObserver
{
	typedef std::list<GameObject*> GameObjects;

public:
	DEFINE_SCRIPT_CLASS(Game);

public:
	Game();
	virtual ~Game();

	//
	// Method called when the object is added and registered
	virtual bool onAdd();

	//
	// Method called when the object is deleted
	virtual void onRemove();
};

// UGLY__
extern Game* GameInstance;

#endif

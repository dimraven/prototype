#ifndef _GAME_H_
#define _GAME_H_

#include <list>

#include <prototype/script_object.h>
using namespace prototype;

class GameObject;

//
// Base class for the game we are creating
class Game : public ScriptObject
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
	virtual void onDelete();
};

#endif

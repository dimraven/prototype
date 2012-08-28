#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <prototype/script_object.h>
using namespace prototype;

//
// Base class for our game objects.
class GameObject : public ScriptObject
{
public:
	DEFINE_SCRIPT_CLASS(GameObject);

public:
	GameObject();
	virtual ~GameObject();
};


#endif

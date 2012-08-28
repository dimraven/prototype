#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "drawable_object.h"

//
// Base class for our game objects.
class GameObject : public DrawableObject
{
public:
	DEFINE_SCRIPT_CLASS(GameObject);

public:
	GameObject();
	virtual ~GameObject();
};


#endif

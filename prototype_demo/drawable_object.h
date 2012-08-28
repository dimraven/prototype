#ifndef _DRAWABLE_OBJECT_H_
#define _DRAWABLE_OBJECT_H_

#include <prototype/script_object.h>
using namespace prototype;

//
// Drawable game objects
class DrawableObject : public ScriptObject
{
public:
	DEFINE_SCRIPT_CLASS(DrawableObject);

public:
	DrawableObject();
	virtual ~DrawableObject();


};

#endif

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

	//
	// Sets metadata associated with this drawable object
	void setMetaData(Dictionary metadata);

	//
	// Method called when metadata is assigned to this object.
	virtual void onMetaDataSet();

	//
	// Add this item to the scene
	void addToScene();

	//
	//
	void removeFromScene();

private:
	Dictionary mMetaData;
};

#endif

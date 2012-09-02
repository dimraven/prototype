#include "drawable_object.h"
IMPLEMENT_SCRIPT_CLASS(DrawableObject, ScriptObject);

DrawableObject::DrawableObject()
	: ScriptObject()
{
}

DrawableObject::~DrawableObject()
{
}

void DrawableObject::setMetaData(Dictionary dict)
{
	mMetaData = dict;
	std::string imageSrc = dict.getString("imageSrc");
}

void DrawableObject::onMetaDataSet()
{
	invoke("onMetaDataSet");
}


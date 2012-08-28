#ifndef _BEHAVIOUR_H_
#define _BEHAVIOUR_H_

#include <prototype/script_object.h>
using namespace prototype;

//
// Base class for all behaviours
class Behaviour : public ScriptObject
{
public:
	DEFINE_SCRIPT_CLASS(Behaviour);

public:
	Behaviour();
	virtual ~Behaviour();
};

#endif

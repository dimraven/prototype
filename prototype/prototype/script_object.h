#ifndef _PROTOTYPE_SCRIPT_OBJECT_H_
#define _PROTOTYPE_SCRIPT_OBJECT_H_

#include "script_invoker.h"
#include "class_definition.h"
#include "script.h"

namespace prototype
{
	//
	// Base class for all scriptable object types.
	class ScriptObject : public ScriptInvoker
	{
	public:
		//
		// Method used to retrieve information about this class. This is used when building the
		// tables wrapping this object on the script-side
		//
		// @return The script definition for this class.
		virtual ClassDefinition* getClassDef() const;
		
		//
		// Method used to retrieve information about this class. This is used when building the
		// tables wrapping this object on the script-side
		//
		// @return The script definition for this class.
		static ClassDefinitionImpl<ScriptObject>* getStaticClassDef();
		
	private:
		//
		// Global instance containing class information about this class. Used by the script engine to
		// create the neccessary wrapper objects to contain the pointer.
		static ClassDefinitionImpl<ScriptObject> gClassDef;

	public:
		ScriptObject();
		virtual ~ScriptObject();

		//
		// This method must be called if this object is to be used in script.
		bool registerObject();

		//
		// Registers this object and assigns it a pre-existing reference id.
		bool registerObject(int scriptRef);

		//
		// This method must be called manually before deleting the object (if it's created on the c++ side). 
		// It makes sure that the _instance reference on the script side is released.
		void unregisterObject();

		//
		// Method called when this object is registered and added to the script engine.
		// @return TRUE if we want it to be added; FALSE otherwise. Note that the object's "unregisterObject" method is called if 
		//		this method returns false.
		virtual bool onAdd();

		//
		// Method called before this object is being unregistered by the script engine
		virtual void onDelete();

	};

}

#endif

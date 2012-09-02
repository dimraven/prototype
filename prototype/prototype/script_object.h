#ifndef _PROTOTYPE_SCRIPT_OBJECT_H_
#define _PROTOTYPE_SCRIPT_OBJECT_H_

#include <list>
#include "script_invoker.h"
#include "class_definition.h"
#include "script.h"

namespace prototype
{
	class ScriptObject;

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
		virtual void onRemove();

	public:
		//
		// Removes a ScriptObjectPtr reference from this object. This is used to handle notifications when this object is deleted.
		// @param ptr
		void detachPointer(ScriptObject** ptr);

		//
		// Attaches a ScriptObjectPtr reference. This is used to handle notifications when this object is deleted.
		// @param ptr
		void attachPointer(ScriptObject** ptr);

	private:
		std::list<ScriptObject**> mSafePointerReferences;
	};

	//
	// Container for the ScriptObject instance. Used to make sure that we don't access script-deleted objects from C++ by misstake.
	//
	template<class T>
	class ScriptObjectPtr
	{
	public:
		ScriptObjectPtr() : mPointer(NULL) {
		}

		ScriptObjectPtr(const ScriptObjectPtr<T>& other) : mPointer(const_cast<T*>(static_cast<const T*>(other.mPointer))) {
			if(mPointer != NULL)
				mPointer->attachPointer(&mPointer);
		}

		ScriptObjectPtr(T* ptr) : mPointer(ptr) {
			if(mPointer != NULL)
				mPointer->attachPointer(&mPointer);
		}

		virtual ~ScriptObjectPtr() {
			if(mPointer)
				mPointer->detachPointer(&mPointer);
		}
		
		void set(T* ptr) {
			if(mPointer != NULL)
				mPointer->detachPointer(&mPointer);
			mPointer = ptr;
			if(mPointer != NULL)
				mPointer->attachPointer(&mPointer);
		}

		T& operator*() {
			if(mPointer == NULL)
				return NULL;

			return *static_cast<T*>(mPointer);
		}

		const T& operator*() const {
			if(mPointer == NULL)
				return NULL;

			return *static_cast<T*>(mPointer);
		}

		T* operator->() {
			if(mPointer == NULL)
				return NULL;

			return static_cast<T*>(mPointer);
		}

		const T* operator->() const {
			if(mPointer == NULL)
				return NULL;

			return static_cast<T*>(mPointer);
		}

		T* get() const {
			if(mPointer == NULL) 
				return NULL;

			return static_cast<T*>(mPointer);
		}

		ScriptObjectPtr<T>& operator=(T* ptr) {
			set(ptr);
			return *this;
		}

		ScriptObjectPtr<T>& operator=(ScriptObjectPtr<T>& other) {
			if(&other == this)
				return *this;

			set(static_cast<T*>(other.mPointer));
			return *this;
		}

		template<class U>
		ScriptObjectPtr<T>& operator=(ScriptObjectPtr<U>& other) {
			if(other.exists())
				set(dynamic_cast<T*>(other.get()));

			set(NULL);
			return *this;
		}

		bool exists() const {
			return mPointer != NULL;
		}

		bool operator==(const ScriptObjectPtr<T>& other) const {
			return mPointer == other.mPointer;
		}

		template<class U>
		bool operator==(const ScriptObjectPtr<U>& other) const {
			return mPointer == static_cast<const ScriptObject*>(other.mPointer);
		}

	private:
		ScriptObject* mPointer;
	};
}

#endif

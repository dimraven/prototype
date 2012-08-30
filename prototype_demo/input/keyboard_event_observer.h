#ifndef _KEYBAORD_EVENT_OBSERVER_H_
#define _KEYBAORD_EVENT_OBSERVER_H_

#include <vector>
#include "keyboard_event_listener.h"

class KeyboardEventObserver
{
	typedef std::vector<KeyboardEventListener*> KeyboardEventListeners;

public:
	KeyboardEventObserver();
	virtual ~KeyboardEventObserver();

	void addKeyboardEventListener(KeyboardEventListener* listener);
	void removeKeyboardEventListener(KeyboardEventListener* listener);

	void onKeyDown(int key);

	void onKeyUp(int key);

private:
	KeyboardEventListeners mKeyboardEventListeners;
};

#endif

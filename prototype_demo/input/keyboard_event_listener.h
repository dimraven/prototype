#ifndef _KEYBOARD_EVENT_LISTENER_H_
#define _KEYBOARD_EVENT_LISTENER_H_

class KeyboardEventListener
{
public:
	//
	// Method called when a keyboard key is pressed
	// @param key the key we are pressing
	virtual void onKeyDown(int key) = 0;

	//
	// Method called when a keyboard key is released
	// @param key the key we released
	virtual void onKeyUp(int key) = 0;
};

#endif

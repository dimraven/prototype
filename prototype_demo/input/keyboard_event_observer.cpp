#include "keyboard_event_observer.h"
#include <algorithm>

KeyboardEventObserver::KeyboardEventObserver()
{
}

KeyboardEventObserver::~KeyboardEventObserver()
{
	mKeyboardEventListeners.clear();
}

void KeyboardEventObserver::addKeyboardEventListener(KeyboardEventListener* listener)
{
	mKeyboardEventListeners.push_back(listener);
}

void KeyboardEventObserver::removeKeyboardEventListener(KeyboardEventListener* listener)
{
	KeyboardEventListeners::iterator it = std::find(mKeyboardEventListeners.begin(), mKeyboardEventListeners.end(), listener);
	if(it != mKeyboardEventListeners.end())
		mKeyboardEventListeners.erase(it);
}

void KeyboardEventObserver::onKeyDown(int key)
{
	KeyboardEventListeners::size_type size = mKeyboardEventListeners.size();
	for(KeyboardEventListeners::size_type i = 0; i < size; ++i)
	{
		mKeyboardEventListeners[i]->onKeyDown(key);
	}
}

void KeyboardEventObserver::onKeyUp(int key)
{
	KeyboardEventListeners::size_type size = mKeyboardEventListeners.size();
	for(KeyboardEventListeners::size_type i = 0; i < size; ++i)
	{
		mKeyboardEventListeners[i]->onKeyUp(key);
	}
}

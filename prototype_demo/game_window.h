#ifndef _GAME_WINDOW_H_
#define _GAME_WINDOW_H_

#include <list>

#include <prototype/script_object.h>
using namespace prototype;

class GameObject;

//
// Class for displaying a game window (in DOS)
class GameWindow : public ScriptObject
{
public:
	DEFINE_SCRIPT_CLASS(GameWindow);

public:
	GameWindow();
	virtual ~GameWindow();

	virtual bool onAdd();
	virtual void onRemove();

	//
	// Shows this game window
	// @param width
	// @param height
	void open(int width, int height, std::string title);

	//
	// Closes a game window
	void close();
};

#endif

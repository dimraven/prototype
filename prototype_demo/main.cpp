#include <iostream>
#include <stdio.h>
#include <dos.h>

#include <prototype/script.h>
using namespace prototype;

#include "game.h"
#include "game_object.h"
#include "game_window.h"
/*
int old_mode;

void enter_mode13h(void)
{
	union REGS in, out;

	// get old video mode
	in.h.ah=0xf;
	int86(0x10, &in, &out);
	old_mode=out.h.al;

	// enter mode 13h
	in.h.ah=0;
	in.h.al=0x13;
	int86(0x10, &in, &out);
}

void leave_mode13h(void)
{
	union REGS in, out;

	// change to the video mode we were in before we switched to mode 13h
	in.h.ah=0;
	in.h.al=old_mode;
	int86(0x10, &in, &out);
}
*/
int main()
{
	// 1. Initialize the script engine
	Script::initialize();

	// 2. Bind our C++ classes
	Script::bind<Game>();
	Script::bind<GameWindow>()
		.addMethod("open", &GameWindow::open)
		.addMethod("close", &GameWindow::close);
	Script::bind<DrawableObject>();
	Script::bind<GameObject>();

	// 3. Load and execute the lua main file
	Script::loadFile("main.lua");

	// 4. Release all resources
	Script::release();

	return 0;
}
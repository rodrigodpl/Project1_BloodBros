#ifndef __MODULEDEBUG_H__
#define __MODULEDEBUG_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

enum debug_functions{

	DRAW_COLLIDERS_F1,
	GOD_MODE_F2,
	NO_ENEMIES_F3,
	NO_PLAYER_F4,
	INSTA_LOSE_F5,
	INSTA_WIN_F6,
	RAMBO_MODE_F7,

	MAX_DEBUG_FUNC

};

class ModuleDebug : public Module
{
public:

	bool Start();
	update_status Update();

public:

	bool activated_functions[MAX_DEBUG_FUNC];

};

#endif
#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"

#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum player_inputs
{
	IN_NULL,
	IN_IDLE,
	IN_LEFT_DOWN,
	IN_RIGHT_DOWN,
	IN_LEFT_AND_RIGHT,
	IN_JUMP_LEFT,
	IN_JUMP_RIGHT,
	IN_CROUCH_UP,
	IN_CROUCH_DOWN,
	IN_SHOT,
	IN_JUMP_FINISH,
	IN_SHOT_FINISH
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();

	bool Init();
	update_status PreUpdate();
	uint player_input();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
};

#endif // __ModuleInput_H__
#ifndef __MODULERETICLE_H__
#define __MODULERETICLE_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

#define INIT_MODE_LIFE 10000

enum modes{

	BASIC_SHOT,
	SHOTGUN,
	MACHINEGUN

};

class ModuleReticle : public Module
{
public:
	ModuleReticle();

	bool Start();
	update_status Update();
	bool CleanUp();

	void ChangeMode(modes new_mode);

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation basic_idle;
	Animation basic_shooting;
	Animation shotgun_idle;
	Animation shotgun_shooting;
	Animation machinegun_idle;
	Animation machinegun_shooting;
	uint mode;
	Uint32 mode_timer;
	Uint32 mode_life;
	uint basic_player_shot_fx;
	uint shotgun_player_shot_fx;
	uint machinegun_player_shot_fx;
	fPoint position;
	Collider* ret_col;

};

#endif
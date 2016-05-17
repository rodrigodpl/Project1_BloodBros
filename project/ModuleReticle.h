#ifndef __MODULERETICLE_H__
#define __MODULERETICLE_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleReticle : public Module
{
public:
	ModuleReticle();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation shooting;
	uint player_shot_fx;
	iPoint position;
	Collider* ret_col;

};

#endif
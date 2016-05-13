#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

enum states{

	NOT_JUMPING,
	JUMP_LEFT,
	JUMP_RIGHT

};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation left;
	Animation right;
	Animation crouched_idle;
	Animation crouched_left;
	Animation crouched_right;
	Animation jump_roll_left;
	Animation jump_roll_right;
	Animation crouched_roll_left;
	Animation crouched_roll_right;
	Animation killed;
	fPoint position;
	Collider* col;
	uint state = NOT_JUMPING;
	bool destroyed = false;
	bool crouched = false;

};




#endif
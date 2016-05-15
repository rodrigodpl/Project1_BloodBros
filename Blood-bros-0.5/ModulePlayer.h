#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

#define JUMP_TIME 3000
#define PUNCH_TIME 1000

enum player_states
{
	ST_UNKNOWN,

	ST_IDLE,
	ST_IDLE_SHOOTING,
	ST_WALK_RIGHT,
	ST_WALK_LEFT,
	ST_CROUCHED_IDLE,
	ST_CROUCHED_SHOOTING,
	ST_JUMP_RIGHT,
	ST_JUMP_LEFT,
	ST_ROLL_RIGHT,
	ST_ROLL_LEFT,

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
	Animation idle_shooting;
	Animation left;
	Animation right;
	Animation crouched_idle;
	Animation crouched_shooting;
	Animation jump_roll_left;
	Animation jump_roll_right;
	Animation crouched_roll_left;
	Animation crouched_roll_right;
	Animation killed;
	fPoint position;
	Collider* col;
	uint state = ST_IDLE;
	int speed = 0;
	bool shooting;
	bool alive;
	bool immune;

};




#endif
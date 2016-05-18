#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;


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

enum angle{

	A_0,
	A_30,
	A_60,
	A_90,
	A_120,
	A_150,
	A_180

};


class ModulePlayer : public Module
{
public:
	ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void GetShootingAngle(uint state);
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation idle_shooting;
	Animation idle_shooting_0;
	Animation idle_shooting_30;
	Animation idle_shooting_60;
	Animation idle_shooting_90;
	Animation idle_shooting_120;
	Animation idle_shooting_150;
	Animation idle_shooting_180;
	Animation left;
	Animation right;
	Animation crouched_idle;
	Animation crouched_shooting;
	Animation crouched_shooting_0;
	Animation crouched_shooting_30;
	Animation crouched_shooting_60;
	Animation crouched_shooting_90;
	Animation crouched_shooting_120;
	Animation crouched_shooting_150;
	Animation crouched_shooting_180;
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
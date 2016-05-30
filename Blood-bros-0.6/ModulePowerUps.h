#ifndef __MODULEPOWERUPS_H__
#define __MODULEPOWERUPS_H__

#include "Module.h"
#include "SDL\include\SDL.h"
#include "p2Point.h"


#define MAX_POWER_UPS 20
#define POWER_UP_LIFE 5000


enum PU_LIST
{
	NO_POWER_UP,

	POINTS_1000,
	POINTS_5000,
	POINTS_7000,
	POINTS_10000,
	POINTS_20000,

	POINTS_LIMIT,

	MACHINEGUN_PU,
	SHOTGUN_PU,

	DYNAMITE_PU,
	EXTRA_LIFE

};

struct Power_up{

	int type;
	iPoint position;
	int y_speed = -15;
	Uint32 born;
	Collider* PU_collider;
	Animation* anim;

};

class ModulePowerUps : public Module
{
public:

	ModulePowerUps();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddPU(uint type, int x, int y);
	Power_up* active_power_ups[MAX_POWER_UPS];

	uint object_drop_fx, picked_points_fx, picked_gun_fx;

	Animation points_1000_anim;
	Animation points_5000_anim;
	Animation points_7000_anim;
	Animation points_10000_anim;
	Animation points_20000_anim;
	Animation machinegun_anim;
	Animation shotgun_anim;
	Animation dynamite_anim;
	Animation extralive_anim;

private:

	SDL_Texture* power_up_sprites;
};

#endif 
#ifndef __MODULETINCAN_H__
#define __MODULETINCAN_H__

#include "Module.h"
#include "SDL\include\SDL.h"
#include "p2Point.h"

enum hits{

	NO_HIT,
	ONE_HIT,
	TWO_HIT,
	THREE_HIT,
	FOUR_HIT,
	FIVE_HIT,
	SIX_HIT,
	SEVEN_HIT,
	LAST_HIT



};

class ModuleTincan : public Module
{
public:

	ModuleTincan();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	Animation rolling_anim;
	Animation idle;
	bool first_time;
	uint hit_counter;
	fPoint position, speed;
	Collider* tincan_col;
	Uint32 release_timer;


private:

	SDL_Texture* tincan_sprites;
};

#endif 
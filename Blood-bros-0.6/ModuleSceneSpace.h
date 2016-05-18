#ifndef __MODULESCENESPACE_H__
#define __MODULESCENESPACE_H__

#include "Module.h"


struct SDL_Texture;

#define WAVE_NUM_OF_ENEMIES 10
#define ENEMY_NUM_STG1 6

class ModuleSceneSpace : public Module
{
public:

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	Uint32 init_level_time;
	Uint32 current_level_time;
	bool released_enemies[WAVE_NUM_OF_ENEMIES];
	void loop_enemies();
	int defeated_enemies;
	bool is_backgr_destroyed;

};

#endif // __MODULESCENESPACE_H___
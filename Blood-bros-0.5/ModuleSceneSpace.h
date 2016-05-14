#ifndef __MODULESCENESPACE_H__
#define __MODULESCENESPACE_H__

#include "Module.h"


struct SDL_Texture;

#define WAVE_NUM_OF_ENEMIES 10
#define ENEMY_NUM_STG1 3

class ModuleSceneSpace : public Module
{
public:
	ModuleSceneSpace();
	~ModuleSceneSpace();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* background = nullptr;
	SDL_Texture* stars = nullptr;
	Uint32 init_level_time;
	Uint32 current_level_time;
	bool released_enemies[WAVE_NUM_OF_ENEMIES];
	void loop_enemies();
	int defeated_enemies = 0;
	bool is_backgr_destroyed = false;

};

#endif // __MODULESCENESPACE_H__
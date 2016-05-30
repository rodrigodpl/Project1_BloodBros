#ifndef __MODULESCENESPACE_H__
#define __MODULESCENESPACE_H__

#include "Module.h"


struct SDL_Texture;

#define ENEMY_NUM_STG1 10

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
	uint released_enemies = 0;
	void loop_enemies();
	int defeated_enemies;
	bool is_backgr_destroyed;

};

#endif // __MODULESCENESPACE_H__
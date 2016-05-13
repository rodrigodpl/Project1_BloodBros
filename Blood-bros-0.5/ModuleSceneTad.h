#ifndef __MODULESCENETAD_H__
#define __MODULESCENETAD_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneTad : public Module
{
public:
	ModuleSceneTad();
	~ModuleSceneTad();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	uint fx = 0;
	Uint32 timer;

};

#endif 
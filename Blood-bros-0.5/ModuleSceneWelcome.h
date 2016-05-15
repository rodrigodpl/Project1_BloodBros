#ifndef __MODULESCENEWELCOME_H__
#define __MODULESCENEWELCOME_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneWelcome : public Module
{
public:
	ModuleSceneWelcome();
	~ModuleSceneWelcome();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	uint fx = 0;
	Uint32 timer;
	bool needs_fade;

};

#endif 
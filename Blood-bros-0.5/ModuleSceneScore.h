#ifndef __MODULESCENESCORE_H__
#define __MODULESCENESCORE_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneScore : public Module
{
public:

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
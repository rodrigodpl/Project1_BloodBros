#ifndef __MODULESCENESTAGE_PRES_H__
#define __MODULESCENESTAGE_PRES_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneStage_Pres : public Module
{
public:
	ModuleSceneStage_Pres();
	~ModuleSceneStage_Pres();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	uint fx = 0;
	Uint32 timer;

};

#endif 
#ifndef __MODULESCENARIO_H__
#define __MODULESCENARIO_H__

#include "Module.h"


#define MAX_ELEMENTS 50


enum SCENARIO_ELEMENTS
{
	NO_TYPE_SCE,
	DESTROYABLE_WALL,
	DESTROYABLE_BOTTLE,
	DESTROYABLE_LIGHT,
	DESTROYABLE_BARREL
};

class Scenario_elem;

struct Scenario_elemInfo
{
	SCENARIO_ELEMENTS type = SCENARIO_ELEMENTS::NO_TYPE_SCE;
	int x, y;
};

class ModuleScenario : public Module
{
public:

	friend class ModuleEnemies;

	ModuleScenario();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddElement(SCENARIO_ELEMENTS type, int x, int y);
	uint bottle_index;

private:

	Scenario_elemInfo queue[MAX_ELEMENTS];
	Scenario_elem* elements[MAX_ELEMENTS];
	SDL_Texture* scene_sprites;

};

#endif // __ModuleEnemies_H__
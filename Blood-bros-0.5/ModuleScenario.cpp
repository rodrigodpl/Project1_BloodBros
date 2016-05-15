#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleScenario.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "Scenario_elem.h"
#include "Scenario_Wall_001.h"
#include "Scenario_Barrel.h"
#include "Scenario_Bottle.h"
#include "Scenario_Light.h"
#include "ModuleReticle.h"

#define SPAWN_MARGIN 50



ModuleScenario::ModuleScenario()
{
	for (uint i = 0; i < MAX_ELEMENTS; ++i)
		elements[i] = nullptr;
}

// Destructor
ModuleScenario::~ModuleScenario()
{
}

bool ModuleScenario::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	scene_sprites = App->textures->Load("stage3_1_scenario.png");

	bottle_index = 0;


	return true;
}



// Called before render is available
update_status ModuleScenario::Update()
{
	for (uint i = 0; i < MAX_ELEMENTS; ++i)
	if (elements[i] != nullptr) elements[i]->Update();

	for (uint i = 0; i < MAX_ELEMENTS; ++i)
	if (elements[i] != nullptr && (elements[i]->GetCollider()->type != COLLIDER_WALL || !(App->enemies->IsEnabled()))) elements[i]->Draw(scene_sprites);

	for (uint i = 0; i < MAX_ELEMENTS; ++i)
		if (elements[i] != nullptr && elements[i]->health <= 0 && elements[i]->dying.Finished()){
			delete elements[i];
			elements[i] = nullptr;
		}

	return UPDATE_CONTINUE;
}



// Called before quitting
bool ModuleScenario::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(scene_sprites);

	for (uint i = 0; i < MAX_ELEMENTS; ++i)
	{
		if (elements[i] != nullptr)
		{
			delete elements[i];
			elements[i] = nullptr;
		}
	}

	return true;
}

bool ModuleScenario::AddElement(SCENARIO_ELEMENTS type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ELEMENTS; i++)
	{
		if (elements[i] == nullptr)
		{
			switch (type)
			{
			case SCENARIO_ELEMENTS::DESTROYABLE_WALL:
				elements[i] = new Scenario_Wall_001(x,y);
				break;

			case SCENARIO_ELEMENTS::DESTROYABLE_BOTTLE:
				elements[i] = new Scenario_Bottle(x, y);
				break;

			case SCENARIO_ELEMENTS::DESTROYABLE_LIGHT:
				elements[i] = new Scenario_Light(x, y);
				break;

			case SCENARIO_ELEMENTS::DESTROYABLE_BARREL:
				elements[i] = new Scenario_Barrel(x, y);
				break;
			}break;
		}
		
	}

	return ret;
}



void ModuleScenario::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ELEMENTS; ++i)
	{
		if (elements[i] != nullptr && elements[i]->GetCollider() == c1 && (App->player->shooting || c2->type == COLLIDER_ENEMY_SHOT))
		{
			elements[i]->health -= 1;
			if (elements[i]->health <= 0){
				elements[i]->animation = &(elements[i]->dying);
			}
			break;
		}
	}
}
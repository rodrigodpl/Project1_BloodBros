#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleSceneSpace.h"
#include "ModuleScenario.h"
#include "ModuleUI.h"
#include "Scenario_elem.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_Barrel_Guy.h"
#include "Enemy_indian_001.h"
#include "Enemy_Indian_003.h"
#include "Enemy_Indian_002.h"
#include "NPC_pig_001.h"
#include "ModuleReticle.h"
#include "p2Point.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}


bool ModuleEnemies::Start()
{
	sprites = App->textures->Load("complete_enemy_spritesheet.png");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if(queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Update();

	for (uint i = 0; i < MAX_ELEMENTS; ++i){
		if (App->scenario->elements[i] != nullptr){

			const Collider* scen_col = App->scenario->elements[i]->GetCollider();

			if (scen_col->type == COLLIDER_WALL)
				App->scenario->elements[i]->Draw(App->scenario->scene_sprites);
		}
	}

	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			if ((enemies[i]->position.x < (0 - SPAWN_MARGIN) || enemies[i]->position.x >(SCREEN_WIDTH + SPAWN_MARGIN)
				|| enemies[i]->position.y < (0 - SPAWN_MARGIN) || enemies[i]->position.y >(SCREEN_HEIGHT + SPAWN_MARGIN))
				|| (enemies[i]->state == EN_ST_DYING && enemies[i]->animation->Finished() && enemies[i]->is_killable)){

				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}


bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for(; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if(i != MAX_ENEMIES)
	{
		switch(info.type)
		{
			case ENEMY_TYPES::BARREL_GUY:
				enemies[i] = new Enemy_Barrel_Guy(info.x,info.y); break;
			case ENEMY_TYPES::INDIAN_001:
				enemies[i] = new Enemy_Indian_001(info.x, info.y); break;
			case ENEMY_TYPES::INDIAN_002:
				enemies[i] = new Enemy_Indian_002(info.x, info.y); break;
			case ENEMY_TYPES::INDIAN_003:
				enemies[i] = new Enemy_Indian_003(info.x, info.y); break;
			case ENEMY_TYPES::PIG_001:
				enemies[i] = new NPC_Pig_001(info.x, info.y); break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && App->player->shooting)
		{
			if (enemies[i]->state != EN_ST_PROTECTING && enemies[i]->state != EN_ST_DYING){
				enemies[i]->state = EN_ST_DYING;
				if (enemies[i]->is_killable == true){
					App->scene_space->defeated_enemies++;
					App->UI->player_score += 100;
				}
			}
			break;
		}
	}
}

void ModuleEnemies::check_explosion(fPoint location){

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if ((enemies[i]->position.x > (location.x - 100) && enemies[i]->position.x < (location.x + 60)) &&
				(enemies[i]->position.y - 30 > (location.y - 100) && enemies[i]->position.y - 30 < (location.y + 60)))
			{
				if (enemies[i]->state != EN_ST_PROTECTING && enemies[i]->state != EN_ST_DYING ){
					enemies[i]->state = EN_ST_DYING;
					App->scene_space->defeated_enemies++;
					App->UI->player_score += 100;
				}
			}
		}

	}
}
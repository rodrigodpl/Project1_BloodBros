#include "Application.h"
#include "Scenario_Wall_001.h"
#include "Path.h"
#include "ModuleSceneSpace.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

Scenario_Wall_001::Scenario_Wall_001(int x, int y) : Scenario_elem(x, y)
{

	health_100.PushBack({ 770, 26, 674, 310 });

	health_60.PushBack({ 770, 357, 674, 310 });

	health_30.PushBack({ 770, 688, 674, 310 });


	collider = App->collision->AddCollider({ 0, 44, 674, 310 }, COLLIDER_TYPE::COLLIDER_WALL, (Module*)App->scenario);

	orig_pos.x = x;
	orig_pos.y = y;

	health = 1000;

	animation = &health_100;
}

void Scenario_Wall_001::Update()
{

	Animation* state = &health_100;;

	if (health <= 1000){

		if (health < 600){

			if (health < 300){
				state = &health_30;
			}
			else{
				state = &health_60;
			}
		}
	}
	
	animation = state;
	
}

void Scenario_Wall_001::Destroy(){

	App->particles->AddParticle(App->particles->destroying_wall, position.x, position.y);
	App->scene_space->is_backgr_destroyed = true;


}
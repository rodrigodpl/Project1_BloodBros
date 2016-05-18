#include "Application.h"
#include "Scenario_Wall_001.h"
#include "Path.h"
#include "ModuleSceneSpace.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

Scenario_Wall_001::Scenario_Wall_001(int x, int y) : Scenario_elem(x, y)
{

	health_500.PushBack({ 770, 26, 674, 310 });

	health_300.PushBack({ 770, 357, 674, 310 });

	health_100.PushBack({ 770, 688, 674, 310 });


	collider = App->collision->AddCollider({ 0, 44, 674, 310 }, COLLIDER_TYPE::COLLIDER_WALL, (Module*)App->scenario);

	orig_pos.x = x;
	orig_pos.y = y;

	health = 500;

	animation = &health_500;
}

void Scenario_Wall_001::Update()
{

	Animation* current_state = &health_500;

	if (health <= 500){

		if (health < 300){

			if (health < 100){

				if (health <= 0){
					current_state = &dying;
					App->scene_space->is_backgr_destroyed = true;
					App->particles->AddParticle(App->particles->destroying_wall, position.x, position.y);
				}
				else
					current_state = &health_100;
			}
			else{
				current_state = &health_300;
			}
		}
	}
	
	if (animation != current_state)
		animation = current_state;
	
}


#include "Application.h"
#include "Scenario_Light.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include <stdlib.h>
#include <time.h>

Scenario_Light::Scenario_Light(int x, int y) : Scenario_elem(x, y)
{

	idle.PushBack({ 36, 209, 106, 99 });
	idle.PushBack({ 225, 209, 106, 99 });
	idle.speed = 0.1f;


	collider = App->collision->AddCollider({ 0, 0, 106, 99 }, COLLIDER_TYPE::COLLIDER_SCENARIO, (Module*)App->scenario);

	orig_pos.x = x;
	orig_pos.y = y;

	health = 75;

	animation = &idle;
	
}


void Scenario_Light::Destroy(){

	App->particles->AddParticle(App->particles->laser, position.x, position.y);


}
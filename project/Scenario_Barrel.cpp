#include "Application.h"
#include "Scenario_Barrel.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include <stdlib.h>
#include <time.h>

Scenario_Barrel::Scenario_Barrel(int x, int y) : Scenario_elem(x, y)
{

	idle.PushBack({ 36, 329, 65, 74 });

	dying.PushBack({ 0, 0, 0, 0 });
	dying.PushBack({ 0, 0, 0, 0 });
	dying.PushBack({ 0, 0, 0, 0 });
	dying.speed = 0.2f;
	dying.loop = false;


	collider = App->collision->AddCollider({ 0, 0, 65, 74 }, COLLIDER_TYPE::COLLIDER_SCENARIO, (Module*)App->scenario);

	orig_pos.x = x;
	orig_pos.y = y;

	health = 1;

	animation = &idle;

}




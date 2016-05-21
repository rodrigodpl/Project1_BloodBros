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

	dying.PushBack({ 0, 0, 0, 0 });
	dying.PushBack({ 0, 0, 0, 0 });
	dying.PushBack({ 0, 0, 0, 0 });
	dying.speed = 0.2f;
	dying.loop = false;

	anim_displacement_x = ((0 - 0) / 20);    //  = (greatest sprite size.x - idle sprite size.x) / dying_num_of_frames * 2
	anim_displacement_y = ((0 - 0) / 20);    //  = (greatest sprite size.y - idle sprite size.y) / dying_num_of_frames * 2


	collider = App->collision->AddCollider({ 0, 0, 106, 99 }, COLLIDER_TYPE::COLLIDER_SCENARIO, (Module*)App->scenario);

	orig_pos.x = x;
	orig_pos.y = y;

	health = 100;

	animation = &idle;
	
}


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

	dying.PushBack({ 154, 355, 129, 74 });
	dying.PushBack({ 302, 323, 148, 154 });
	dying.speed = 0.2f;
	dying.loop = false;

	anim_displacement_x = ((65 - 148) / 20);   //  = (idle sprite size.x - greatest sprite size.x) / dying_num_of_frames * 2
	anim_displacement_y = ((74 - 154) / 20);   //  = (idle sprite size.yg - reatest sprite size.y ) / dying_num_of_frames * 2

	collider = App->collision->AddCollider({ 0, 0, 65, 74 }, COLLIDER_TYPE::COLLIDER_SCENARIO, (Module*)App->scenario);

	orig_pos.x = x;
	orig_pos.y = y;

	health = 1;

	animation = &idle;

}




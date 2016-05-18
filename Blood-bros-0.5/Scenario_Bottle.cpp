#include "Application.h"
#include "Scenario_Bottle.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleScenario.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#define BOTTLE_NUM 6
uint bottles[BOTTLE_NUM] = { BLUE_NARROW, BLUE_WIDE, BLUE_NARROW, BLUE_NARROW, ORANGE, BLUE_NARROW };

Scenario_Bottle::Scenario_Bottle(int x, int y) : Scenario_elem(x, y)
{


	collider = App->collision->AddCollider({ 0, 0, 40, 45 }, COLLIDER_TYPE::COLLIDER_SCENARIO, (Module*)App->scenario);

	orig_pos.x = x;
	orig_pos.y = y;

	health = 1;

	
	switch (bottles[App->scenario->bottle_index]){
	case BLUE_WIDE:
		idle.PushBack({ 57, 122, 44, 46 });
		dying.PushBack({ 0, 0, 0, 0 });
		dying.PushBack({ 0, 0, 0, 0 });
		dying.PushBack({ 0, 0, 0, 0 });
		dying.speed = 0.2f;
		dying.loop = false;
		break;
	case BLUE_NARROW:
		idle.PushBack({ 113, 122, 35, 48 });
		dying.PushBack({ 0, 0, 0, 0 });
		dying.PushBack({ 0, 0, 0, 0 });
		dying.PushBack({ 0, 0, 0, 0 });
		dying.speed = 0.2f;
		dying.loop = false;
		break;
	case ORANGE:
		idle.PushBack({ 160, 122, 35, 48 });
		dying.PushBack({ 0, 0, 0, 0 });
		dying.PushBack({ 0, 0, 0, 0 });
		dying.PushBack({ 0, 0, 0, 0 });
		dying.speed = 0.2f;
		dying.loop = false;
		break;

	}


	App->scenario->bottle_index++;

	animation = &idle;
	
}



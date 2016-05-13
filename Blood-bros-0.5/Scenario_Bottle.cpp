#include "Application.h"
#include "Scenario_Bottle.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleScenario.h"
#include "p2Point.h"
#include "ModuleParticles.h"


Scenario_Bottle::Scenario_Bottle(int x, int y) : Scenario_elem(x, y)
{

	uint bottles[BOTTLE_NUM] = { BLUE_NARROW, BLUE_WIDE, BLUE_NARROW, BLUE_NARROW, ORANGE, BLUE_NARROW };

	collider = App->collision->AddCollider({ 0, 0, 40, 45 }, COLLIDER_TYPE::COLLIDER_SCENARIO, (Module*)App->scenario);

	orig_pos.x = x;
	orig_pos.y = y;

	health = 10;

	
	switch (bottles[App->scenario->bottle_index]){
	case BLUE_WIDE:
		idle.PushBack({ 57, 122, 44, 46 });
		break;
	case BLUE_NARROW:
		idle.PushBack({ 113, 122, 35, 48 });
		break;
	case ORANGE:
		idle.PushBack({ 160, 122, 35, 48 });
		break;

	}

	App->scenario->bottle_index++;

	animation = &idle;
	
}


void Scenario_Bottle::Destroy(){

	App->particles->AddParticle(App->particles->laser, position.x, position.y);


}
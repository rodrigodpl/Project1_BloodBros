#include "Application.h"
#include "Scenario_Light.h"
#include "Path.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include <stdlib.h>
#include <time.h>

Scenario_Light::Scenario_Light(int x, int y) : Scenario_elem(x, y)
{

	idle.PushBack({ 37, 208, 106, 98 });
	idle.PushBack({ 224, 208, 106, 98 });
	idle.speed = 0.1f;

	dying.PushBack({ 353, 208, 106, 98 });
	dying.PushBack({ 472, 208, 106, 98 });
	dying.speed = 0.2f;
	dying.loop = false;

	anim_displacement_x = 0; 
	anim_displacement_y = 0; 


	collider = App->collision->AddCollider({ 0, 0, 106, 99 }, COLLIDER_TYPE::COLLIDER_SCENARIO, (Module*)App->scenario);

	orig_pos.x = x;
	orig_pos.y = y;

	health = 30;

	animation = &idle;

	destroyed_fx = App->audio->LoadFx("FX/bottle-chash.wav");
	
}


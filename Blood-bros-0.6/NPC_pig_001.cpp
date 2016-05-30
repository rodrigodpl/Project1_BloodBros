#include "Application.h"
#include "NPC_Pig_001.h"
#include "Path.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleSceneSpace.h"
#include "ModulePowerUps.h"
#include "p2Point.h"
#include "ModuleParticles.h"

NPC_Pig_001::NPC_Pig_001(int x, int y) : Enemy(x, y)
{
	walking_right.PushBack({ 74, 416, 102, 67 });
	walking_right.PushBack({ 197, 418, 102, 64 });
	walking_right.speed = 0.1f;

	collider = App->collision->AddCollider({ position.x, position.y - 116, 108, 75 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;

	dying.PushBack({ 74, 416, 102, 67 });
	dying.PushBack({ 0, 0, 0, 0 });
	dying.PushBack({ 74, 416, 102, 67 });
	dying.PushBack({ 0, 0, 0, 0 });
	dying.PushBack({ 197, 418, 102, 64 });
	dying.PushBack({ 0, 0, 0, 0 });
	dying.PushBack({ 197, 418, 102, 64 });
	dying.PushBack({ 0, 0, 0, 0 });
	dying.speed = 0.2f;
	dying.loop = false;

	pig_hit_fx = App->audio->LoadFx("FX/pig-hitted.wav");

	Pig_001_path.PushBack({ -7, 0 }, 400, &walking_right);

	is_killable = false;

	drops_power_up = PU_LIST::MACHINEGUN_PU;

}

NPC_Pig_001::~NPC_Pig_001(){

	if (collider != nullptr)
		App->collision->EraseCollider(collider);

	App->audio->UnLoadFx(pig_hit_fx);

}


void NPC_Pig_001::Update()
{
	
	if (state != EN_ST_DYING)
		position = orig_pos + Pig_001_path.GetCurrentSpeed(&animation);
	else
		position.x -= 7;

		
	if (state == EN_ST_DYING && animation != &dying){
		
		App->audio->PlayFx(pig_hit_fx);
		App->power_ups->AddPU(drops_power_up, position.x, position.y);

		animation->Reset();
		animation = &dying;
		}
	else if (animation == &dying && animation->Finished()){
		Pig_001_path.Reset();
		animation->Reset();
		animation = &walking_right; 
		state = EN_ST_WALKING;
		orig_pos = position;
	}


}

#include "Application.h"
#include "Enemy_Horse_001.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleSceneSpace.h"
#include "ModulePowerUps.h"
#include "ModuleParticles.h"
#include "p2Point.h"
#include "SDL_mixer\include\SDL_mixer.h"

Enemy_Horse_001::Enemy_Horse_001(int x, int y) : Enemy(x, y)
{
	walking.PushBack({ 66, 1528, 93, 80 });
	walking.PushBack({ 180, 1528, 89, 80 });
	walking.PushBack({ 284, 1531, 92, 77 });
	walking.PushBack({ 388, 1531, 96, 77 });
	walking.speed = 0.1f;

	dying.PushBack({ 512, 1515, 86, 92 });
	dying.PushBack({ 612, 1515, 87, 92 });
	dying.PushBack({ 724, 1519, 83, 90 });
	dying.PushBack({ 512, 1515, 86, 92 });
	dying.PushBack({ 612, 1515, 87, 92 });
	dying.PushBack({ 724, 1519, 83, 90 });
	dying.speed = 0.15f;
	dying.loop = false;

	running.PushBack({ 724, 1519, 99, 72 });
	running.PushBack({ 934, 1542, 99, 68 });
	running.PushBack({ 1043, 1535, 99, 75 });
	running.PushBack({ 1151, 1532, 96, 78 });
	running.speed = 0.1f;


	collider = App->collision->AddCollider({ position.x, position.y - 116, 55, 116 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;

	mounted = true;

	horse_hit_fx = App->audio->LoadFx("FX/horse-hitted.wav");
	horse_run_fx = App->audio->LoadFx("FX/riding-horse.wav");

	Horse_001_walking_path.PushBack({ -2, 0 }, 1500, &walking);
	Horse_001_running_path.PushBack({ -4, 0 }, 1500, &running);

	is_killable = false;

	drops_power_up = PU_LIST::POINTS_5000;

}

Enemy_Horse_001::~Enemy_Horse_001()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);

	App->audio->UnLoadFx(horse_hit_fx);
	App->audio->UnLoadFx(horse_run_fx);
}

void Enemy_Horse_001::Update()
{

	if (riding_channel == -1)
		riding_channel = App->audio->Channel_PlayFx(horse_run_fx, 10);

	if (state == EN_ST_DYING && SDL_GetTicks() - 500 < timer)
		state = EN_ST_WALKING;

	if (state != EN_ST_DYING){
		if (mounted)
			position = orig_pos + Horse_001_walking_path.GetCurrentSpeed(&animation);
		else
			position = orig_pos + Horse_001_running_path.GetCurrentSpeed(&animation);
	}


	if (state == EN_ST_DYING && animation == &walking){

		mounted = false;
		animation = &dying;
		Mix_HaltChannel(riding_channel);
		App->audio->PlayFx(horse_hit_fx);
	}
	else if (state == EN_ST_DYING && animation == &running){

		animation->Reset();
		App->power_ups->AddPU(drops_power_up, position.x, position.y);
		animation = &dying;
		Mix_HaltChannel(riding_channel);
		App->audio->PlayFx(horse_hit_fx);
	}


	if (animation == &dying && animation->Finished()){
		animation->Reset();
		state = EN_ST_WALKING;
		timer = SDL_GetTicks();
		orig_pos = position;
		Horse_001_running_path.Reset();
		riding_channel = App->audio->Channel_PlayFx(horse_run_fx, 10);
	}

	

}


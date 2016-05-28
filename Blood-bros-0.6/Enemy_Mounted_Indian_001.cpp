#include "Application.h"
#include "Enemy_Mounted_indian_001.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleSceneSpace.h"
#include "ModuleParticles.h"
#include "p2Point.h"

Enemy_Mounted_Indian_001::Enemy_Mounted_Indian_001(int x, int y) : Enemy(x, y)
{
	walking.PushBack({ 1528, 805, 46, 60 });
	walking.speed = 0.1f;

	shooting.PushBack({ 1528, 805, 46, 60 });
	shooting.PushBack({ 1608, 805, 46, 60 });
	shooting.PushBack({ 1689, 805, 51, 60 });
	shooting.PushBack({ 1608, 805, 46, 60 });
	shooting.PushBack({ 1528, 805, 46, 60 });
	shooting.speed = 0.1f;
	shooting.loop = false;

	dying.PushBack({ 1781, 808, 56, 57 });
	dying.speed = 0.15f;
	dying.loop = false;


	collider = App->collision->AddCollider({ position.x, position.y - 116, 70, 70 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;


	Mounted_Indian_001_path.PushBack({ -2, 0 }, 50, &walking);
	Mounted_Indian_001_path.PushBack({ -2, 0 }, 100, &shooting);
	Mounted_Indian_001_path.PushBack({ -2, 0 }, 50, &walking);

}

void Enemy_Mounted_Indian_001::Update()
{

	if (state != EN_ST_DYING)
		position = orig_pos + Mounted_Indian_001_path.GetCurrentSpeed(&animation);
	else if (state == EN_ST_DYING && animation != &dying)
		animation = &dying;

	if (last_anim != animation){

		if (animation == &walking)
			state = EN_ST_WALKING;
		else if (animation == &dying)
			state = EN_ST_DYING;
		else if (animation == &shooting)
			state = EN_ST_SHOOTING;

		last_anim = animation;
		animation->Reset();

	}

	if (state == EN_ST_SHOOTING && ((animation->current_frame) > (animation->last_frame / 2))){
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 25, position.y - 30, COLLIDER_ENEMY_SHOT);
		state = EN_ST_WALKING;
	}
}


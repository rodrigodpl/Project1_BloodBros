#include "Application.h"
#include "Enemy_Barrel_Guy.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleSceneSpace.h"
#include "ModuleParticles.h"

Enemy_Barrel_Guy::Enemy_Barrel_Guy(int x, int y) : Enemy(x, y)
{
	
	walking.PushBack({ 92, 554, 76, 138 });
	walking.PushBack({ 218, 552, 56, 141 });
	walking.PushBack({ 330, 555, 61, 141 });
	walking.PushBack({ 456, 552, 55, 144 });
	walking.speed = 0.1f;

	to_protect.PushBack({ 456, 723, 55, 133 });
	to_protect.PushBack({ 101, 875, 57, 98 });
	to_protect.PushBack({ 215, 904, 55, 70 });
	to_protect.speed = 0.1f;
	to_protect.loop = false;

	protect.PushBack({ 215, 904, 55, 70 });

	from_protect.PushBack({ 215, 904, 55, 70 });
	from_protect.PushBack({ 101, 875, 57, 98 });
	from_protect.PushBack({ 456, 723, 55, 133 });
	from_protect.speed = 0.1f;
	from_protect.loop = false;

	shooting.PushBack({ 90, 712, 77, 142 });
	shooting.PushBack({ 206, 715, 76, 139 });
	shooting.PushBack({ 312, 715, 88, 139 });
	shooting.PushBack({ 206, 715, 76, 139 });
	shooting.PushBack({ 90, 712, 77, 142 });
	shooting.speed = 0.1f;
	shooting.loop = false;

	dying.PushBack({ 0, 0, 0, 0});
	dying.PushBack({ 0, 0, 0, 0});
	dying.speed = 0.15f;
	dying.loop = false;

	collider = App->collision->AddCollider({ position.x, position.y - 138, 76, 138 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;

	Barrel_Guy_path.PushBack({ -2, 0 }, 100, &walking);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &shooting);
	Barrel_Guy_path.PushBack({ 0, 0 }, 30, &to_protect);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &protect);
	Barrel_Guy_path.PushBack({ 0, 0 }, 30, &from_protect);
	Barrel_Guy_path.PushBack({ -2, 0 }, 100, &walking);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &shooting);
	Barrel_Guy_path.PushBack({ 0, 0 }, 30, &to_protect);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &protect);
	Barrel_Guy_path.PushBack({ 0, 0 }, 30, &from_protect);
	Barrel_Guy_path.PushBack({ 2, 0 }, 100, &walking);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &shooting);
	Barrel_Guy_path.PushBack({ 0, 0 }, 30, &to_protect);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &protect);
	Barrel_Guy_path.PushBack({ 0, 0 }, 30, &from_protect);
	Barrel_Guy_path.PushBack({ 2, 0 }, 500, &walking);

}

void Enemy_Barrel_Guy::Update()
{

	if (state != EN_ST_DYING)
		position = orig_pos + Barrel_Guy_path.GetCurrentSpeed(&animation);
	else if (state == EN_ST_DYING && animation != &dying)
		animation = &dying;


	if (last_anim != animation){

		if (animation == &protect)
			state = EN_ST_PROTECTING;
		else if (animation == &shooting)
			state = EN_ST_SHOOTING;
		else if (animation == &dying)
			state = EN_ST_DYING;
		else
			state = EN_ST_WALKING;

		last_anim = animation;
		animation->Reset();

	}

	if (state == EN_ST_SHOOTING && ((animation->current_frame) > (animation->last_frame / 2))){
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 40, position.y - 100, COLLIDER_ENEMY_SHOT);
		state = EN_ST_WALKING;
	}
}

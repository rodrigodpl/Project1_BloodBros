#include "Application.h"
#include "Enemy_Barrel_Guy.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleSceneSpace.h"
#include "ModuleParticles.h"

Enemy_Barrel_Guy::Enemy_Barrel_Guy(int x, int y) : Enemy(x, y)
{
	
	walking.PushBack({ 697, 527, 54, 143 });
	walking.PushBack({ 817, 530, 60, 140 });
	walking.PushBack({ 934, 527, 55, 140 });
	walking.PushBack({ 1040, 529, 75, 138 });
	walking.speed = 0.1f;


	to_protect.PushBack({ 697, 698, 54, 132 });
	to_protect.PushBack({ 1051, 851, 55, 96 });
	to_protect.PushBack({ 938, 879, 54, 69 });
	to_protect.speed = 0.1f;
	to_protect.loop = false;

	protect.PushBack({ 938, 879, 54, 69 });

	from_protect.PushBack({ 938, 879, 54, 69 });
	from_protect.PushBack({ 1051, 851, 55, 96 });
	from_protect.PushBack({ 697, 698, 54, 132 });
	from_protect.speed = 0.1f;
	from_protect.loop = false;


	shooting.PushBack({ 1041, 687, 76, 141 });
	shooting.PushBack({ 925, 690, 76, 138 });
	shooting.PushBack({ 808, 690, 76, 138 });
	shooting.PushBack({ 925, 690, 76, 138 });
	shooting.PushBack({ 1041, 687, 76, 141 });
	shooting.speed = 0.1f;
	shooting.loop = false;


	dying.PushBack({ 413, 856, 66, 132 });
	dying.PushBack({ 502, 856, 93, 132 });
	dying.PushBack({ 612, 868, 87, 123 });
	dying.PushBack({ 713, 895, 84, 93 });
	dying.speed = 0.15f;
	dying.loop = false;

	collider = App->collision->AddCollider({ position.x, position.y - 138, 76, 138 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;

	Barrel_Guy_path.PushBack({ 2, 0 }, 100, &walking);
	Barrel_Guy_path.PushBack({ 0, 0 }, 70, &shooting);
	Barrel_Guy_path.PushBack({ 0, 0 }, 30, &to_protect);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &protect);
	Barrel_Guy_path.PushBack({ 0, 0 }, 30, &from_protect);
	Barrel_Guy_path.PushBack({ 2, 0 }, 100, &walking);
	Barrel_Guy_path.PushBack({ 0, 0 }, 70, &shooting);
	Barrel_Guy_path.PushBack({ 0, 0 }, 30, &to_protect);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &protect);
	Barrel_Guy_path.PushBack({ 0, 0 }, 30, &from_protect);
	Barrel_Guy_path.PushBack({ 2, 0 }, 100, &walking);
	Barrel_Guy_path.PushBack({ 0, 0 }, 70, &shooting);
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
		else if (animation == &walking)
			state = EN_ST_WALKING;

		last_anim = animation;
		animation->Reset();

	}

	if (state == EN_ST_SHOOTING && ((animation->current_frame) > (animation->last_frame / 2))){
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 40, position.y - 100, COLLIDER_ENEMY_SHOT);
		state = EN_ST_WALKING;
	}
}

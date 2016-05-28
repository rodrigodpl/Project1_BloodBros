#include "Application.h"
#include "Enemy_indian_001.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleSceneSpace.h"
#include "ModuleParticles.h"
#include "p2Point.h"

Enemy_Indian_001::Enemy_Indian_001(int x, int y) : Enemy(x, y)
{
	walking.PushBack({ 1215, 28, 54, 115 });
	walking.PushBack({ 1110, 27, 79, 115 });
	walking.PushBack({ 996, 30, 96, 112 });
	walking.PushBack({ 934, 29, 51, 115 });
	walking.PushBack({ 843, 30, 77, 115 });
	walking.PushBack({ 737, 31, 96, 112 });
	walking.speed = 0.1f;

	shooting.PushBack({ 529, 31, 99, 112 });
	shooting.PushBack({ 641, 0, 82, 144 });
	shooting.PushBack({ 529, 31, 99, 112 });
	shooting.speed = 0.05f;
	shooting.loop = false;

	dying.PushBack({ 24, 190, 84, 130 });
	dying.PushBack({ 139, 224, 83, 115 });
	dying.PushBack({ 247, 233, 102, 80 });
	dying.PushBack({ 391, 288, 102, 22 });
	dying.speed = 0.15f;
	dying.loop = false;


	collider = App->collision->AddCollider({ position.x, position.y - 116, 55, 116 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;


	Indian_001_path.PushBack({ 2, 0 }, 100, &walking);
	Indian_001_path.PushBack({ 0, 0 }, 100, &shooting);
	Indian_001_path.PushBack({ 2, 0 }, 100, &walking);

}

void Enemy_Indian_001::Update()
{

	if (state != EN_ST_DYING)
		position = orig_pos + Indian_001_path.GetCurrentSpeed(&animation);
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
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 40, position.y - 100, COLLIDER_ENEMY_SHOT);
		state = EN_ST_WALKING;
	}
}


#include "Application.h"
#include "Enemy_indian_002.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleSceneSpace.h"
#include "p2Point.h"
#include "ModuleParticles.h"

Enemy_Indian_002::Enemy_Indian_002(int x, int y) : Enemy(x, y)
{
	walking_right.PushBack({ 0, 32, 54, 115 });
	walking_right.PushBack({ 68, 31, 79, 115 });
	walking_right.PushBack({ 163, 33, 96, 112 });
	walking_right.PushBack({ 270, 31, 51, 115 });
	walking_right.PushBack({ 335, 32, 77, 115 });
	walking_right.PushBack({ 422, 34, 96, 112 });
	walking_right.speed = 0.1f;

	walking_left.PushBack({ 1215, 28, 54, 115 });
	walking_left.PushBack({ 1110, 27, 79, 115 });
	walking_left.PushBack({ 996, 30, 96, 112 });
	walking_left.PushBack({ 934, 29, 51, 115 });
	walking_left.PushBack({ 843, 30, 77, 115 });
	walking_left.PushBack({ 737, 31, 96, 112 });
	walking_left.speed = 0.1f;

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


	Indian_002_path.PushBack({ -2, 0 }, 100, &walking_right);
	Indian_002_path.PushBack({ 0, 0 }, 100, &shooting);
	Indian_002_path.PushBack({ 2, 0 }, 500, &walking_left);

}

void Enemy_Indian_002::Update()
{

	if (state != EN_ST_DYING)
		position = orig_pos + Indian_002_path.GetCurrentSpeed(&animation);
	else if (state == EN_ST_DYING && animation != &dying)
		animation = &dying;


	if (last_anim != animation){

		if (animation == &walking_left || animation == &walking_right)
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
		App->particles->AddParticle(App->particles->shot_flare, position.x + 17, position.y - 100);
		state = EN_ST_WALKING;
	}
}


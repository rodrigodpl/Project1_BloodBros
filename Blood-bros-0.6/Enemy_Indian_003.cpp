#include "Application.h"
#include "Enemy_indian_003.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleSceneSpace.h"
#include "p2Point.h"
#include "ModuleParticles.h"

Enemy_Indian_003::Enemy_Indian_003(int x, int y) : Enemy(x, y)
{
	walking_left.PushBack({ 1494, 89, 34, 74 });
	walking_left.PushBack({ 1537, 89, 51, 73 });
	walking_left.PushBack({ 1598, 90, 61, 71 });
	walking_left.PushBack({ 1666, 89, 33, 73 });
	walking_left.PushBack({ 1708, 89, 49, 74 });
	walking_left.PushBack({ 1764, 91, 61, 71 });
	walking_left.speed = 0.1f;

	walking_right.PushBack({ 2271, 87, 34, 74 });
	walking_right.PushBack({ 2204, 86, 50, 74 });
	walking_right.PushBack({ 2131, 89, 61, 71 });
	walking_right.PushBack({ 2091, 88, 33, 73 });
	walking_right.PushBack({ 2033, 89, 49, 72 });
	walking_right.PushBack({ 1965, 89, 61, 72 });
	walking_right.speed = 0.1f;


	falling.PushBack({ 1398, 578, 76, 92 });
	falling.PushBack({ 1488, 578, 65, 95 });
	falling.PushBack({ 1571, 578, 46, 93 });
	falling.speed = 0.1f;


	shooting.PushBack({ 1832, 89, 63, 72 });
	shooting.PushBack({ 1904, 75, 52, 86 });
	shooting.PushBack({ 1832, 89, 63, 72 });
	shooting.speed = 0.05f;
	shooting.loop = false;

	dying.PushBack({ 1582, 213, 54, 60 });
	dying.PushBack({ 1652, 218, 65, 51 });
	dying.PushBack({ 1744, 253, 65, 14 });
	dying.speed = 0.15f;
	dying.loop = false;

	collider = App->collision->AddCollider({ position.x, position.y - 116, 55, 116 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;


	Indian_003_path.PushBack({ 2, 0 }, 150, &walking_right);
	Indian_003_path.PushBack({ 0, 0 }, 100, &shooting);
	Indian_003_path.PushBack({ -2, 0 }, 900, &walking_left);

	Indian_003_Falling_path.PushBack({ 0, 2 }, 200, &falling);

}

void Enemy_Indian_003::Update()
{

	if (App->scene_space->is_backgr_destroyed && position.y < SCREEN_HEIGHT - 270 && state != EN_ST_FALLING){
		state = EN_ST_FALLING;
		orig_pos = position;
		Indian_003_path.Reset();
	}
	else if (position.y >= SCREEN_HEIGHT - 250 && state == EN_ST_FALLING){
		position.y = SCREEN_HEIGHT - 250;
		orig_pos = position;
		state = EN_ST_WALKING;
	}


	if (state != EN_ST_DYING){
		if (state == EN_ST_FALLING){
			position = orig_pos + Indian_003_Falling_path.GetCurrentSpeed(&animation);
			return;
		}
		else
			position = orig_pos + Indian_003_path.GetCurrentSpeed(&animation);
	}
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
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 40, position.y - 60, COLLIDER_ENEMY_SHOT);
		state = EN_ST_WALKING;
	}
}


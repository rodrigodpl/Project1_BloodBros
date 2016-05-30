#include "Application.h"
#include "Enemy_Cart_001.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleSceneSpace.h"
#include "p2Point.h"
#include "ModuleParticles.h"

Enemy_Cart_001::Enemy_Cart_001(int x, int y) : Enemy(x, y)
{

	walking_left.PushBack({ 42, 1109, 86, 76 });
	walking_left.PushBack({ 139, 1108, 86, 77 });
	walking_left.PushBack({ 246, 1109, 86, 76 });
	walking_left.PushBack({ 348, 1108, 87, 77 });
	walking_left.speed = 0.1f;


	shooting.PushBack({ 445, 1110, 93, 75 });
	shooting.PushBack({ 550, 1113, 99, 71 });
	shooting.PushBack({ 48, 1224, 101, 67 });
	shooting.PushBack({ 195, 1223, 105, 68 });
	shooting.PushBack({ 342, 1223, 104, 68 });
	shooting.PushBack({ 477, 1223, 104, 68 });
	shooting.PushBack({ 477, 1223, 104, 68 });
	shooting.PushBack({ 342, 1223, 104, 68 });
	shooting.PushBack({ 195, 1223, 105, 68 });
	shooting.PushBack({ 48, 1224, 101, 67 });
	shooting.PushBack({ 550, 1113, 99, 71 });
	shooting.PushBack({ 445, 1110, 93, 75 });
	shooting.speed = 0.1f;
	shooting.loop = false;



	dying.PushBack({ 42, 1109, 86, 76 });
	dying.speed = 0.15f;
	dying.loop = false;


	collider = App->collision->AddCollider({ position.x, position.y - 80, 55, 80 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;


	Cart_001_path.PushBack({ -2, 0 }, 100, &walking_left);
	Cart_001_path.PushBack({ 0, 0 }, 100, &shooting);
	Cart_001_path.PushBack({ -2, 0 }, 100, &walking_left);
	Cart_001_path.PushBack({ 0, 0 }, 100, &shooting);
	Cart_001_path.PushBack({ -2, 0 }, 100, &walking_left);
	Cart_001_path.PushBack({ 0, 0 }, 100, &shooting);
	Cart_001_path.PushBack({ -2, 0 }, 500, &walking_left);

}

void Enemy_Cart_001::Update()
{

	if (state != EN_ST_DYING)
		position = orig_pos + Cart_001_path.GetCurrentSpeed(&animation);
	else if (state == EN_ST_DYING && animation != &dying)
		animation = &dying;


	if (last_anim != animation){

		if (animation == &walking_left)
			state = EN_ST_WALKING;
		else if (animation == &dying)
			state = EN_ST_DYING;
		else if (animation == &shooting)
			state = EN_ST_SHOOTING;

		last_anim = animation;
		animation->Reset();

	}


	if (state == EN_ST_SHOOTING && ((animation->current_frame) > (animation->last_frame / 2))){
		App->particles->AddParticle(App->particles->dynamite, position.x + 50, position.y - 80, COLLIDER_ENEMY_BOMB);
		state = EN_ST_WALKING;
	}
}


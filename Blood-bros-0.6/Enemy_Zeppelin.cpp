#include "Application.h"
#include "Enemy_Zeppelin.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleSceneSpace.h"
#include "ModuleParticles.h"
#include "p2Point.h"

Enemy_Zeppelin::Enemy_Zeppelin(int x, int y) : Enemy(x, y)
{

	walking.PushBack({ 32, 1713, 307, 121 });
	walking.speed = 0.1f;

	shooting.PushBack({ 374, 1714, 307, 122 });
	shooting.PushBack({ 701, 1714, 307, 122 });
	shooting.PushBack({ 1038, 1713, 308, 121 });
	shooting.PushBack({ 1038, 1713, 308, 121 });
	shooting.PushBack({ 1038, 1713, 308, 121 });
	shooting.PushBack({ 1038, 1713, 308, 121 });
	shooting.PushBack({ 1038, 1713, 308, 121 });
	shooting.PushBack({ 1038, 1713, 308, 121 });
	shooting.PushBack({ 1038, 1713, 308, 121 });
	shooting.PushBack({ 701, 1714, 307, 122 });
	shooting.PushBack({ 374, 1714, 307, 122 });
	shooting.PushBack({ 32, 1713, 307, 121 });
	shooting.speed = 0.1f;
	shooting.loop = false;


	dying.PushBack({ 32, 1713, 307, 121 });
	dying.speed = 0.15f;
	dying.loop = false;


	collider = App->collision->AddCollider({ position.x, position.y - 121, 307, 121 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;

	has_shot_1 = false, has_shot_2 = false, has_shot_3 = false;

	Zeppelin_001_path.PushBack({ 0, 0 }, 160, &appearing);
	Zeppelin_001_path.PushBack({ 0, 0 }, 220, &shooting);
	Zeppelin_001_path.PushBack({ -1, 0 }, 150, &walking);
	Zeppelin_001_path.PushBack({ 0, 0 }, 220, &shooting);
	Zeppelin_001_path.PushBack({ -1, 0 }, 150, &walking);
	Zeppelin_001_path.PushBack({ 0, 0 }, 220, &shooting);
	Zeppelin_001_path.PushBack({ -1, 0 }, 700, &walking);

	appearing_factor = 307;

}

void Enemy_Zeppelin::Update()
{

	if (animation == &appearing){
		Animation aux_appear;
		aux_appear.PushBack({ 32, 1713 , 307 - appearing_factor, 122 });
		appearing_factor -= 2;
		position.x -= 2;
		appearing = aux_appear;
		orig_pos = position;
		state = EN_ST_PROTECTING;
	}
	

	if (state != EN_ST_DYING)
		position = orig_pos + Zeppelin_001_path.GetCurrentSpeed(&animation);
	else if (state == EN_ST_DYING && animation != &dying)
		animation = &dying;

	if (last_anim != animation){

		if (animation == &walking){
			state = EN_ST_WALKING;
			has_shot_1 = false, has_shot_2 = false, has_shot_3 = false;
		}
		else if (animation == &dying)
			state = EN_ST_DYING;
		else if (animation == &shooting)
			state = EN_ST_SHOOTING;

		last_anim = animation;
		animation->Reset();

	}

	if (state == EN_ST_SHOOTING){

		if (animation->current_frame > 4 && has_shot_1 == false){
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 150, position.y, COLLIDER_ENEMY_SHOT);
			has_shot_1 = true;
		}
		else if (animation->current_frame > 6 && has_shot_2 == false){
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 150, position.y, COLLIDER_ENEMY_SHOT);
			has_shot_2 = true;
		}
		else if (animation->current_frame > 8 && has_shot_3 == false){
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 150, position.y, COLLIDER_ENEMY_SHOT);
			has_shot_3 = true;
		}
	}

}


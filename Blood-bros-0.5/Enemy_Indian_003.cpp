#include "Application.h"
#include "Enemy_indian_003.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleSceneSpace.h"
#include "p2Point.h"
#include "ModuleParticles.h"

Enemy_Indian_003::Enemy_Indian_003(int x, int y) : Enemy(x, y)
{
	walking_left.PushBack({ 601, 578, 44, 93 });
	walking_left.PushBack({ 653, 578, 67, 92 });
	walking_left.PushBack({ 731, 578, 78, 90 });
	walking_left.PushBack({ 815, 578, 44, 93 });
	walking_left.PushBack({ 868, 578, 78, 115 });
	walking_left.PushBack({ 939, 578, 76, 89 });
	walking_left.speed = 0.1f;

	walking_right.PushBack({ 1187, 578, 80, 92 });
	walking_right.PushBack({ 1273, 578, 65, 91 });
	walking_right.PushBack({ 1348, 578, 42, 94 });
	walking_right.PushBack({ 1398, 578, 76, 92 });
	walking_right.PushBack({ 1488, 578, 65, 95 });
	walking_right.PushBack({ 1571, 578, 46, 93 });
	walking_right.speed = 0.1f;


	shooting.PushBack({ 1024, 576, 80, 93 });
	shooting.PushBack({ 1113, 554, 66, 115 });
	shooting.speed = 0.05f;
	shooting.loop = false;



	collider = App->collision->AddCollider({ position.x, position.y - 116, 55, 116 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;


	Indian_003_path.PushBack({ 2, 0 }, 150, &walking_right);
	Indian_003_path.PushBack({ 0, 0 }, 100, &shooting);
	Indian_003_path.PushBack({ -2, 0 }, 700, &walking_left);

}

void Enemy_Indian_003::Update()
{

	position = orig_pos + Indian_003_path.GetCurrentSpeed(&animation);

	if (animation == &shooting && !(has_shot)){
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 40, position.y - 100, COLLIDER_ENEMY_SHOT, 100);
		has_shot = true;
	}
	else if (animation != &shooting){
		has_shot = false;
		shooting.Reset();
	}
}

void Enemy_Indian_003::Die(){

	App->particles->AddParticle(App->particles->indian_dying, position.x, position.y);
	App->scene_space->defeated_enemies++;


}
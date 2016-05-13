#include "Application.h"
#include "Enemy_indian_001.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleSceneSpace.h"
#include "ModuleParticles.h"
#include "p2Point.h"

Enemy_Indian_001::Enemy_Indian_001(int x, int y) : Enemy(x, y)
{
	walking.PushBack({ 1240, 47, 55, 116 });
	walking.PushBack({ 762, 49, 96, 114 });
	walking.PushBack({ 868, 49, 78, 115 });
	walking.PushBack({ 959, 48, 52, 116 });
	walking.PushBack({ 1021, 49, 97, 112 });
	walking.PushBack({ 1136, 46, 80, 116 });
	walking.speed = 0.1f;

	shooting.PushBack({ 554, 50, 100, 113 });
	shooting.PushBack({ 666, 19, 82, 145 });
	shooting.PushBack({ 554, 50, 100, 113 });
	shooting.speed = 0.05f;
	shooting.loop = false;

	falling.PushBack({ 559, 189, 52, 154 });
	falling.PushBack({ 654, 253, 74, 81 });
	falling.speed = 0.05f;
	falling.loop = false;

	collider = App->collision->AddCollider({ position.x, position.y - 116, 55, 116 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;


	Indian_001_path.PushBack({ 2, 0 }, 100, &walking);
	Indian_001_path.PushBack({ 0, 0 }, 100, &shooting);
	Indian_001_path.PushBack({ 2, 0 }, 100, &walking);

}

void Enemy_Indian_001::Update()
{

	position = orig_pos + Indian_001_path.GetCurrentSpeed(&animation);

	if (animation == &shooting && !(has_shot)){
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 40, position.y - 100, COLLIDER_ENEMY_SHOT, 700);
		has_shot = true;
	}
	else if (animation != &shooting){
		has_shot = false;
		shooting.Reset();
	}
}

void Enemy_Indian_001::Die(){

	App->particles->AddParticle(App->particles->indian_dying, position.x, position.y);
	App->scene_space->defeated_enemies++;


}
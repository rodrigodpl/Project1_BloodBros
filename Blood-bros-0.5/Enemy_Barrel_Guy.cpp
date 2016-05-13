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

	protect.PushBack({ 456, 723, 55, 133 });
	protect.PushBack({ 101, 875, 57, 98 });
	protect.PushBack({ 215, 904, 55, 70 });	
	protect.PushBack({ 215, 904, 55, 70 });
	protect.PushBack({ 101, 875, 57, 98 });
	protect.PushBack({ 456, 723, 55, 133 });
	protect.speed = 0.1f;
	protect.loop = false;

	shooting.PushBack({ 90, 712, 77, 142 });
	shooting.PushBack({ 206, 715, 76, 139 });
	shooting.PushBack({ 312, 715, 88, 139 });
	shooting.PushBack({ 206, 715, 76, 139 });
	shooting.PushBack({ 90, 712, 77, 142 });
	shooting.speed = 0.1f;
	shooting.loop = false;

	collider = App->collision->AddCollider({ position.x, position.y - 138, 76, 138 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;

	Barrel_Guy_path.PushBack({ -2, 0 }, 100, &walking);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &shooting);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &protect);
	Barrel_Guy_path.PushBack({ -2, 0 }, 100, &walking);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &shooting);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &protect);
	Barrel_Guy_path.PushBack({ 2, 0 }, 100, &walking);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &shooting);
	Barrel_Guy_path.PushBack({ 0, 0 }, 100, &protect);
	Barrel_Guy_path.PushBack({ 2, 0 }, 500, &walking);

}

void Enemy_Barrel_Guy::Update()
{

	position = orig_pos + Barrel_Guy_path.GetCurrentSpeed(&animation);
	if (animation == &protect && !(is_protecting)){
		is_protecting = true;
	}
	else if(animation != &protect && is_protecting){
		is_protecting = false;
		protect.Reset();
	}

	if (animation == &shooting && !(has_shot)){
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 25, position.y - 120, COLLIDER_ENEMY_SHOT, 400);
		has_shot = true;
	}
	else if (animation != &shooting){
		has_shot = false;
		shooting.Reset();
	}
}

void Enemy_Barrel_Guy::Die(){

	App->particles->AddParticle(App->particles->barrel_guy_dying, position.x, position.y);
	App->scene_space->defeated_enemies++;


}
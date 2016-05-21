#include "Application.h"
#include "Scenario_elem.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"

Scenario_elem::Scenario_elem(int x, int y) : position(x, y), collider(nullptr)
{}

Scenario_elem::~Scenario_elem()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

const Collider* Scenario_elem::GetCollider() const
{
	return collider;
}

void Scenario_elem::Draw(SDL_Texture* scenario_sprites)
{

	collider->SetPos(position.x, position.y);
		
	if (animation == &dying){
		position.x += anim_displacement_x;
		position.y += anim_displacement_y;
	}

	App->render->Blit(scenario_sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}



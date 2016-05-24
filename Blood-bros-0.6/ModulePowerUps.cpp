#include "ModulePowerUps.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "ModuleUI.h"
#include "ModuleReticle.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL.h"



ModulePowerUps::ModulePowerUps()
{
	for (uint i = 0; i < MAX_POWER_UPS; ++i)
		active_power_ups[i] = nullptr;
}


bool ModulePowerUps::Start()
{
	power_up_sprites = App->textures->Load("power_ups_spritesheet.png");

	points_1000_anim.PushBack({ 0, 123, 80, 48 });
	points_1000_anim.PushBack({ 154, 123, 80, 48 });
	points_1000_anim.speed = 0.2f;

	points_5000_anim.PushBack({ 294, 115, 104, 56 });
	points_5000_anim.PushBack({ 430, 115, 104, 56 });
	points_5000_anim.speed = 0.2f;

	points_7000_anim.PushBack({ 566, 115, 104, 56 });
	points_7000_anim.PushBack({ 702, 115, 104, 56 });
	points_7000_anim.speed = 0.2f;

	points_10000_anim.PushBack({ 834, 107, 156, 64});
	points_10000_anim.PushBack({ 1038, 107, 156, 64});
	points_10000_anim.speed = 0.2f;

	points_20000_anim.PushBack({ 1244, 107, 160, 64 });
	points_20000_anim.PushBack({ 1452, 107, 160, 64 });
	points_20000_anim.speed = 0.2f;

	machinegun_anim.PushBack({ 282, 0, 192, 64 });
	machinegun_anim.PushBack({ 486, 0, 192, 64 });
	machinegun_anim.speed = 0.2f;

	shotgun_anim.PushBack({ 6, 0, 128, 64 });
	shotgun_anim.PushBack({ 146, 0, 128, 64 });
	shotgun_anim.speed = 0.2f;

	dynamite_anim.PushBack({ 699, 0, 64, 64 });
	dynamite_anim.PushBack({ 767, 0, 64, 64 });
	dynamite_anim.speed = 0.2f;

	extralive_anim.PushBack({ 835, 0, 64, 64 });
	extralive_anim.PushBack({ 903, 0, 64, 64 });
	extralive_anim.speed = 0.2f;
									
	return true;
}

bool ModulePowerUps::CleanUp()
{
	App->textures->Unload(power_up_sprites);

	for (uint i = 0; i < MAX_POWER_UPS; ++i)
	{
		if (active_power_ups[i] != nullptr)
		{
			delete active_power_ups[i];
			active_power_ups[i] = nullptr;
		}
	}

	return true;
}

update_status ModulePowerUps::Update(){

	for (uint i = 0; i < MAX_POWER_UPS; ++i){

		if (active_power_ups[i] != nullptr){

			if (SDL_GetTicks() - POWER_UP_LIFE > active_power_ups[i]->born){
				App->collision->EraseCollider(active_power_ups[i]->PU_collider);
				delete active_power_ups[i];
				active_power_ups[i] = nullptr;
			}
			else{

				if (active_power_ups[i]->position.y < SCREEN_HEIGHT - 100){
					active_power_ups[i]->y_speed -= CONST_GRAVITY;
					active_power_ups[i]->position.y += active_power_ups[i]->y_speed;
					active_power_ups[i]->PU_collider->SetPos(active_power_ups[i]->position.x, active_power_ups[i]->position.y);
				}
				else if (active_power_ups[i]->position.y < SCREEN_HEIGHT - 100)
					active_power_ups[i]->position.y = SCREEN_HEIGHT - 100;


				SDL_Rect r = active_power_ups[i]->anim->GetCurrentFrame();

				App->render->Blit(power_up_sprites, active_power_ups[i]->position.x, active_power_ups[i]->position.y, &r);
			}
		}
	}

	return UPDATE_CONTINUE;
}

bool ModulePowerUps::AddPU(uint type, int x, int y){

	for (uint i = 0; i < MAX_POWER_UPS; ++i){

		if (active_power_ups[i] == nullptr){

			active_power_ups[i] = new Power_up;

			active_power_ups[i]->type = type;
			active_power_ups[i]->position.x = x;
			active_power_ups[i]->position.y = y;
			active_power_ups[i]->born = SDL_GetTicks();
			active_power_ups[i]->PU_collider = App->collision->AddCollider({ active_power_ups[i]->position.x, 
				active_power_ups[i]->position.y, 110, 56 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->power_ups);

			switch (type){

			case POINTS_1000: active_power_ups[i]->anim = &points_1000_anim; break;
			case POINTS_5000: active_power_ups[i]->anim = &points_5000_anim; break;
			case POINTS_7000: active_power_ups[i]->anim = &points_7000_anim; break;
			case POINTS_10000: active_power_ups[i]->anim = &points_10000_anim; break;
			case POINTS_20000: active_power_ups[i]->anim = &points_20000_anim; break;
			case DYNAMITE_PU: active_power_ups[i]->anim = &dynamite_anim; break;
			case EXTRA_LIVE: active_power_ups[i]->anim = &extralive_anim; break;
			case SHOTGUN_PU: active_power_ups[i]->anim = &shotgun_anim; break;
			case MACHINEGUN_PU: active_power_ups[i]->anim = &machinegun_anim; break;
			}
			

			break;
		}

	}

	return true;
}


void ModulePowerUps::OnCollision(Collider* c1, Collider* c2){

	for (uint i = 0; i < MAX_POWER_UPS; ++i)
	{
		if (active_power_ups[i] != nullptr && active_power_ups[i]->PU_collider == c1)
		{
			
			switch (active_power_ups[i]->type){

			case POINTS_1000: App->UI->player_score += 1000; break;
			case POINTS_5000: App->UI->player_score += 5000; break;
			case POINTS_7000: App->UI->player_score += 7000; break;
			case POINTS_10000: App->UI->player_score += 10000; break;
			case POINTS_20000: App->UI->player_score += 20000; break;
			case DYNAMITE_PU: App->UI->dynamite_num++; break;
			case EXTRA_LIVE: App->UI->p1_lives++; break;
			case SHOTGUN_PU: App->reticle->ChangeMode(SHOTGUN); break;
			case MACHINEGUN_PU: App->reticle->ChangeMode(MACHINEGUN); break;
			}

			App->collision->EraseCollider(active_power_ups[i]->PU_collider);
			delete active_power_ups[i];
			active_power_ups[i] = nullptr;

			break;
		}
	}
}




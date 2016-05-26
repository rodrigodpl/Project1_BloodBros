#include "ModuleTincan.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModulePowerUps.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

#define INITIAL_Y 383

ModuleTincan::ModuleTincan(){

	rolling_anim.PushBack({ 0, 0, 30, 48 });
	rolling_anim.PushBack({ 45, 0, 36, 48 });
	rolling_anim.PushBack({ 96, 6, 48, 30 });
	rolling_anim.PushBack({ 147, 0, 48, 36 });
	rolling_anim.PushBack({ 210, 0, 30, 48 });
	rolling_anim.PushBack({ 261, 0, 36, 48 });
	rolling_anim.PushBack({ 300, 12, 48, 30 });
	rolling_anim.PushBack({ 351, 12, 48, 36 });
	rolling_anim.speed = 0.2f;

	idle.PushBack({ 0, 0, 30, 48 });


}


bool ModuleTincan::Start(){

	first_time = true;

	position = { 420, INITIAL_Y }, speed = { 0, 0 };

	hit_counter = NO_HIT; release_timer = 0;

	tincan_sprites = App->textures->Load("tincan_spritesheet.png");

	tincan_col = App->collision->AddCollider({ position.x, position.y, 40, 40 }, COLLIDER_TINCAN, this);

	return true;
}

bool ModuleTincan::CleanUp(){

	App->textures->Unload(tincan_sprites);
	App->collision->EraseCollider(tincan_col);

	return true;

}


update_status ModuleTincan::Update(){

	

	SDL_Rect r = idle.GetCurrentFrame();

	if (hit_counter != NO_HIT){
		if (position.y <= INITIAL_Y){
			speed.y -= ((float) 0.3 * CONST_GRAVITY);
			position += speed;
			r = rolling_anim.GetCurrentFrame();
		}
		else{
			position.y = 383;
			hit_counter = NO_HIT;
			first_time = false;
		}
	}

	tincan_col->SetPos(position.x, position.y);

	

	App->render->Blit(tincan_sprites, position.x, position.y, &r);

	return UPDATE_CONTINUE;
}

void ModuleTincan::OnCollision(Collider* c1, Collider* c2){

	if (tincan_col == c1 && App->player->shooting && SDL_GetTicks() - 500 > release_timer){

		if (hit_counter != LAST_HIT)
			hit_counter++;

		switch (hit_counter){

		case THREE_HIT: App->power_ups->AddPU(POINTS_1000, position.x, position.y); break;
		case FOUR_HIT: App->power_ups->AddPU(POINTS_5000, position.x, position.y); break;
		case FIVE_HIT: App->power_ups->AddPU(POINTS_7000, position.x, position.y); break;
		case SIX_HIT: App->power_ups->AddPU(POINTS_10000, position.x, position.y); break;
		case SEVEN_HIT: App->power_ups->AddPU(POINTS_20000, position.x, position.y); break;
		case LAST_HIT:
			if (first_time){
				App->power_ups->AddPU(EXTRA_LIFE, position.x, position.y);
				first_time = false;
			}
			else
				App->power_ups->AddPU(POINTS_20000, position.x, position.y);
			break;
		}

		speed.y = -10;

		if (speed.x == 0 || speed.x == 5)
			speed.x = -5;
		else
			speed.x = 5;

		release_timer = SDL_GetTicks();
	}
	
}
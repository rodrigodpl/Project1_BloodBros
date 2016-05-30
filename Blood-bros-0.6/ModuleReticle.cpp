#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleDebug.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleReticle.h"
#include "SDL\include\SDL.h"


ModuleReticle::ModuleReticle()
{
	graphics = NULL;
	current_animation = &basic_idle;

	position.x = 150;
	position.y = 80;

	// idle animation (just the ship)
	basic_idle.PushBack({ 0, 0, 65, 60 });
	basic_idle.PushBack({ 88, 0, 65, 60 });
	basic_idle.speed = 0.1f;

	basic_shooting.PushBack({ 218, 0, 65, 60 });
	basic_shooting.PushBack({ 306, 0, 65, 60 });
	basic_shooting.PushBack({ 376, 0, 65, 60 });
	basic_shooting.PushBack({ 468, 0, 65, 60 });
	basic_shooting.PushBack({ 536, 0, 65, 60 });
	basic_shooting.PushBack({ 640, 0, 65, 60 });
	basic_shooting.speed = 0.3f;

	shotgun_idle.PushBack({ 0, 0, 65, 60 });
	shotgun_idle.PushBack({ 88, 0, 65, 60 });
	shotgun_idle.speed = 0.1f;

	shotgun_shooting.PushBack({ 218, 0, 65, 60 });
	shotgun_shooting.PushBack({ 306, 0, 65, 60 });
	shotgun_shooting.PushBack({ 376, 0, 65, 60 });
	shotgun_shooting.PushBack({ 468, 0, 65, 60 });
	shotgun_shooting.PushBack({ 536, 0, 65, 60 });
	shotgun_shooting.PushBack({ 640, 0, 65, 60 });
	shotgun_shooting.speed = 0.2f;

	machinegun_idle.PushBack({ 0, 0, 65, 60 });
	machinegun_idle.PushBack({ 88, 0, 65, 60 });
	machinegun_idle.speed = 0.1f;

	machinegun_shooting.PushBack({ 218, 0, 65, 60 });
	machinegun_shooting.PushBack({ 306, 0, 65, 60 });
	machinegun_shooting.PushBack({ 376, 0, 65, 60 });
	machinegun_shooting.PushBack({ 468, 0, 65, 60 });
	machinegun_shooting.PushBack({ 536, 0, 65, 60 });
	machinegun_shooting.PushBack({ 640, 0, 65, 60 });
	machinegun_shooting.speed = 0.5f;


}


bool ModuleReticle::Start()
{
	LOG("Loading reticle");

	graphics = App->textures->Load("sprites/crossdot.png");

	basic_player_shot_fx = App->audio->LoadFx("FX/Player_Basic_Shot.wav");
	shotgun_player_shot_fx = App->audio->LoadFx("FX/shotgun-shoot.wav");
	machinegun_player_shot_fx = App->audio->LoadFx("FX/machinegun-shoot.wav");

	ret_col = App->collision->AddCollider({ position.x, position.y, 65, 60 }, COLLIDER_PLAYER_SHOT);

	mode = BASIC_SHOT;

	return true;
}

// Unload assets
bool ModuleReticle::CleanUp()
{
	LOG("Unloading reticle");

	App->textures->Unload(graphics);

	App->audio->UnLoadFx(basic_player_shot_fx);
	App->audio->UnLoadFx(shotgun_player_shot_fx);
	App->audio->UnLoadFx(machinegun_player_shot_fx);

	App->collision->EraseCollider(ret_col);

	return true;
}

// Update: draw background
update_status ModuleReticle::Update()
{
	int xspeed = 0;
	int yspeed = 0;

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
		xspeed = 8;
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
		xspeed = -8;
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE)
		yspeed = -8;
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		yspeed = 8;

	if (position.x + xspeed > 0 && position.x + xspeed < SCREEN_WIDTH - 70)
		position.x += xspeed;

	if (position.y + yspeed > 0 && position.y + yspeed < SCREEN_HEIGHT - 250)
		position.y += yspeed;


	switch (mode){
	case BASIC_SHOT:
		if (App->player->shooting && App->player->alive && current_animation != &basic_shooting){
			App->audio->PlayFx(basic_player_shot_fx);
			current_animation = &basic_shooting;
		}
		else if (current_animation == &basic_shooting && current_animation->Finished()){
			current_animation->Reset();
			current_animation = &basic_idle;
		}
		break;

	case SHOTGUN:
		if (App->player->shooting && App->player->alive && current_animation != &shotgun_shooting){
			App->audio->PlayFx(shotgun_player_shot_fx);
			current_animation = &shotgun_shooting;
		}
		else if (current_animation == &shotgun_shooting && current_animation->Finished()){
			current_animation->Reset();
			current_animation = &shotgun_idle;
		}

		if (SDL_GetTicks() - mode_life > mode_timer)
			ChangeMode(BASIC_SHOT);

		break;

	case MACHINEGUN:
		if (App->player->shooting && App->player->alive && current_animation != &machinegun_shooting){
			App->audio->PlayFx(machinegun_player_shot_fx);
			current_animation = &machinegun_shooting;
		}
		else if (current_animation == &machinegun_shooting && current_animation->Finished()){
			current_animation->Reset();
			current_animation = &machinegun_idle;
		}

		if (SDL_GetTicks() - mode_life > mode_timer && App->debug->activated_functions[RAMBO_MODE_F7])
			ChangeMode(BASIC_SHOT);

		break;
	}

	if (App->player->current_animation == &App->player->victory_dance){
		current_animation->Reset();
		current_animation = &basic_idle;
	}

	ret_col->SetPos(position.x, position.y);


	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModuleReticle::ChangeMode(modes new_mode){

	if (mode == new_mode)
		mode_life += 10000;
	else{
		mode = new_mode;
		mode_life = INIT_MODE_LIFE;
		mode_timer = SDL_GetTicks();
	}
}
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleReticle.h"
#include "SDL\include\SDL.h"


ModuleReticle::ModuleReticle()
{
	graphics = NULL;
	current_animation = &idle;

	position.x = 150;
	position.y = 80;

	// idle animation (just the ship)
	idle.PushBack({ 0, 0, 65, 60 });
	idle.PushBack({ 88, 0, 65, 60 });
	idle.speed = 0.1f;

	shooting.PushBack({ 218, 0, 65, 60 });
	shooting.PushBack({ 306, 0, 65, 60 });
	shooting.PushBack({ 376, 0, 65, 60 });
	shooting.PushBack({ 468, 0, 65, 60 });
	shooting.PushBack({ 536, 0, 65, 60 });
	shooting.PushBack({ 640, 0, 65, 60 });
	shooting.speed = 0.3f;


}


bool ModuleReticle::Start()
{
	LOG("Loading reticle");

	graphics = App->textures->Load("crossdot.png");

	player_shot_fx = App->audio->LoadFx("FX/Player_Basic_Shot.wav");

	ret_col = App->collision->AddCollider({ position.x, position.y, 65, 60 }, COLLIDER_PLAYER_SHOT);

	return true;
}

// Unload assets
bool ModuleReticle::CleanUp()
{
	LOG("Unloading reticle");

	App->textures->Unload(graphics);

	App->audio->UnLoadFx(player_shot_fx);

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


	if (App->player->shooting && App->player->alive && current_animation != &shooting){
		App->audio->PlayFx(player_shot_fx);
		current_animation = &shooting;
	}
	else if (current_animation == &shooting && current_animation->Finished()){
		current_animation->Reset();
		current_animation = &idle;
	}


	ret_col->SetPos(position.x, position.y);


	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}
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
	idle.PushBack({ 7, 8, 67, 71 });
	idle.PushBack({ 95, 8, 67, 71 });
	idle.speed = 0.1f;


}

ModuleReticle::~ModuleReticle()
{}

// Load assets
bool ModuleReticle::Start()
{
	LOG("Loading reticle");

	graphics = App->textures->Load("crossdot.png");

	player_shot_fx = App->audio->LoadFx("FX/Player_Basic_Shot.wav");

	timer = SDL_GetTicks();

	ret_col = App->collision->AddCollider({ position.x, position.y, 67, 60 }, COLLIDER_PLAYER_SHOT);

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

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		xspeed = 8;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		xspeed = -8;
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		yspeed = -8;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		yspeed = 8;
	}

	if (position.x + xspeed > 0 && position.x + xspeed < SCREEN_WIDTH - 70){
		position.x += xspeed;
	}

	if (position.y + yspeed > 0 && position.y + yspeed < SCREEN_HEIGHT - 250){
		position.y += yspeed;
	}

	// TODO 3: Shoot lasers when the player hits SPACE

	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT && App->player->alive)
	{
		App->audio->PlayFx(player_shot_fx);
		if ((SDL_GetTicks() - timer) > 400){
			App->particles->AddParticle(App->particles->player_shot, position.x + 5, position.y + 20);
			timer = SDL_GetTicks();
		}
	}
	else{
		current_animation = &idle;
	}

	ret_col->SetPos(position.x, position.y);



	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}
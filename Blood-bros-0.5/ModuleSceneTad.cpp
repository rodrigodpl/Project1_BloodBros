#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "SDL\include\SDL.h"
#include "ModuleSceneTad.h"



ModuleSceneTad::ModuleSceneTad()
{}

ModuleSceneTad::~ModuleSceneTad()
{}

// Load assets
bool ModuleSceneTad::Start()
{
	LOG("Loading space intro");

	background = App->textures->Load("TadCorporation_background.png");

	App->render->camera.x = App->render->camera.y = 0;

	timer = SDL_GetTicks();

	return true;
}

// UnLoad assets
bool ModuleSceneTad::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);


	return true;
}

// Update: draw background
update_status ModuleSceneTad::Update()
{
	App->render->Blit(background, 0, 0, NULL);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_stage_pres);
	}

	if (SDL_GetTicks() - timer > 6000){
		App->fade->FadeToBlack(this, (Module*)App->scene_welcome);
	}


	return UPDATE_CONTINUE;
}
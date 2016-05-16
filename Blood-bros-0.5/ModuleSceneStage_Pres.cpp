#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "SDL\include\SDL.h"
#include "ModuleSceneStage_Pres.h"

#define TIME_TO_SWAP 8000


bool ModuleSceneStage_Pres::Start()
{
	LOG("Loading space intro");

	background = App->textures->Load("stage_pres_background.png");

	App->audio->PlayMusic("Music/startscreen.wav");

	App->render->camera.x = App->render->camera.y = 0;

	timer = SDL_GetTicks();

	return true;
}

// UnLoad assets
bool ModuleSceneStage_Pres::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);


	return true;
}

// Update: draw background
update_status ModuleSceneStage_Pres::Update()
{
	App->render->Blit(background, 0, 0, NULL);

	if (SDL_GetTicks() - timer > TIME_TO_SWAP)
		App->fade->FadeToBlack(this, (Module*)App->scene_space);

	return UPDATE_CONTINUE;
}
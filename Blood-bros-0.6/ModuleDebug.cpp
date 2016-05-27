#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "ModuleSceneSpace.h"
#include "ModuleFadeToBlack.h"
#include "ModuleReticle.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "ModuleDebug.h"
#include "ModuleInput.h"


bool ModuleDebug::Start(){


	for (uint i = 0; i < MAX_DEBUG_FUNC; i++)
		activated_functions[i] = false;

	return(true);

}


update_status ModuleDebug::Update(){

	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		activated_functions[DRAW_COLLIDERS_F1] = !(activated_functions[DRAW_COLLIDERS_F1]);

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN)
		activated_functions[GOD_MODE_F2] = !(activated_functions[GOD_MODE_F2]);

	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN){

		activated_functions[NO_ENEMIES_F3] = !(activated_functions[NO_ENEMIES_F3]);

		if (activated_functions[NO_ENEMIES_F3])
			App->enemies->Disable();
		else{
			App->enemies->Enable();
			App->scene_space->loop_enemies();
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_DOWN){

		activated_functions[NO_PLAYER_F4] = !(activated_functions[NO_PLAYER_F4]);

		if (activated_functions[NO_PLAYER_F4]){
			App->player->Disable();
			App->reticle->Disable();
		}
		else{
			App->player->Enable();
			App->reticle->Enable();
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN){

		Mix_FadeOutMusic(1000);

		App->player->speed = 0;
		App->player->current_animation = &(App->player->killed);

		App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_score, 3);

		App->player->alive = false;

	}

	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_DOWN)
		activated_functions[INSTA_WIN_F6] = true;

	if (activated_functions[INSTA_WIN_F6] == true){
		if (App->player->current_animation != &App->player->victory_dance){
			App->player->current_animation->Reset();
			App->player->current_animation = &App->player->victory_dance;
		}

		if (App->player->current_animation->Finished()){
			Mix_FadeOutMusic(1000);
			App->fade->FadeToBlack((Module*) App->scene_space, (Module*)App->scene_score);
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_DOWN){
		activated_functions[RAMBO_MODE_F7] = !(activated_functions[RAMBO_MODE_F7]);

		if (activated_functions[RAMBO_MODE_F7])
			App->reticle->ChangeMode(MACHINEGUN);
	}


		return(UPDATE_CONTINUE);

}


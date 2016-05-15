#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleSceneSpace.h"
#include "ModuleReticle.h"
#include "ModulePlayer.h"
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



		return(UPDATE_CONTINUE);

}


#include "Application.h"
#include "ModuleFonts.h"
#include "ModuleSceneSpace.h"
#include "ModuleUI.h"
#include <stdio.h>


bool ModuleUI::Start(){

	player_score = 0;

	text_manager = new ModuleFonts();

	//white font:
	text_manager->Load("font.png", "!@#$%&º()*+,-./0123456789$:;<=>?ªABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_'abcdefghijklmnopqrstuvwxyz·?& ¬", 1);
	// ª == (C); ¬ == · (big);
	return true;

}


update_status ModuleUI::Update(){

	if (App->scene_space->IsEnabled()){
		sprintf_s(score_text, 10, "%7d", player_score);
		text_manager->Blit(200, SCREEN_HEIGHT - 40, WHITE_FONT, score_text);
	}


	return UPDATE_CONTINUE;

}


bool ModuleUI::CleanUp(){

	text_manager->UnLoad(WHITE_FONT);

	delete text_manager;

	return true;
}
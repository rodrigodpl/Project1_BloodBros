#include "Application.h"
#include "ModuleFonts.h"
#include "ModuleSceneSpace.h"
#include "ModuleDebug.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include <stdio.h>


bool ModuleUI::Start(){

	player_score = 0;

	p1_lifes = 1;

	dynamite_num = 10;

	text_manager = new ModuleFonts();

	UI_sprites = App->textures->Load("UI_spritesheet.png");

	FOE_letters.PushBack({ 0, 0, 0, 0 });

	FOE_bar_00.PushBack({ 0, 0, 0, 0 });
	FOE_bar_10.PushBack({ 0, 0, 0, 0 });
	FOE_bar_30.PushBack({ 0, 0, 0, 0 });
	FOE_bar_50.PushBack({ 0, 0, 0, 0 });
	FOE_bar_70.PushBack({ 0, 0, 0, 0 });
	FOE_bar_90.PushBack({ 0, 0, 0, 0 });
	FOE_bar_100.PushBack({ 0, 0, 0, 0 });

	player_life.PushBack({ 0, 0, 0, 0 });
	dynamite_logo.PushBack({ 0, 0, 0, 0 });
	p1_score_logo.PushBack({ 0, 0, 0, 0 });
	top_score_logo.PushBack({ 0, 0, 0, 0 });

	//white font:
	text_manager->Load("font.png", "!@#$%&º()*+,-./0123456789$:;<=>?ªABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_'abcdefghijklmnopqrstuvwxyz·?& ¬", 1);
	// ª == (C); ¬ == · (big);
	return true;

}


update_status ModuleUI::Update(){

	if (App->scene_space->IsEnabled()){

		SDL_Rect r = p1_score_logo.GetCurrentFrame();  //  player score

		App->render->Blit(UI_sprites, 5, 5, &r);

		sprintf_s(score_text, 10, "%7d", player_score);  
		text_manager->Blit(5 + r.w, 5, WHITE_FONT, score_text);  

		r = top_score_logo.GetCurrentFrame();  //  top score

		App->render->Blit(UI_sprites, 300, 5, &r);

		sprintf_s(score_text, 10, "%7d", player_score);
		text_manager->Blit(200 + r.w, 5, WHITE_FONT, score_text);

		r = FOE_letters.GetCurrentFrame();     // FOE

		App->render->Blit(UI_sprites, 20, SCREEN_HEIGHT - 10, &r);

		update_FOE(); 

		r = FOE_bar.GetCurrentFrame();

		App->render->Blit(UI_sprites, 30, SCREEN_HEIGHT - 10, &r);

		r = dynamite_logo.GetCurrentFrame();  //dynamite

		App->render->Blit(UI_sprites, 5, SCREEN_HEIGHT - 20, &r);
		
		if (App->debug->activated_functions[RAMBO_MODE_F7])
			text_manager->Blit(5, SCREEN_HEIGHT - 15, WHITE_FONT, "unl");
		else{
			sprintf_s(dynamite_text, 10, "%2d", dynamite_num);
			text_manager->Blit(5, SCREEN_HEIGHT - 15, WHITE_FONT, dynamite_text);
		}

		uint x_lifes = 5, y_lifes = SCREEN_HEIGHT - 10;   //player lifes

		r = player_life.GetCurrentFrame();

		for (uint i = 0; i < p1_lifes && i < 6; i++){

			App->render->Blit(UI_sprites, x_lifes, y_lifes, &r);
			x_lifes += r.w;

			if (i == 2)
				y_lifes += r.h;
		}

	}


	return UPDATE_CONTINUE;

}


bool ModuleUI::CleanUp(){

	text_manager->UnLoad(WHITE_FONT);

	App->textures->Unload(UI_sprites);

	delete text_manager;

	return true;
}

void ModuleUI::update_FOE(){

	float progress = App->scene_space->defeated_enemies / ENEMY_NUM_STG1;

	if (progress == 0){
		FOE_bar = FOE_bar_00; return;
	}
	else if (progress <= 0.1){
		FOE_bar = FOE_bar_10; return;
	}
	else if (progress <= 0.3){
		FOE_bar = FOE_bar_30; return;
	}
	else if (progress <= 0.5){
		FOE_bar = FOE_bar_50; return;
	}
	else if (progress <= 0.7){
		FOE_bar = FOE_bar_70; return;
	}
	else if (progress <= 0.9){
		FOE_bar = FOE_bar_90; return;
	}
	else 
		FOE_bar = FOE_bar_100;


}


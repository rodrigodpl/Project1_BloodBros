#include "Application.h"
#include "ModuleFonts.h"
#include "ModuleSceneSpace.h"
#include "ModuleDebug.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include <stdio.h>


bool ModuleUI::Start(){

	text_manager = new ModuleFonts();

	UI_sprites = App->textures->Load("sprites/UI_spritesheet.png");

	FOE_letters.PushBack({ 118, 67, 150, 40 });

	FOE_bar_00.PushBack({ 249, 0, 320, 40 });
	FOE_bar_10.PushBack({ 588, 0, 320, 40 });
	FOE_bar_30.PushBack({ 916, 0, 320, 40 });
	FOE_bar_50.PushBack({ 1260, 0, 320, 40 });
	FOE_bar_70.PushBack({ 249, 92, 320, 40 });
	FOE_bar_90.PushBack({ 588, 92, 320, 40 });
	FOE_bar_100.PushBack({ 916, 92, 320, 40 });

	player_life.PushBack({ 0, 347, 40, 40 });
	dynamite_logo.PushBack({ 61, 353, 75, 75 });
	p1_score_logo.PushBack({ 118, 191, 80, 40 });
	top_score_logo.PushBack({ 22, 191, 80, 40 });

	//white font:
	text_manager->Load("sprites/font.png", "!@#$%&º()*+,-./0123456789$:;<=>?ªABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_'abcdefghijklmnopqrstuvwxyz·?& ¬", 1);
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
			uint save_num_of_lifes = p1_lifes;
			sprintf_s(dynamite_text, 10, "%2d", dynamite_num);
			p1_lifes = save_num_of_lifes;
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

	float progress = (float) App->scene_space->defeated_enemies / 10;

	if (progress <= 0.1){
		FOE_bar = FOE_bar_100; return;
	}
	else if (progress <= 0.3){
		FOE_bar = FOE_bar_90; return;
	}
	else if (progress <= 0.5){
		FOE_bar = FOE_bar_70; return;
	}
	else if (progress <= 0.7){
		FOE_bar = FOE_bar_50; return;
	}
	else if (progress <= 0.9){
		FOE_bar = FOE_bar_30; return;
	}
	else if (progress < 1.0){
		FOE_bar = FOE_bar_10; return;
	}
	else 
		FOE_bar = FOE_bar_00;


}

void ModuleUI::reset(){

	player_score = 0;

	p1_lifes = 1;

	dynamite_num = 10;

}


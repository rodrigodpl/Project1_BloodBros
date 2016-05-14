#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleReticle.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScenario.h"
#include "ModuleSceneSpace.h"
#include "SDL/include/SDL.h"


ModuleSceneSpace::ModuleSceneSpace()
{}

ModuleSceneSpace::~ModuleSceneSpace()
{}

// Load assets
bool ModuleSceneSpace::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("background.png");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->reticle->Enable();
	App->scenario->Enable();

	App->audio->PlayMusic("Music/Main_Song.wav", 1.0f);
	
	// Colliders ---


	// Enemies ---
	loop_enemies();      // first loop = first wave;
	defeated_enemies = 0;
	is_backgr_destroyed = false;
	// TODO 1: Add a new wave of red birds
	App->scenario->AddElement(DESTROYABLE_WALL, 0, 44);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 255, 383);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 290, 383);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 365, 383);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 390, 383);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 455, 383);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 480, 383);
	App->scenario->AddElement(DESTROYABLE_LIGHT, 500, 0);
	App->scenario->AddElement(DESTROYABLE_LIGHT, 300, 0);
	App->scenario->AddElement(DESTROYABLE_LIGHT, 100, 0);
	App->scenario->AddElement(DESTROYABLE_BARREL, 20, 350);
	App->scenario->AddElement(DESTROYABLE_BARREL, 85, 350);
	App->scenario->AddElement(DESTROYABLE_BARREL, 170, 350);
	App->scenario->AddElement(DESTROYABLE_BARREL, SCREEN_WIDTH - 85 - 20, 355);
	App->scenario->AddElement(DESTROYABLE_BARREL, SCREEN_WIDTH - 85 - 85, 355);
	App->scenario->AddElement(DESTROYABLE_BARREL, SCREEN_WIDTH - 85 - 170, 355);


	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(background);

	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->reticle->Disable();
	App->scenario->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	if (defeated_enemies >= ENEMY_NUM_STG1 && is_backgr_destroyed){
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(this, (Module*)App->scene_score);
	}

	current_level_time = SDL_GetTicks() - init_level_time;

	if (current_level_time > 4000 && released_enemies[0] == false){
		App->enemies->AddEnemy(INDIAN_001, -20, 400);
		released_enemies[0] = true;
	}

	if (current_level_time > 6000 && released_enemies[1] == false){
		App->enemies->AddEnemy(INDIAN_002, SCREEN_WIDTH + 20, 400);
		released_enemies[1] = true;
	}

	if (current_level_time > 10000 && released_enemies[2] == false){
		App->enemies->AddEnemy(BARREL_GUY, SCREEN_WIDTH + 20, 420);
		released_enemies[2] = true;
	}

	if (current_level_time > 15000 && released_enemies[3] == false){
		App->enemies->AddEnemy(INDIAN_003, -20, 222);
		released_enemies[3] = true;
	}
	if (current_level_time > 18000 && released_enemies[4] == false){
		App->enemies->AddEnemy(INDIAN_003, -20, 222);
		released_enemies[4] = true;
	}

	if (current_level_time > 22000){
		loop_enemies();

	}


	// Draw everything --------------------------------------
	App->render->Blit(background, 0, 0, NULL);
	
	return UPDATE_CONTINUE;
}

void ModuleSceneSpace::loop_enemies(){

	uint i;
	for (i = 0; i < WAVE_NUM_OF_ENEMIES; i++){
		released_enemies[i] = false;
	}


	init_level_time = SDL_GetTicks();

}


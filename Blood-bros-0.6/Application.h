#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 21

class ModuleWindow;
class ModuleInput;
class ModuleFonts;
class ModuleUI;
class ModuleDebug;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleSceneSpace;
class ModuleSceneScore;
class ModuleSceneTad;
class ModuleSceneWelcome;
class ModuleSceneStage_Pres;
class ModulePlayer;
class ModuleFadeToBlack;
class ModulePowerUps;
class ModuleAudio;
class ModuleCollision;
class ModuleEnemies;
class ModuleReticle;
class ModuleScenario;
class ModuleTincan;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleDebug* debug;
	ModuleInput* input;
	ModuleUI* UI;
	ModuleTextures* textures;
	ModuleSceneSpace* scene_space;
	ModuleSceneScore* scene_score;
	ModuleSceneTad* scene_tad;
	ModuleSceneWelcome* scene_welcome;
	ModuleSceneStage_Pres* scene_stage_pres;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModulePowerUps* power_ups;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleEnemies* enemies;
	ModuleReticle* reticle;
	ModuleScenario* scenario;
	ModuleTincan* tincan;


public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__
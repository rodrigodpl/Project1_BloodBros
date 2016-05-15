#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18

class ModuleWindow;
class ModuleInput;
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
class ModuleAudio;
class ModuleCollision;
class ModuleEnemies;
class ModuleReticle;
class ModuleScenario;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleDebug* debug;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneSpace* scene_space;
	ModuleSceneScore* scene_score;
	ModuleSceneTad* scene_tad;
	ModuleSceneWelcome* scene_welcome;
	ModuleSceneStage_Pres* scene_stage_pres;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleEnemies* enemies;
	ModuleReticle* reticle;
	ModuleScenario* scenario;


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
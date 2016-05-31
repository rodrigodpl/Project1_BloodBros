#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleReticle.h"
#include "ModuleScenario.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	enemy_shot.anim.PushBack({ 14, 67, 23, 22 });
	enemy_shot.anim.PushBack({ 49, 67, 23, 22 });
	enemy_shot.anim.speed = 0.2f;
	enemy_shot.life = 10000;

	enemy_shot_2.anim.PushBack({ 72, 444,  48, 38 });
	enemy_shot_2.anim.PushBack({ 121, 445, 48,38});
	enemy_shot_2.anim.PushBack({ 164, 444, 48,38});
	enemy_shot_2.anim.PushBack({ 222, 444,48,38 });
	enemy_shot_2.anim.speed = 0.2f;
	enemy_shot_2.life = 10000;

	dynamite.anim.PushBack({ 26, 710, 48, 48 });
	dynamite.anim.PushBack({ 95, 710, 15, 48 });
	dynamite.anim.PushBack({ 131, 719, 45, 15 });
	dynamite.anim.PushBack({ 188, 716, 33, 27 });
	dynamite.anim.PushBack({ 245, 719, 30, 30 });
	dynamite.anim.PushBack({ 299, 719, 12, 33 });
	dynamite.anim.PushBack({ 344, 722, 24, 27 });
	dynamite.anim.PushBack({ 392, 731, 27, 12 });
	dynamite.anim.speed = 0.2f;

	enemy_bomb.anim.PushBack({ 395, 666, 18, 21 });
	enemy_bomb.anim.PushBack({ 349, 666, 15, 24 });
	enemy_bomb.anim.PushBack({ 295, 663, 24, 30 });
	enemy_bomb.anim.PushBack({ 241, 663, 33, 27 });
	enemy_bomb.anim.PushBack({ 190, 663, 33, 27 });
	enemy_bomb.anim.PushBack({ 136, 657, 36, 36 });
	enemy_bomb.anim.PushBack({ 85, 654, 30, 42 });
	enemy_bomb.anim.PushBack({ 34, 651, 36, 48 });
	enemy_bomb.anim.speed = 0.225f;

	explosion.anim.PushBack({ 7, 785, 108, 116 });
	explosion.anim.PushBack({ 146, 804, 154, 154 });
	explosion.anim.PushBack({ 305, 804, 154, 154 });
	explosion.anim.PushBack({ 466, 804, 154, 154 });
	explosion.anim.PushBack({ 637, 804, 154, 154 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.2f;

	enemy_explosion.anim.PushBack({ 576, 441, 83, 168 });
	enemy_explosion.anim.PushBack({ 645, 441, 83, 168 });
	enemy_explosion.anim.PushBack({ 709, 441, 83, 168 });
	enemy_explosion.anim.PushBack({ 801, 441, 83, 168 });
	enemy_explosion.anim.PushBack({ 889, 441, 83, 168 });
	enemy_explosion.anim.PushBack({ 978, 441, 83, 168 });
	enemy_explosion.anim.PushBack({ 1065, 441, 83, 168 });
	enemy_explosion.anim.PushBack({ 1158, 441, 83, 168 });
	enemy_explosion.anim.PushBack({ 1236, 441, 83, 168 });
	enemy_explosion.anim.loop = false;
	enemy_explosion.anim.speed = 0.2f;


	destroying_wall.anim.PushBack({ 429, 33, 252, 101 });
	destroying_wall.anim.PushBack({ 703, 30, 255, 98 });
	destroying_wall.anim.PushBack({ 439, 163, 238, 94 });
	destroying_wall.anim.PushBack({ 708, 166, 240, 91 });
	destroying_wall.anim.speed = 0.2f;
	destroying_wall.life = 2500;

	shot_flare.anim.PushBack({ 408, 1008, 45, 42 });
	shot_flare.anim.PushBack({ 461, 1009, 45, 42 });
	shot_flare.anim.PushBack({ 513, 1008, 45, 42 });
	shot_flare.anim.loop = false;
	shot_flare.anim.speed = 0.2f;

	big_shot_flare.anim.PushBack({ 86, 1017, 96, 48 });
	big_shot_flare.anim.PushBack({ 173, 1006, 96, 48 });
	big_shot_flare.anim.PushBack({ 265, 1012, 96, 48 });
	big_shot_flare.anim.loop = false;
	big_shot_flare.anim.speed = 0.2f;

	fire.anim.PushBack({ 1022, 682, 48, 96 });
	fire.anim.PushBack({ 1083, 682, 48, 96 });
	fire.anim.PushBack({ 959, 682, 48, 96 });
	fire.anim.PushBack({ 1141, 682, 48, 96 });
	fire.anim.PushBack({ 1198, 682, 48, 96 });
	fire.anim.PushBack({ 1265, 682, 48, 96 });
	fire.anim.loop;
	fire.anim.speed = 0.2f;
}


bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("sprites/Particles_SpriteSheet.png");

	//Load fx
	enemy_bomb.fx = App->audio->LoadFx("FX/bomb-trhow.wav");
	explosion.fx = App->audio->LoadFx("FX/explosion.wav");
	destroying_wall.fx = App->audio->LoadFx("FX/building-collapse.wav");
	enemy_explosion.fx = App->audio->LoadFx("FX/explosion.wav");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	// Unload fx
	App->audio->UnLoadFx(enemy_bomb.fx);
	App->audio->UnLoadFx(explosion.fx);
	App->audio->UnLoadFx(enemy_explosion.fx);
	App->audio->UnLoadFx(destroying_wall.fx);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}


update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;

			if(collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);


			if (collider_type == COLLIDER_ENEMY_SHOT)
				p->speed = p->position.GetDirection(App->player->position);
			else if (collider_type == COLLIDER_DYNAMITE)
				p->speed = App->player->position.GetSpeed(App->reticle->position);
			else if (collider_type == COLLIDER_ENEMY_BOMB)
				p->speed = p->position.GetSpeed(App->player->position);
			


			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if(active[i] != nullptr && active[i]->collider == c1)
		{
			if ((c2->type == COLLIDER_PLAYER_SHOT && (App->player->shooting)) || c2->type == COLLIDER_SCENARIO){

				if (c1->type == COLLIDER_ENEMY_BOMB)
					App->particles->AddParticle(App->particles->enemy_explosion, active[i]->position.x - 40, active[i]->position.y - 168);
				
				delete active[i];
				active[i] = nullptr;
				break;
			}
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if(collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{

		if ((((float)SDL_GetTicks()) - born) > life)
			ret = false;
	}
	else
		if (anim.Finished()){
			ret = false;
			if (collider != nullptr && (collider->type == COLLIDER_DYNAMITE || collider->type == COLLIDER_ENEMY_BOMB)){
				if (collider->type == COLLIDER_DYNAMITE){
					App->particles->AddParticle(App->particles->explosion, position.x - 75, position.y - 75);
					App->enemies->check_explosion(position.x - 75, position.y - 75);
					App->scenario->check_explosion(position.x - 75, position.y - 75);
				}
				else if (collider->type == COLLIDER_ENEMY_BOMB){
					App->particles->AddParticle(App->particles->enemy_explosion, position.x - 40, position.y - 168);
					App->player->check_explosion(position.x - 40, position.y - 168);
				}
			}
			
		}

	if (collider != nullptr){

		if (collider->type == COLLIDER_ENEMY_BOMB && slow_down_counter < 1){
			anim.current_frame -= anim.speed;
			slow_down_counter++;
			return ret;
		}
		else{

			if (collider->type == COLLIDER_ENEMY_BOMB)
				slow_down_counter = 0;

			position.x += speed.x;
			position.y += speed.y;

			collider->SetPos(position.x, position.y);

			if (collider->type == COLLIDER_DYNAMITE || collider->type == COLLIDER_ENEMY_BOMB)
				speed.y -= CONST_GRAVITY;
		}
	}

	return ret;
}



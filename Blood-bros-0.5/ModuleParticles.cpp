#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleReticle.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

#define BASE_ENEMY_SHOT_SPEED 2

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;


	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.speed = 0.3f;

	laser.anim.PushBack({36, 94, 31, 30});
	laser.anim.PushBack({85, 103, 31, 30});
	laser.anim.speed = 0.2f;
	laser.speed.x = 5;
	laser.life = 3000;

	enemy_shot.anim.PushBack({ 14, 67, 23, 22 });
	enemy_shot.anim.PushBack({ 49, 67, 23, 22 });
	enemy_shot.anim.speed = 0.2f;
	enemy_shot.life = 10000;

	player_shot.anim.PushBack({ 45, 121, 71, 39 });
	player_shot.anim.PushBack({ 146, 121, 71, 39 });
	player_shot.anim.PushBack({ 252, 121, 71, 39 });
	player_shot.anim.PushBack({ 14, 168, 71, 39 });
	player_shot.anim.PushBack({ 102, 168, 71, 39 });
	player_shot.anim.speed = 0.3f;
	player_shot.anim.loop = false;


	barrel_guy_dying.anim.PushBack({ 232, 103, 16, 12 });
	barrel_guy_dying.anim.PushBack({ 249, 103, 16, 12 });
	barrel_guy_dying.anim.speed = 0.2f;
	barrel_guy_dying.anim.loop = false;

	indian_dying.anim.PushBack({ 232, 103, 16, 12 });
	indian_dying.anim.PushBack({ 249, 103, 16, 12 });
	indian_dying.anim.speed = 0.2f;
	indian_dying.anim.loop = false;

	destroying_wall.anim.PushBack({ 232, 103, 16, 12 });
	destroying_wall.anim.PushBack({ 232, 103, 16, 12 });
	destroying_wall.anim.speed = 0.2f;
	destroying_wall.anim.loop = false;

	
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Particles_SpriteSheet.png");

	// Load particles fx particle
	explosion.fx = App->audio->LoadFx("rtype/explosion.wav");
	laser.fx = App->audio->LoadFx("rtype/laser.wav");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	// Unload fx

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

// Update: draw background
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
			if (collider_type == COLLIDER_ENEMY_SHOT){
				p->speed = p->position.GetDirection(BASE_ENEMY_SHOT_SPEED, App->player->position);
			}
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
			if (c2->type == COLLIDER_PLAYER_SHOT && !(App->reticle->shooting)){
				break;
			}
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
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
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}


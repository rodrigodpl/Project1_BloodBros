#include "Application.h"
#include "ModuleInput.h"
#include "ModuleDebug.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_WALL][COLLIDER_SCENARIO] = false;
	matrix[COLLIDER_WALL][COLLIDER_DYNAMITE] = false;
	matrix[COLLIDER_WALL][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_WALL][COLLIDER_TINCAN] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_BOMB] = false;

	matrix[COLLIDER_SCENARIO][COLLIDER_WALL] = false;
	matrix[COLLIDER_SCENARIO][COLLIDER_SCENARIO] = false;
	matrix[COLLIDER_SCENARIO][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_SCENARIO][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_SCENARIO][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_SCENARIO][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_SCENARIO][COLLIDER_DYNAMITE] = false;
	matrix[COLLIDER_SCENARIO][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_SCENARIO][COLLIDER_TINCAN] = false;
	matrix[COLLIDER_SCENARIO][COLLIDER_ENEMY_BOMB] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_SCENARIO] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_DYNAMITE] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_TINCAN] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_BOMB] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_SCENARIO] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_DYNAMITE] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_TINCAN] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_BOMB] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_SCENARIO] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_DYNAMITE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_TINCAN] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_BOMB] = true;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_SCENARIO] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_DYNAMITE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_TINCAN] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_BOMB] = false;

	matrix[COLLIDER_DYNAMITE][COLLIDER_WALL] = false;
	matrix[COLLIDER_DYNAMITE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_DYNAMITE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_DYNAMITE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_DYNAMITE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_DYNAMITE][COLLIDER_SCENARIO] = false;
	matrix[COLLIDER_DYNAMITE][COLLIDER_DYNAMITE] = false;
	matrix[COLLIDER_DYNAMITE][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_DYNAMITE][COLLIDER_TINCAN] = false;
	matrix[COLLIDER_DYNAMITE][COLLIDER_ENEMY_BOMB] = false;

	matrix[COLLIDER_POWER_UP][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_SCENARIO] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_DYNAMITE] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_TINCAN] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_BOMB] = false;

	matrix[COLLIDER_TINCAN][COLLIDER_WALL] = false;
	matrix[COLLIDER_TINCAN][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_TINCAN][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_TINCAN][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_TINCAN][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_TINCAN][COLLIDER_SCENARIO] = false;
	matrix[COLLIDER_TINCAN][COLLIDER_DYNAMITE] = false;
	matrix[COLLIDER_TINCAN][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_TINCAN][COLLIDER_TINCAN] = false;
	matrix[COLLIDER_TINCAN][COLLIDER_ENEMY_BOMB] = false;

	matrix[COLLIDER_ENEMY_BOMB][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_BOMB][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_BOMB][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_BOMB][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY_BOMB][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_BOMB][COLLIDER_SCENARIO] = true;
	matrix[COLLIDER_ENEMY_BOMB][COLLIDER_DYNAMITE] = false;
	matrix[COLLIDER_ENEMY_BOMB][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_BOMB][COLLIDER_TINCAN] = false;
	matrix[COLLIDER_ENEMY_BOMB][COLLIDER_ENEMY_BOMB] = false;
}


update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->CheckCollision(c2->rect) == true)
			{
				if(matrix[c1->type][c2->type] && c1->callback) 
					c1->callback->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->callback) 
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	if (App->debug->activated_functions[DRAW_COLLIDERS_F1])
			DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{

	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case COLLIDER_SCENARIO: // cyan
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
			case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case COLLIDER_DYNAMITE: // gray
			App->render->DrawQuad(colliders[i]->rect, 125, 125, 125, alpha);
			break;
			case COLLIDER_POWER_UP: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
			case COLLIDER_TINCAN: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case COLLIDER_ENEMY_BOMB: // orange
			App->render->DrawQuad(colliders[i]->rect, 255, 125, 0, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool ModuleCollision::EraseCollider(Collider* collider)
{
	if(collider != nullptr)
	{
		// we still search for it in case we received a dangling pointer
		for(uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if(colliders[i] == collider)
			{
				collider->to_delete = true;
				break;
			}
		}
	}
		

	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}
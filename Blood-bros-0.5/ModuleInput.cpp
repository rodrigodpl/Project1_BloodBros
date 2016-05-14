#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for(uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if(keyboard[SDL_SCANCODE_ESCAPE] && App->fade->IsFading() == false)
		return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}


uint ModuleInput::player_input(){

	switch (App->player->state){

	case ST_IDLE:

		if (keyboard[SDL_SCANCODE_J] == KEY_REPEAT)
			return(IN_SHOT);
		if (keyboard[SDL_SCANCODE_A] == KEY_REPEAT && keyboard[SDL_SCANCODE_D] == KEY_IDLE)
			return(IN_LEFT_DOWN);
		if (keyboard[SDL_SCANCODE_D] == KEY_REPEAT && keyboard[SDL_SCANCODE_A] == KEY_IDLE)
			return(IN_RIGHT_DOWN);
		if (keyboard[SDL_SCANCODE_S] == KEY_REPEAT)
			return(IN_CROUCH_DOWN);

		break;

	case ST_IDLE_SHOOTING:

		if (keyboard[SDL_SCANCODE_J] == KEY_IDLE && App->player->current_animation->Finished())
			return(IN_SHOT_FINISH);
		if (keyboard[SDL_SCANCODE_J] == KEY_REPEAT && App->player->current_animation->Finished())
			return(IN_SHOT);
		if (keyboard[SDL_SCANCODE_S] == KEY_REPEAT)
			return(IN_CROUCH_DOWN);

		break;

	case ST_CROUCHED_IDLE:

		if (keyboard[SDL_SCANCODE_S] == KEY_IDLE)
			return(IN_CROUCH_UP);
		if (keyboard[SDL_SCANCODE_J] == KEY_REPEAT)
			return(IN_SHOT);
		if (keyboard[SDL_SCANCODE_K] == KEY_DOWN && keyboard[SDL_SCANCODE_A] == KEY_REPEAT &&
			keyboard[SDL_SCANCODE_D] == KEY_IDLE)
			return(IN_JUMP_LEFT);
		if (keyboard[SDL_SCANCODE_K] == KEY_DOWN && keyboard[SDL_SCANCODE_D] == KEY_REPEAT &&
			keyboard[SDL_SCANCODE_A] == KEY_IDLE)
			return(IN_JUMP_RIGHT);

		break;

	case ST_CROUCHED_SHOOTING:

		if (keyboard[SDL_SCANCODE_J] == KEY_IDLE && App->player->current_animation->Finished())
			return(IN_SHOT_FINISH);
		if (keyboard[SDL_SCANCODE_J] == KEY_REPEAT && App->player->current_animation->Finished())
			return(IN_SHOT);
		if (keyboard[SDL_SCANCODE_S] == KEY_IDLE)
			return(IN_CROUCH_UP);

		break;

	case ST_WALK_LEFT:

		if (keyboard[SDL_SCANCODE_J] == KEY_REPEAT)
			return(IN_SHOT);
		if (keyboard[SDL_SCANCODE_K] == KEY_DOWN)
			return(IN_JUMP_LEFT);
		if (keyboard[SDL_SCANCODE_A] == KEY_IDLE)
			return(IN_IDLE);
		if (App->player->current_animation->Finished()){
			App->player->current_animation->Reset();
			App->player->current_animation->current_frame = 4.0f; break;
		}

		break;

	case ST_WALK_RIGHT:

		if (keyboard[SDL_SCANCODE_J] == KEY_REPEAT)
			return(IN_SHOT);
		if (keyboard[SDL_SCANCODE_K] == KEY_DOWN)
			return(IN_JUMP_RIGHT);
		if (keyboard[SDL_SCANCODE_D] == KEY_IDLE)
			return(IN_IDLE);
		if (App->player->current_animation->Finished()){
			App->player->current_animation->Reset();
			App->player->current_animation->current_frame = 4.0f; break;
		}

		break;

	case ST_JUMP_LEFT:

		if (App->player->current_animation->Finished())
			return(IN_IDLE);

		break;

	case ST_JUMP_RIGHT:

		if (App->player->current_animation->Finished())
			return(IN_IDLE);

		break;

	case ST_ROLL_LEFT:

		if (App->player->current_animation->Finished() && keyboard[SDL_SCANCODE_S] == KEY_REPEAT)
			return(IN_CROUCH_DOWN);
		if (App->player->current_animation->Finished())
			return(IN_IDLE);

		break;

	case ST_ROLL_RIGHT:

		if (App->player->current_animation->Finished())
			return(IN_IDLE);

		break;

	}

	return(IN_NULL);

}

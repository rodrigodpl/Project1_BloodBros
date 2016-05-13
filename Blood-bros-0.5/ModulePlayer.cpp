#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	idle.PushBack({ 359, 20, 70, 184 });

	// Move left
	left.PushBack({ 248, 20, 88, 181 });
	left.PushBack({ 146, 20, 88, 181 });
	left.PushBack({ 612, 602, 103, 181 });
	left.PushBack({ 612, 602, 103, 181 });
	left.PushBack({ 514, 602, 97, 179 });
	left.PushBack({ 514, 602, 97, 179 });
	left.PushBack({ 385, 600, 121, 181 });
	left.PushBack({ 385, 600, 121, 181 });
	left.PushBack({ 612, 602, 103, 181 });
	left.PushBack({ 612, 602, 103, 181 });
	left.PushBack({ 514, 602, 97, 179 });
	left.PushBack({ 514, 602, 97, 179 });
	left.PushBack({ 385, 600, 121, 181 });
	left.PushBack({ 385, 600, 121, 181 });
	left.PushBack({ 50, 20, 89, 182 });
	left.loop = false;
	left.speed = 0.3f;

	// Move right
	right.PushBack({ 455, 20, 67, 184 });
	right.PushBack({ 542, 20, 85, 184 });
	right.PushBack({ 24, 602, 103, 181 });
	right.PushBack({ 128, 603, 97, 178 });
	right.PushBack({ 232, 600, 122, 181 });
	right.PushBack({ 24, 602, 103, 181 });
	right.PushBack({ 128, 603, 97, 178 });
	right.PushBack({ 232, 600, 122, 181 });
	right.PushBack({ 629, 20, 94, 184 });
	right.loop = false;
	right.speed = 0.3f;

	crouched_idle.PushBack({ 1228, 20, 83, 136 });
	crouched_idle.loop = false;
	crouched_idle.speed = 0.3f;

	crouched_left.PushBack({ 1136, 20, 85, 136 });
	crouched_left.PushBack({ 1033, 20, 92, 136 });
	crouched_left.PushBack({ 934, 20, 98, 136 });
	crouched_left.loop = false;
	crouched_left.speed = 0.3f;

	crouched_right.PushBack({ 1331, 19, 82, 137 });
	crouched_right.PushBack({ 1421, 19, 90, 136 });
	crouched_right.PushBack({ 1511, 20, 97, 136 });
	crouched_right.loop = false;
	crouched_right.speed = 0.3f;

	crouched_roll_left.PushBack({ 1328, 1126, 130, 82 });
	crouched_roll_left.PushBack({ 1180, 1111, 145, 96 });
	crouched_roll_left.PushBack({ 1040, 1114, 138, 94 });
	crouched_roll_left.loop = false;
	crouched_roll_left.speed = 0.3f;

	crouched_roll_right.PushBack({ 940, 741, 130, 82 });
	crouched_roll_right.PushBack({ 1073, 726, 145, 96 });
	crouched_roll_right.PushBack({ 1219, 729, 138, 94 });
	crouched_roll_right.loop = false;
	crouched_roll_right.speed = 0.3f;

	jump_roll_left.PushBack({ 1034, 958, 192, 97 });
	jump_roll_left.PushBack({ 1247, 867, 115, 189 });
	jump_roll_left.PushBack({ 938, 898, 96, 157 });
	jump_roll_left.PushBack({ 1040, 1114, 139, 94 });
	jump_roll_left.PushBack({ 938, 1063, 97, 145 });
	jump_roll_left.loop = false;
	jump_roll_left.speed = 0.1f;

	jump_roll_right.PushBack({ 938, 510, 97, 160 });
	jump_roll_right.PushBack({ 1171, 570, 193, 99 });
	jump_roll_right.PushBack({ 1363, 513, 97, 156 });
	jump_roll_right.PushBack({ 1218, 729, 140, 94 });
	jump_roll_right.PushBack({ 1362, 678, 98, 145 });
	jump_roll_right.loop = false;
	jump_roll_right.speed = 0.1f;

	killed.PushBack({ 32, 884, 83, 157 });
	killed.PushBack({ 0, 0, 0, 0 });
	killed.PushBack({ 32, 884, 83, 157 });
	killed.PushBack({ 0, 0, 0, 0 });
	killed.PushBack({ 162, 834, 101, 144 });
	killed.PushBack({ 0, 0, 0, 0 });
	killed.PushBack({ 162, 834, 101, 144 });
	killed.PushBack({ 0, 0, 0, 0 });
	killed.PushBack({ 282, 881, 123, 96 });
	killed.PushBack({ 0, 0, 0, 0 });
	killed.PushBack({ 282, 881, 123, 96 });
	killed.PushBack({ 0, 0, 0, 0 });
	killed.PushBack({ 417, 885, 153, 92 });
	killed.PushBack({ 0, 0, 0, 0 });
	killed.PushBack({ 417, 885, 153, 92 });
	killed.PushBack({ 0, 0, 0, 0 });
	killed.speed = 0.2f;


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("cowboy.png");
	current_animation = &idle;

	destroyed = false;
	position.x = 350;
	position.y = 610;

	col = App->collision->AddCollider({ position.x, position.y, 70, 184 }, COLLIDER_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->collision->EraseCollider(col);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 0;

	if (destroyed == false){
		if (state == NOT_JUMPING) {

			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
			{
				speed = 3;

				if (current_animation != &right)
				{
					right.Reset();
					current_animation = &right;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
			{
				speed = -3;
				if (current_animation != &left)
				{
					left.Reset();
					current_animation = &left;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
			{
				speed = 0;
				crouched = true;
				if (current_animation != &crouched_left)
				{
					crouched_left.Reset();
					current_animation = &crouched_left;
				}
			}

			if ((App->input->keyboard[SDL_SCANCODE_D]) == KEY_STATE::KEY_REPEAT && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT))
			{
				speed = 0;
				crouched = true;
				if (current_animation != &crouched_right)
				{
					crouched_right.Reset();
					current_animation = &crouched_right;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
				App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
			{
				speed = 0;
				crouched = true;
				if (current_animation != &crouched_idle)
				{
					crouched_idle.Reset();
					current_animation = &crouched_idle;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE){
				current_animation = &idle;
			}

			if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN){

				if (speed == -3){
					state = JUMP_LEFT;
					if (crouched){
						current_animation = &crouched_roll_left;
					}
					else{
						current_animation = &jump_roll_left;
					}
				}

				else if (speed == 3){
					state = JUMP_RIGHT;
					if (crouched){
						current_animation = &crouched_roll_right;
					}
					else{
						current_animation = &jump_roll_right;
					}
				}
			}
		}

		if (state == JUMP_LEFT){
			speed = -5;
		}
		else if (state == JUMP_RIGHT){
			speed = 5;
		}

		if ((position.x + speed) < (SCREEN_WIDTH - 30) && (position.x + speed) > 0){
			position.x += speed;
		}

		if (current_animation->Finished() && state != NOT_JUMPING){
			state = NOT_JUMPING;
			jump_roll_left.Reset();
			jump_roll_left.loops = 0;
			jump_roll_right.Reset();
			jump_roll_right.loops = 0;
			crouched_roll_left.Reset();
			crouched_roll_left.loops = 0;
			crouched_roll_right.Reset();
			crouched_roll_right.loops = 0;
		}

		col->SetPos(position.x, position.y - 184);

		crouched = false;
	}

	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);



	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if(c1 == col && destroyed == false && App->fade->IsFading() == false && state == NOT_JUMPING)
	{
		Mix_FadeOutMusic(1000);


		current_animation = &killed;

		App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_score, 3);

		destroyed = true;
	}
}
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleDebug.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleReticle.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer()
{
	idle.PushBack({ 359, 20, 70, 184 });


	idle_shooting_0.PushBack({ 24, 221, 111, 180 });
	idle_shooting_0.PushBack({ 12, 419, 123, 177 });
	idle_shooting_0.speed = 0.15f;
	idle_shooting_30.PushBack({ 159, 220, 93, 180 });
	idle_shooting_30.PushBack({ 141, 418, 111, 177 });
	idle_shooting_30.speed = 0.15f;
	idle_shooting_60.PushBack({ 279, 208, 87, 192 });
	idle_shooting_60.PushBack({ 258, 409, 108, 186 });
	idle_shooting_60.speed = 0.15f;
	idle_shooting_90.PushBack({ 390, 208, 69, 195 });
	idle_shooting_90.PushBack({ 376, 406, 83, 192 });
	idle_shooting_90.speed = 0.15f;
	idle_shooting_120.PushBack({ 486, 208, 84, 195 });
	idle_shooting_120.PushBack({ 486, 406, 66, 192 });
	idle_shooting_120.speed = 0.15f;
	idle_shooting_150.PushBack({ 573, 220, 102, 183 });
	idle_shooting_150.PushBack({ 573, 418, 90, 180 });
	idle_shooting_150.speed = 0.15f;
	idle_shooting_180.PushBack({ 684, 220, 135, 183 });
	idle_shooting_180.PushBack({ 684, 418, 123, 180 });
	idle_shooting_180.speed = 0.15f;



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

	crouched_shooting_0.PushBack({ 884, 168, 120, 135 });
	crouched_shooting_0.PushBack({ 891, 316, 114, 135 });
	crouched_shooting_0.speed = 0.15f;
	crouched_shooting_30.PushBack({ 1025, 168, 99, 135 });
	crouched_shooting_30.PushBack({ 1031, 316, 93, 135 });
	crouched_shooting_30.speed = 0.15f;
	crouched_shooting_60.PushBack({ 1136, 156, 84, 147 });
	crouched_shooting_60.PushBack({ 1136, 304, 84, 147 });
	crouched_shooting_60.speed = 0.15f;
	crouched_shooting_90.PushBack({ 1229, 156, 81, 147 });
	crouched_shooting_90.PushBack({ 1229, 304, 81, 147 });
	crouched_shooting_90.speed = 0.15f;
	crouched_shooting_120.PushBack({ 1331, 157, 87, 146 });
	crouched_shooting_120.PushBack({ 1331, 304, 84, 147 });
	crouched_shooting_120.speed = 0.15f;
	crouched_shooting_150.PushBack({ 1421, 168, 108, 135 });
	crouched_shooting_150.PushBack({ 1421, 316, 108, 135 });
	crouched_shooting_150.speed = 0.15f;
	crouched_shooting_180.PushBack({ 1538, 168, 141, 135 });
	crouched_shooting_180.PushBack({ 1547, 316, 129, 135 });
	crouched_shooting_180.speed = 0.15f;


	crouched_roll_left.PushBack({ 1328, 1126, 130, 82 });
	crouched_roll_left.PushBack({ 1180, 1111, 145, 96 });
	crouched_roll_left.PushBack({ 1040, 1114, 138, 94 });
	crouched_roll_left.loop = false;
	crouched_roll_left.speed = 0.1f;

	crouched_roll_right.PushBack({ 940, 741, 130, 82 });
	crouched_roll_right.PushBack({ 1073, 726, 145, 96 });
	crouched_roll_right.PushBack({ 1219, 729, 138, 94 });
	crouched_roll_right.loop = false;
	crouched_roll_right.speed = 0.1f;

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
	killed.loop = false;
	killed.speed = 0.2f;


}


bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("cowboy.png");
	current_animation = &idle;

	shooting = false;
	alive = true;
	immune = false;

	position.x = 350;
	position.y = 610;

	col = App->collision->AddCollider({ position.x, position.y, 70, 90 }, COLLIDER_PLAYER, this);

	return true;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->collision->EraseCollider(col);

	return true;
}

update_status ModulePlayer::Update()
{

	if (alive){

		uint input = App->input->player_input();

		if (input != IN_NULL){
			switch (state){

			case ST_IDLE:

				switch (input){

				case IN_CROUCH_DOWN:
					state = ST_CROUCHED_IDLE;
					current_animation = &crouched_idle; break;
				case IN_LEFT_DOWN:
					state = ST_WALK_LEFT;
					speed = -3;
					current_animation = &left; break;
				case IN_RIGHT_DOWN:
					state = ST_WALK_RIGHT;
					speed = 3;
					current_animation = &right; break;
				case IN_SHOT:
					state = ST_IDLE_SHOOTING;
					shooting = true;
					GetShootingAngle(state); break;

				}

				break;

			case ST_IDLE_SHOOTING:

				shooting = false;

				switch (input){

				case IN_SHOT_FINISH:
					state = ST_IDLE;
					current_animation->Reset();
					current_animation = &idle; break;
				case IN_SHOT:
					GetShootingAngle(state);
					shooting = true; break;
				case IN_CROUCH_DOWN:
					state = ST_CROUCHED_SHOOTING;
					uint curr_frame = current_animation->current_frame;
					current_animation->Reset();
					current_animation = &crouched_shooting;
					current_animation->current_frame = curr_frame; break;

				}

				break;


			case ST_CROUCHED_IDLE:

				switch (input){

				case IN_SHOT:
					state = ST_CROUCHED_SHOOTING;
					shooting = true;
					GetShootingAngle(state); break;
				case IN_CROUCH_UP:
					state = ST_IDLE;
					current_animation = &idle; break;
				case IN_JUMP_LEFT:
					state = ST_ROLL_LEFT;
					immune = true;
					current_animation = &crouched_roll_left;
					speed = -5; break;
				case IN_JUMP_RIGHT:
					state = ST_ROLL_RIGHT;
					immune = true;
					current_animation = &crouched_roll_right;
					speed = 5; break;

				}

				break;

			case ST_CROUCHED_SHOOTING:

				shooting = false;

				switch (input){

				case IN_SHOT_FINISH:
					state = ST_CROUCHED_IDLE;
					current_animation->Reset();
					current_animation = &crouched_idle; break;
				case IN_SHOT:
					GetShootingAngle(state);
					shooting = true; break;
				case IN_CROUCH_UP:
					state = ST_IDLE;
					uint curr_frame = current_animation->current_frame;
					current_animation->Reset();
					current_animation = &idle_shooting;
					current_animation->current_frame = curr_frame; break;

				}

				break;

			case ST_WALK_LEFT:

				switch (input){

				case IN_SHOT:
					state = ST_IDLE_SHOOTING;
					current_animation->Reset();
					current_animation = &idle_shooting;
					speed = 0;
					shooting = true; break;
				case IN_JUMP_LEFT:
					state = ST_JUMP_LEFT;
					current_animation->Reset();
					immune = true;
					current_animation = &jump_roll_left;
					speed = -5; break;
				case IN_IDLE:
					state = ST_IDLE;
					current_animation->Reset();
					speed = 0;
					current_animation = &idle; break;

				}

				break;

			case ST_WALK_RIGHT:

				switch (input){

				case IN_SHOT:
					state = ST_IDLE_SHOOTING;
					current_animation->Reset();
					current_animation = &idle_shooting;
					speed = 0;
					shooting = true; break;
				case IN_JUMP_RIGHT:
					state = ST_JUMP_RIGHT;
					current_animation->Reset();
					immune = true;
					current_animation = &jump_roll_right;
					speed = 5; break;
				case IN_IDLE:
					state = ST_IDLE;
					current_animation->Reset();
					speed = 0;
					current_animation = &idle; break;

				}

				break;

			case ST_JUMP_LEFT:

				state = ST_IDLE;
				current_animation->Reset();
				immune = false;
				speed = 0;
				current_animation = &idle;

				break;

			case ST_JUMP_RIGHT:

				state = ST_IDLE;
				current_animation->Reset();
				immune = false;
				speed = 0;
				current_animation = &idle;

				break;

			case ST_ROLL_LEFT:

				switch (input){

				case IN_CROUCH_DOWN:
					state = ST_CROUCHED_IDLE;
					current_animation->Reset();
					immune = false;
					speed = 0;
					current_animation = &crouched_idle; break;
				case IN_IDLE:
					state = ST_IDLE;
					current_animation->Reset();
					immune = false;
					speed = 0;
					current_animation = &idle; break;

				}

				break;

			case ST_ROLL_RIGHT:

				switch (input){

				case IN_CROUCH_DOWN:
					state = ST_CROUCHED_IDLE;
					current_animation->Reset();
					immune = false;
					speed = 0;
					current_animation = &crouched_idle; break;
				case IN_IDLE:
					state = ST_IDLE;
					current_animation->Reset();
					immune = false;
					speed = 0;
					current_animation = &idle; break;

				}

				break;


			}
		}
	}

	if (position.x + speed < SCREEN_WIDTH - 150 && position.x + speed > 20)
		position.x += speed;

	col->SetPos(position.x, position.y - 100);

	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;

}



void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if(c1 == col && alive && App->fade->IsFading() == false && immune == false && App->debug->activated_functions[GOD_MODE_F2] == false)
	{
		Mix_FadeOutMusic(1000);

		speed = 0;
		current_animation = &killed;

		App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_score, 3);

		alive = false;
	}
}


void ModulePlayer::GetShootingAngle(uint state){


	current_animation->Reset();

	int distance_to_reticle = App->reticle->position.x - position.x;
	uint result = A_0;

	if (distance_to_reticle > -((SCREEN_WIDTH / 6) * 3))
		result = A_30;
	if (distance_to_reticle > -((SCREEN_WIDTH / 6) * 2))
		result = A_60;
	if (distance_to_reticle > -((SCREEN_WIDTH / 6) * 1))
		result = A_90;
	if (distance_to_reticle > (SCREEN_WIDTH / 6) * 1)
		result = A_120;
	if (distance_to_reticle > (SCREEN_WIDTH / 6) * 2)
		result = A_150;
	if (distance_to_reticle > (SCREEN_WIDTH / 6) * 3)
		result = A_180;

	switch (result){

		case A_0: idle_shooting = idle_shooting_0; crouched_shooting = crouched_shooting_0; break;
		case A_30: idle_shooting = idle_shooting_30; crouched_shooting = crouched_shooting_30; break;
		case A_60: idle_shooting = idle_shooting_60; crouched_shooting = crouched_shooting_60; break;
		case A_90: idle_shooting = idle_shooting_90; crouched_shooting = crouched_shooting_90; break;
		case A_120: idle_shooting = idle_shooting_120; crouched_shooting = crouched_shooting_120; break;
		case A_150: idle_shooting = idle_shooting_150; crouched_shooting = crouched_shooting_150; break;
		case A_180: idle_shooting = idle_shooting_180; crouched_shooting = crouched_shooting_180; break;
	}

	if (state == ST_CROUCHED_SHOOTING)
		current_animation = &crouched_shooting;
	else if (state == ST_IDLE_SHOOTING)
		current_animation = &idle_shooting;

}
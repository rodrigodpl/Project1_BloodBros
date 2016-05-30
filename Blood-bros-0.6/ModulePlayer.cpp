#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleDebug.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleReticle.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModulePlayer.h"
#include "SDL\include\SDL.h"


ModulePlayer::ModulePlayer()
{
	idle.PushBack({ 359, 20, 70, 184 });


	idle_shooting_0.PushBack({ 24, 1300, 111, 180 });
	idle_shooting_0.PushBack({ 21, 1514, 114, 176 });
	idle_shooting_0.speed = 0.15f;
	idle_shooting_30.PushBack({ 186, 1300, 93, 180 });
	idle_shooting_30.PushBack({ 168, 1514, 111, 177 });
	idle_shooting_30.speed = 0.15f;
	idle_shooting_60.PushBack({ 322, 1289, 87, 191 });
	idle_shooting_60.PushBack({ 301, 1505, 108, 186 });
	idle_shooting_60.speed = 0.15f;
	idle_shooting_90.PushBack({ 449, 1287, 69, 193 });
	idle_shooting_90.PushBack({ 435, 1499, 83, 192 });
	idle_shooting_90.speed = 0.15f;
	idle_shooting_120.PushBack({ 581, 1288, 84, 192 });
	idle_shooting_120.PushBack({ 581, 1499, 66, 192 });
	idle_shooting_120.speed = 0.15f;
	idle_shooting_150.PushBack({ 696, 1297, 102, 183 });
	idle_shooting_150.PushBack({ 696, 1511, 90, 180 });
	idle_shooting_150.speed = 0.15f;
	idle_shooting_180.PushBack({ 807, 1297, 129, 183 });
	idle_shooting_180.PushBack({ 807, 1511, 120, 180 });
	idle_shooting_180.speed = 0.15f;
	

	left.PushBack({ 248, 20, 88, 181 });
	left.PushBack({ 612, 602, 103, 181 });
	left.PushBack({ 514, 602, 97, 179 });
	left.PushBack({ 385, 600, 121, 181 });
	left.PushBack({ 612, 602, 103, 181 });
	left.PushBack({ 50, 20, 89, 182 });
	left.loop = false;
	left.speed = 0.15f;


	right.PushBack({ 455, 20, 67, 184 });
	right.PushBack({ 542, 20, 85, 184 });
	right.PushBack({ 24, 602, 103, 181 });
	right.PushBack({ 128, 603, 97, 178 });
	right.PushBack({ 232, 600, 122, 181 });
	right.PushBack({ 629, 20, 94, 184 });
	right.loop = false;
	right.speed = 0.15f;

	crouched_idle.PushBack({ 1228, 20, 83, 136 });

	crouched_shooting_0.PushBack({ 43, 1726, 120, 135 });
	crouched_shooting_0.PushBack({ 31, 1957, 132, 132 });
	crouched_shooting_0.speed = 0.15f;
	crouched_shooting_30.PushBack({ 206, 1762, 99, 135 });
	crouched_shooting_30.PushBack({ 188, 1957, 117, 132 });
	crouched_shooting_30.speed = 0.15f;
	crouched_shooting_60.PushBack({ 350, 1750, 84, 147 });
	crouched_shooting_60.PushBack({ 332, 1933, 102, 156 });
	crouched_shooting_60.speed = 0.15f;
	crouched_shooting_90.PushBack({ 502, 1750, 81, 147 });
	crouched_shooting_90.PushBack({ 493, 1933, 90, 156 });
	crouched_shooting_90.speed = 0.15f;
	crouched_shooting_120.PushBack({ 637, 1751, 87, 146 });
	crouched_shooting_120.PushBack({ 637, 1945, 81, 144 });
	crouched_shooting_120.speed = 0.15f;
	crouched_shooting_150.PushBack({ 772, 1762, 108, 135 });
	crouched_shooting_150.PushBack({ 772, 1951, 90, 138 });
	crouched_shooting_150.speed = 0.15f;
	crouched_shooting_180.PushBack({ 893, 1762, 139, 35 });
	crouched_shooting_180.PushBack({ 893, 1957, 123, 132 });
	crouched_shooting_180.speed = 0.15f;

	victory_dance.PushBack({ 1025, 1315, 90, 180 });
	victory_dance.PushBack({ 1125, 1321, 84, 174 });
	victory_dance.PushBack({ 1221, 1384, 48, 111 });
	victory_dance.PushBack({ 1283, 1378, 48, 117 });
	victory_dance.PushBack({ 1338, 1420, 33, 75 });
	victory_dance.PushBack({ 1385, 1420, 36, 75 });
	victory_dance.PushBack({ 1444, 1457, 15, 30 });
	victory_dance.speed = 0.10f;
	victory_dance.loop = false;


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

	respawning.PushBack({ 417, 885, 153, 92 });
	respawning.PushBack({ 0, 0, 0, 0 });
	respawning.PushBack({ 417, 885, 153, 92 });
	respawning.PushBack({ 0, 0, 0, 0 });
	respawning.PushBack({ 282, 881, 123, 96 });
	respawning.PushBack({ 0, 0, 0, 0 });
	respawning.PushBack({ 282, 881, 123, 96 });
	respawning.PushBack({ 0, 0, 0, 0 });
	respawning.PushBack({ 162, 834, 101, 144 });
	respawning.PushBack({ 0, 0, 0, 0 });
	respawning.PushBack({ 162, 834, 101, 144 });
	respawning.PushBack({ 0, 0, 0, 0 });
	respawning.PushBack({ 32, 884, 83, 157 });
	respawning.PushBack({ 0, 0, 0, 0 });
	respawning.PushBack({ 32, 884, 83, 157 });
	respawning.loop = false;
	respawning.speed = 0.15f;


}


bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("sprites/player_spritesheet.png");
	current_animation = &idle;

	player_dying_fx = App->audio->LoadFx("FX/mainchar_hit.wav");


	shooting = false;
	alive = true;
	immune = false;

	invincibility_timer = 0;

	position.x = 350;
	position.y = 610;

	col = App->collision->AddCollider({ position.x, position.y, 70, 90 }, COLLIDER_PLAYER, this);


	left.Reset();
	right.Reset();
	jump_roll_left.Reset();
	jump_roll_right.Reset();
	crouched_roll_left.Reset();
	crouched_roll_right.Reset();
	killed.Reset();
	respawning.Reset();
	victory_dance.Reset();

	return true;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->audio->UnLoadFx(player_dying_fx);
	App->collision->EraseCollider(col);

	return true;
}

update_status ModulePlayer::Update()
{

	if (alive){

		if (current_animation == &victory_dance){
			if (App->player->current_animation->current_frame > 2)
				App->player->position = { 150, SCREEN_HEIGHT - 220 };

			if (App->player->current_animation->current_frame > 4)
				App->player->position = { 150, SCREEN_HEIGHT - 320 };

			if (App->player->current_animation->current_frame > 6)
				App->player->position = { 150, SCREEN_HEIGHT - 380 };
		}
		else{

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
						float curr_frame = current_animation->current_frame;
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
						float curr_frame = current_animation->current_frame;
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
					case IN_CROUCH_DOWN:
						state = ST_CROUCHED_IDLE;
						current_animation->Reset();
						speed = 0;
						current_animation = &crouched_idle; break;

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
					case IN_CROUCH_DOWN:
						state = ST_CROUCHED_IDLE;
						current_animation->Reset();
						speed = 0;
						current_animation = &crouched_idle; break;

					}

					break;

				case ST_JUMP_LEFT:

					state = ST_IDLE;
					current_animation->Reset();
					immune = false;
					speed = 0;
					current_animation = &idle; break;

				case ST_JUMP_RIGHT:

					state = ST_IDLE;
					current_animation->Reset();
					immune = false;
					speed = 0;
					current_animation = &idle; break;

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

	}
	else{

		if (current_animation == &killed){
			if (current_animation->Finished() && App->UI->p1_lifes == 0){
				Mix_FadeOutMusic(1000);
				App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_score, 1);
			}
			else if (current_animation->Finished() && App->UI->p1_lifes > 0){
				App->UI->p1_lifes--;
				current_animation->Reset();
				current_animation = &respawning;
			}
		}
		else{
			if (current_animation->Finished()){
				alive = true;
				invincibility_timer = SDL_GetTicks();
				current_animation->Reset();
				current_animation = &idle;
				state = ST_IDLE;
			}
		}

	}

	
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;

}



void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if(c1 == col && alive && App->fade->IsFading() == false && immune == false && App->debug->activated_functions[GOD_MODE_F2] == false
		 && (SDL_GetTicks() - 1000) > invincibility_timer)
	{
		App->audio->PlayFx(player_dying_fx);

		speed = 0;
		current_animation = &killed;

		alive = false;
		shooting = false;
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
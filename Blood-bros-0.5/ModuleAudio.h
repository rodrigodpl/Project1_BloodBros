#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 200

class ModuleAudio : public Module
{
	friend class ModuleSceneSpace;
	friend class ModulePlayer;
public:

	ModuleAudio();

	bool Init();
	bool CleanUp();

	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	uint LoadFx(const char* path);
	bool UnLoadFx(uint id);

	bool PlayFx(unsigned int fx, int repeat = 0);

private:

	Mix_Music*	music = nullptr;
	Mix_Chunk*	fx[MAX_FX];
	uint			last_fx = 1;
};

#endif // __ModuleAudio_H__
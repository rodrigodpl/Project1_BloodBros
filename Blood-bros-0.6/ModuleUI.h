#include "Module.h"
#include "Animation.h"

enum fonts{

	WHITE_FONT


};

class ModuleUI : public Module{

public:
	bool Start();
	update_status Update();
	bool CleanUp();
	void update_FOE();

public:

	ModuleFonts* text_manager;
	uint player_score;
	char score_text[10];
	uint dynamite_num;
	char dynamite_text[5];
	uint p1_lifes;

	Animation FOE_letters;
	Animation FOE_bar;

	Animation FOE_bar_00;
	Animation FOE_bar_10;
	Animation FOE_bar_30;
	Animation FOE_bar_50;
	Animation FOE_bar_70;
	Animation FOE_bar_90;
	Animation FOE_bar_100;

	Animation player_life;
	Animation dynamite_logo;
	Animation p1_score_logo;
	Animation top_score_logo;

	SDL_Texture* UI_sprites;

};
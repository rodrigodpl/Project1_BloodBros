#include "Module.h"

enum fonts{

	WHITE_FONT


};

class ModuleUI : public Module{

public:
	bool Start();
	update_status Update();
	bool CleanUp();

public:

	ModuleFonts* text_manager;
	uint player_score;
	char score_text[10];
	uint dynamite_num;
	uint p1_lives;
	

};
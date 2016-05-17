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
	uint player_score = 0;
	char score_text[10];
	

};
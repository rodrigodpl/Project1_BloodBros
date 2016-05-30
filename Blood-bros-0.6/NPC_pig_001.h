#ifndef __NPC_PIG_001_H__
#define __NPC_PIG_001_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class NPC_Pig_001 : public Enemy
{
private:
	Animation walking_right;
	p2Point<int> orig_pos;
	Path Pig_001_path;

	uint pig_hit_fx;

public:

	NPC_Pig_001(int x, int y);
	~NPC_Pig_001();

	void Update();
};

#endif 
#ifndef __ENEMY_HORSE_001_H__
#define __ENEMY_HORSE_001_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Enemy_Horse_001 : public Enemy
{
private:

	Animation walking;
	Animation running;
	p2Point<int> orig_pos;
	Uint32 timer;

	Path Horse_001_walking_path;
	Path Horse_001_running_path;
	bool mounted;


public:

	Enemy_Horse_001(int x, int y);

	void Update();
};

#endif 
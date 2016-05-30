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
	uint horse_hit_fx, horse_run_fx, riding_channel = -1;

	Path Horse_001_walking_path;
	Path Horse_001_running_path;
	bool mounted;


public:

	Enemy_Horse_001(int x, int y);
	~Enemy_Horse_001();

	void Update();
};

#endif 
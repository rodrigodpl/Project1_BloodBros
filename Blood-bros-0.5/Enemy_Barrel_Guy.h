#ifndef __ENEMY_BARREL_GUY_H__
#define __ENEMY_BARREL_GUY_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Enemy_Barrel_Guy : public Enemy
{
private:

	Animation walking;
	Animation to_protect;
	Animation protect;
	Animation from_protect;
	Animation shooting;
	p2Point<int> orig_pos;
	Path Barrel_Guy_path;


public:

	Enemy_Barrel_Guy(int x, int y);

	void Update();
};

#endif 
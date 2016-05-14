#ifndef __ENEMY_INDIAN_001_H__
#define __ENEMY_INDIAN_001_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Enemy_Indian_001 : public Enemy
{
private:

	Animation walking;
	Animation shooting;
	p2Point<int> orig_pos;
	Path Indian_001_path;


public:

	Enemy_Indian_001(int x, int y);

	void Update();
};

#endif 
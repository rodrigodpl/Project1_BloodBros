#ifndef __ENEMY_INDIAN_002_H__
#define __ENEMY_INDIAN_002_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Enemy_Indian_002 : public Enemy
{
private:

	Animation walking_left;
	Animation walking_right;
	Animation shooting;
	p2Point<int> orig_pos;
	Path Indian_002_path;


public:

	Enemy_Indian_002(int x, int y);

	void Update();
};

#endif 
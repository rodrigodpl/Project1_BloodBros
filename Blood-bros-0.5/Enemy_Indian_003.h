#ifndef __ENEMY_INDIAN_003_H__
#define __ENEMY_INDIAN_003_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Enemy_Indian_003 : public Enemy
{
private:

	Animation walking_left;
	Animation walking_right;
	Animation shooting;
	p2Point<int> orig_pos;
	Path Indian_003_path;


public:

	Enemy_Indian_003(int x, int y);
	bool has_shot = false;

	void Update();
	void Die();
};

#endif 
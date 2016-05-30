#ifndef __ENEMY_CART_001_H__
#define __ENEMY_CART_001_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Enemy_Cart_001 : public Enemy
{
private:

	Animation walking_left;
	Animation shooting;
	p2Point<int> orig_pos;
	Path Cart_001_path;



public:

	Enemy_Cart_001(int x, int y);

	void Update();
};

#endif 
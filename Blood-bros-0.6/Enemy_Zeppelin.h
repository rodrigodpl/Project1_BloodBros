#ifndef __ENEMY_ZEPPELIN_H__
#define __ENEMY_ZEPPELIN_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Enemy_Zeppelin : public Enemy
{
private:

	Animation walking;
	Animation shooting;
	Animation appearing;
	p2Point<int> orig_pos;
	Path Zeppelin_001_path;
	bool has_shot_1, has_shot_2, has_shot_3;
	float appearing_factor;


public:

	Enemy_Zeppelin(int x, int y);

	void Update();
};

#endif 
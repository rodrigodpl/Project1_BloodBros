#ifndef __ENEMY_MOUNTED_INDIAN_001_H__
#define __ENEMY_MOUNTED_INDIAN_001_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Enemy_Mounted_Indian_001 : public Enemy
{
private:

	Animation walking;
	Animation shooting;
	p2Point<int> orig_pos;
	Path Mounted_Indian_001_path;


public:

	Enemy_Mounted_Indian_001(int x, int y);

	void Update();
};

#endif 
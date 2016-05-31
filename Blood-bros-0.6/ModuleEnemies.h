#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "SDL\include\SDL.h"
#include "p2Point.h"


#define MAX_ENEMIES 100


enum ENEMY_TYPES
{
	NO_TYPE,
	INDIAN_001,
	INDIAN_002,
	INDIAN_003,
	BARREL_GUY,
	PIG_001,
	ZEPPELIN,
	MOUNTED_INDIAN_001,
	HORSE_001,
	CART_001
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void check_explosion(int x, int y);

	bool AddEnemy(ENEMY_TYPES type, int x, int y);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__
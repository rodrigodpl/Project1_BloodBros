#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
	friend class ModuleEnemies;
protected:
	Animation* animation;
	Collider* collider;

public:
	iPoint position;
	bool is_protecting = false;

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Update() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void Die() {};
};

#endif // __ENEMY_H__
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

enum enemy_states{

	EN_ST_WALKING,
	EN_ST_SHOOTING,
	EN_ST_PROTECTING,
	EN_ST_DYING

};

class Enemy
{
	friend class ModuleEnemies;
protected:
	Animation* animation;
	Collider* collider;

public:
	iPoint position;
	uint state = EN_ST_WALKING;
	Animation* last_anim = nullptr;
	Animation dying;
	bool is_killable = true;

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Update() {};
	virtual void Draw(SDL_Texture* enemy_sprites);
};

#endif // __ENEMY_H__
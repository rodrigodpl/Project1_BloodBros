#ifndef __SCENARIO_ELEM_H__
#define __SCENARIO_ELEM_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Scenario_elem
{
	friend class ModuleScenario;

protected:
	Animation* animation;
	Collider* collider;

public:
	iPoint position;

public:
	Scenario_elem(int x, int y);
	virtual ~Scenario_elem();

	const Collider* GetCollider() const;

	virtual void Update() {};
	virtual void Draw(SDL_Texture* scenario_sprites);

	int health;
	Animation dying;
};

#endif
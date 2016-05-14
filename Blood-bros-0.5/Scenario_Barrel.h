#ifndef __SCENARIO_BARREL_H__
#define __SCENARIO_BARREL_H__

#include "Scenario_elem.h"
#include "p2Point.h"


class Scenario_Barrel : public Scenario_elem
{
private:

	Animation idle;
	p2Point<int> orig_pos;


public:

	Scenario_Barrel(int x, int y);

};

#endif
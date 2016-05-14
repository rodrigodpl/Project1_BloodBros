#ifndef __SCENARIO_LIGHT_H__
#define __SCENARIO_LIGHT_H__

#include "Scenario_elem.h"
#include "p2Point.h"


class Scenario_Light : public Scenario_elem
{
private:

	Animation idle;
	p2Point<int> orig_pos;


public:

	Scenario_Light(int x, int y);


};

#endif
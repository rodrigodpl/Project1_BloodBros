#ifndef __SCENARIO_WALL_001_H__
#define __SCENARIO_WALL_001_H__

#include "Scenario_elem.h"
#include "p2Point.h"

class Scenario_Wall_001 : public Scenario_elem
{
private:
	
	Animation health_500;
	Animation health_300;
	Animation health_100;



	p2Point<int> orig_pos;

	
public:

	Scenario_Wall_001(int x, int y);

	void Update();

};

#endif 
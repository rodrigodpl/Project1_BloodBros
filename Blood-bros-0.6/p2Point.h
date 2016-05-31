// ----------------------------------------------------
// Point class    -----------
// ----------------------------------------------------

#ifndef __P2POINT_H__
#define __P2POINT_H__

#include "Globals.h"
#include "Animation.h"
#include <math.h>

#define HALF_PLAYER_WIDTH 50
#define HALF_PLAYER_HEIGHT 80
#define DYNAMITE_FRAMES 40
#define CONST_GRAVITY -1


template<class TYPE>
class p2Point
{
public:

	TYPE x, y;

	p2Point()
	{}

	p2Point(const p2Point& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	p2Point(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;
	}

	p2Point& create(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;

		return(*this);
	}

	// Math ------------------------------------------------
	p2Point operator -(const p2Point &v) const
	{
		p2Point r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	p2Point operator + (const p2Point &v) const
	{
		p2Point r;

		r.x = x + v.x;
		r.y = y + v.y;

		return(r);
	}

	const p2Point& operator -=(const p2Point &v)
	{
		x -= v.x;
		y -= v.y;

		return(*this);
	}

	const p2Point& operator +=(const p2Point &v)
	{
		x += v.x;
		y += v.y;

		return(*this);
	}

	bool operator ==(const p2Point& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator !=(const p2Point& v) const
	{
		return (x != v.x || y != v.y);
	}

	// Utils ------------------------------------------------
	bool IsZero() const
	{
		return (x == 0 && y == 0);
	}

	p2Point& SetToZero()
	{
		x = y = 0;
		return(*this);
	}

	p2Point& Negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}


	p2Point<float> GetDirection(p2Point dst){

		p2Point<float> direction;

		direction.y = 0.5;
		direction.x = (((dst.x + HALF_PLAYER_WIDTH) - x) / ((dst.y - HALF_PLAYER_HEIGHT) - y)) * 0.5;

		while((abs(direction.x) + abs(direction.y)) > 5){
			direction.x *= 0.9;
			direction.y *= 0.9;

		}

		while ((abs(direction.x) + abs(direction.y)) < 4){
			direction.x *= 1.1;
			direction.y *= 1.1;

		}


		return(direction);
	}

	// Distances ---------------------------------------------
	TYPE DistanceTo(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (TYPE)sqrtf(float(fx*fx) + float(fy*fy));
	}

	TYPE DistanceNoSqrt(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (fx*fx) + (fy*fy);
	}

	TYPE DistanceManhattan(const p2Point& v) const
	{
		return abs(v.x - x) + abs(v.y - y);
	}

	p2Point<float> GetSpeed(p2Point<float> dst){

		p2Point<float> speed{ ((dst.x - x) / DYNAMITE_FRAMES), (-(800 + ((y - 170) - dst.y))/ 40) };

		return(speed);

	}
};

typedef p2Point<int> iPoint;
typedef p2Point<float> fPoint;

#endif // __P2POINT_H__
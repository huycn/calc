#pragma once
#include <Windows.h>

namespace guitk {

class Point : public POINT
{
public:
	Point()									{ x = y = 0;}
	Point(int x, int y)						{ this->x = x; this->y = y; }
	Point(const POINT &p)					{ x = p.x; y = p.y; }

	Point & operator=(const POINT &other)	{ POINT::operator=(other); return *this; }
};

} // guitk


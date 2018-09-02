#include "vector2Helper.h"



vector2Helper::vector2Helper()
{
	x = y = 0;
}

vector2Helper::vector2Helper(int a, int b)
{
	x = a; y = b;
}

void vector2Helper::set(int a, int b)
{
	x = a; y = b;
}

void vector2Helper::rotate(float angle_r)
{
	float _x = static_cast<float>(x),
		_y = static_cast<float>(y),
		s = sinf(angle_r),
		c = cosf(angle_r),
		a = _x * c - _y * s,
		b = _x * s + _y * c;

	x = static_cast<int>(a);
	y = static_cast<int>(b);
}


vector2Helper::~vector2Helper()
{
}

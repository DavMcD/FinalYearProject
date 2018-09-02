#pragma once
#include <windows.h>
#include <vector>
class vector2Helper
{
public:
	int x, y;

	vector2Helper();
	vector2Helper(int a, int b);
	void set(int a, int b);
	void rotate(float angle_r);

	~vector2Helper();
};


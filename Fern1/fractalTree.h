#pragma once
#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "Bitmap.h"
#include "vector2Helper.h"

class fractalTree
{
public:
	const float PI = 3.1415926536f;
	fractalTree();
	void create(Bitmap* bmp);
	float DegToRadian(float degree);
	void render();

	~fractalTree();
private:
	Bitmap bmp;
	Bitmap* _bmp;
	float     _ang;

	void drawRL(vector2Helper* sp, float line_len, float a, bool rg);
};


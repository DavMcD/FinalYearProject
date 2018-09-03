#pragma once
#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "Bitmap.h"
#include "vector2Helper.h"
#include "Randomizer.h"

class fractalTree
{
public:
	const float PI = 3.1415926536f;
	fractalTree();
	void create(Bitmap* bmp);
	float DegToRadian(float degree);
	void render();
	void getPreGen();

	~fractalTree();
private:
	Bitmap bmp;
	Bitmap* _bmp;
	float     _ang;
	bool userGuided = false;

	Randomizer randFern;
	void setWeightedVariables(std::vector<float>);
	void randomizeVariables();


	//the following are the randomised variables
	const float CONST_angDegrees = 25.0f;
	const float CONST_rightLineMod = 0.7f;
	const float CONST_leftLineMod = 0.7f;
	const float CONST_lineLenMin = 3.0f;
	const float CONST_line_len = 130.0f;

	float angDegrees = CONST_angDegrees;
	float rightLineMod = CONST_rightLineMod;
	float leftLineMod = CONST_leftLineMod;
	float lineLenMin = CONST_lineLenMin;
	float line_len = CONST_line_len;

	void drawRL(vector2Helper* sp, float line_len, float a, bool rg);
};


#pragma once
#include "Bitmap.h"
#include "Randomizer.h"
#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
class fractalFern
{
public:
	fractalFern();
	void getPreGen();
	void render();
	~fractalFern();
private:
	const int BMP_SIZE = 600, ITERATIONS = static_cast<int>(15e5);
	float rnd();
	Bitmap bmp;
	bool userGuided = false;

	Randomizer randFern;

#pragma region private vars
	//the following are the variables used to make the original Barnsley Fern
	//these are used as the benchmark to deviate from if no other data is given to the program
	//The Names have been chosen to give a summary of the effect that they have on the final image, however this is inexact
	const float CONST_LeftLeafCurve = 0.2f;
	const float CONST_RightLeafCurve = .15f;
	const float CONST_LeftLeafSize = .26f;
	const float CONST_RightLeafSize = .26f;
	const float CONST_LeftLeafThinness = .23f;
	const float CONST_RightLeafThickness = .28f;
	const float CONST_LeftAngleWithStem = .22f;
	const float CONST_RightAngleWithStem = .24f;
	const float CONST_LeftLeafSpawnPosition = 1.6f;
	const float CONST_RightLeafSpawnPosition = .44f;
	const float CONST_Spikiness = .85f;
	const float CONST_Curviness = .04f;
	const float CONST_Gravity = .04f;
	const float CONST_Aggressiveness = .85f;
	const float CONST_Size = 1.6f;

	//the following variables are the final values used to create the images
	//this is also the data that is saved to the txt file (in the order they appear here)
	float LeftLeafCurve;
	float RightLeafCurve;
	float LeftLeafSize;
	float RightLeafSize;
	float LeftLeafThinness;
	float RightLeafThickness;
	float LeftAngleWithStem;
	float RightAngleWithStem;
	float LeftLeafSpawnPosition;
	float RightLeafSpawnPosition;
	float Spikiness;
	float Curviness;
	float Gravity;
	float Aggressiveness;
	float Size;

	//the following variables are used to store the average of the previous generation's selections
	float AvgLeftLeafCurve = 0;
	float AvgRightLeafCurve = 0;
	float AvgLeftLeafSize = 0;
	float AvgRightLeafSize = 0;
	float AvgLeftLeafThinness = 0;
	float AvgRightLeafThickness = 0;
	float AvgLeftAngleWithStem = 0;
	float AvgRightAngleWithStem = 0;
	float AvgLeftLeafSpawnPosition = 0;
	float AvgRightLeafSpawnPosition = 0;
	float AvgSpikiness = 0;
	float AvgCurviness = 0;
	float AvgGravity = 0;
	float AvgAggressiveness = 0;
	float AvgSize = 0;
#pragma endregion

	void setWeightedVariables(std::vector<float>);
	void randomizeVariables();
	void randomizeWeightedVariables(int distribution);
	void getAverageFern();
	void getXY(float& x, float& y);
};


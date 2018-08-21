#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "Bitmap.h"

const int BMP_SIZE = 600, ITERATIONS = static_cast<int>(15e5);
const float PI = 3.1415926536f;


class vector2
{
public:
	vector2() { x = y = 0; }
	vector2(int a, int b) { x = a; y = b; }
	void set(int a, int b) { x = a; y = b; }
	void rotate(float angle_r)
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

	int x, y;
};

class fractalTree
{
public:
	fractalTree() { _ang = DegToRadian(24.0f); }
	float DegToRadian(float degree) { return degree * (PI / 180.0f); }

	void create(Bitmap* bmp)
	{
		_bmp = bmp;
		float line_len = 130.0f;

		vector2 sp(_bmp->getWidth() / 2, _bmp->getHeight() - 1);
		MoveToEx(_bmp->getDC(), sp.x, sp.y, NULL);
		sp.y -= static_cast<int>(line_len);
		LineTo(_bmp->getDC(), sp.x, sp.y);

		drawRL(&sp, line_len, 0, true);
		drawRL(&sp, line_len, 0, false);
	}
	void draw()
	{
		std::ofstream fernDataFile("TreeData.txt");


		//this essentially "deselects" the previous generation by resetting the bools that determine which values will be chosen
		for (int i = 0; i < 20; i++)
		{
			fernDataFile << "0 ";
		}
		fernDataFile << std::endl;

		bmp.create(640, 512);
		bmp.setPenColor(RGB(255, 255, 0));

		
		for (int i = 0; i < 20; i++)
		{

			create(&bmp);
			bmp.saveBitmap("./tree" + std::to_string(i) + ".bmp");
			bmp.clear();
			//TODO write data to file
			std::cout << std::to_string((i * 5)) << "% Complete" << std::endl;
		}
		BitBlt(GetDC(GetConsoleWindow()), 0, 20, 648, 512, bmp.getDC(), 0, 0, SRCCOPY);
		system("PAUSE");
	}

private:
	Bitmap bmp;
	void drawRL(vector2* sp, float line_len, float a, bool rg)
	{
		float left_line = line_len;
		line_len *= (0.75f - (std::rand() % 4) / 10.0f);
		left_line *= 0.75f;

		if (line_len < 2.0f) return;

		MoveToEx(_bmp->getDC(), sp->x, sp->y, NULL);
		vector2 r(0, static_cast<int>(line_len));
	
		if (rg) a -= _ang;
		else a += _ang;

		r.rotate(a);
		r.x += sp->x; r.y = sp->y - r.y;

		LineTo(_bmp->getDC(), r.x, r.y);

		drawRL(&r, line_len, a, true);
		drawRL(&r, left_line, a, false);
	}

	Bitmap* _bmp;
	float     _ang;
};
class fern {
public:
	void draw() 
	{
		std::ofstream fernDataFile("FernData.txt");

		fernDataFile << "0 " << std::endl;

		//this essentially "deselects" the previous generation by resetting the bools that determine which values will be chosen
		for (int i = 0; i < 20; i++)
		{
			fernDataFile << "0 ";
		}
		fernDataFile << std::endl;

		//ferns are generated 20 times it give appropriate variation and choice
		for (int i = 0; i < 20; i++)
		{
			srand(time(NULL));

			//this is a progress counter so the user knows the program is running
			std::cout << std::to_string((i * 5)) << "% Complete" << std::endl;

			//if no images were selected from the previous generation, randomize based on the original barnsely fern
			if (userGuided == false)
			{
				randomizeVariables();
			}
			else
			{
				//the first image is always the average of all the previously selected images
				if (i == 0)
				{
					getAverageFern();
				}
				//the next 5 are based off the average with slight deviations
				else if (i < 6)
				{
					randomizeWeightedVariables(1);
				}
				//the next 5 are based off the average with moderate deviations
				else if (i < 11)
				{
					randomizeWeightedVariables(2);
				}
				//the next 5 are based off the average with large deviations
				else if (i < 16)
				{
					randomizeWeightedVariables(3);
				}
				//the last 4 are completely random (to give the user more choice and to stop the data converging too hard)
				else
				{
					randomizeVariables();
				}
			}

			//the following code was found at https://rosettacode.org/wiki/Barnsley_fern
			//this does the actual generation of the image
			bmp.create(BMP_SIZE, BMP_SIZE);
			float x = 0, y = 0; HDC dc = bmp.getDC();
			int hs = BMP_SIZE >> 1;
			for (int f = 0; f < ITERATIONS; f++) {
				SetPixel(dc, hs + static_cast<int>(x * 55.f),
					BMP_SIZE - 15 - static_cast<int>(y * 55.f),
					RGB(static_cast<int>(rnd() * 80.f) + 20,
						static_cast<int>(rnd() * 128.f) + 128,
						static_cast<int>(rnd() * 80.f) + 30));
				getXY(x, y);
			}

			//this saves the file to a .bmp
			bmp.saveBitmap("./bf" + std::to_string(i) + ".bmp");

			//the following writes the data to the txt file, seperating variables by spaces and data sets by lines
			fernDataFile << LeftLeafCurve << " " << RightLeafCurve << " " << LeftLeafSize << " " << RightLeafSize << " " << LeftLeafThinness << " " <<
				RightLeafThickness << " " << LeftAngleWithStem << " " << RightAngleWithStem << " " << LeftLeafSpawnPosition << " " <<
				RightLeafSpawnPosition << " " << Spikiness << " " << Curviness << " " << Gravity << " " << Aggressiveness << " " << Size << " " << std::endl;
		}
	}

	//this function reads the data file to see if any ferns of the previous generation have been chosen
	void getPreGen()
	{
		int count = 0; //the number of selected ferns (for getting the average)
		int varNum = 0;

		//vector of bools indicating which of the last 20 have been selected (true means the were selected)
		std::vector<bool> selectedFerns(20, 0);

		//vector of the values from the previous generation (in case they need to be saved)
		std::vector<double> avgValues(15, 0);
		std::fstream fernDataFile("FernData.txt"); //load in the data file
		int temp = 0;
		fernDataFile >> temp;

		//runs 20 times (the number of ferns generated currently)
		for (int i = 0; i < selectedFerns.size(); i++)
		{
			//save the first 20 variables into the vector of bools
			//the first line (these 20 var) are the variables that determine which data to use from the previos set
			bool tmp;
			fernDataFile >> tmp; //this saves the first variable in the txt file then iterates to the next variable and does the same
			selectedFerns[i] = tmp;
			if (tmp == 1)
			{
				count++; //if one of the ferns are selected add to the count
			}
		}

		//runs 20 times (the number of ferns generated currently)
		for (int i = 0; i < selectedFerns.size(); i++)
		{
			double temp;
			if (selectedFerns[i])
			{
				for (int it = 0; it < avgValues.size(); it++)
				{
					//this goes though each variable then adds it to the according part of the vector
					//at the end of the loop avgValues will contain the sum of each variable of the selected previous generation
					//this will need to be divided at the end to get the true average variable value
					fernDataFile >> temp;
					avgValues[it] += temp;
				}
			}
			else
			{
				for (int it = 0; it < avgValues.size(); it++)
				{
					//this is done as the >> operator not only saves the data but also iterates to the next variable
					//the data is "saved" then immediately discarded then the program iterates to the next piece of data
					//this is done the same number of times as there are data in every set of ferns so it skips to the next fern
					fernDataFile >> temp;
				}
			}
		}

		//if count is bigger than 0, at least 1 fern was selected from the previous generation
		if (count > 0)
		{
			userGuided = true; //this is a bool used to determine whether the draw() should use the default fern generation
			for (int i = 0; i < avgValues.size(); i++)
			{
				//divide each variable by the count to get the average
				avgValues[i] = avgValues[i] / ((double)count);
			}
		}

		//assign the vector values to the corresponding  member variables
		AvgLeftLeafCurve = avgValues[0];
		AvgRightLeafCurve = avgValues[1];
		AvgLeftLeafSize = avgValues[2];
		AvgRightLeafSize = avgValues[3];
		AvgLeftLeafThinness = avgValues[4];
		AvgRightLeafThickness = avgValues[5];
		AvgLeftAngleWithStem = avgValues[6];
		AvgRightAngleWithStem = avgValues[7];
		AvgLeftLeafSpawnPosition = avgValues[8];
		AvgRightLeafSpawnPosition = avgValues[9];
		AvgSpikiness = avgValues[10];
		AvgCurviness = avgValues[11];
		AvgGravity = avgValues[12];
		AvgAggressiveness = avgValues[13];
		AvgSize = avgValues[14];
	}

private:

	Bitmap bmp;

	bool userGuided = false;

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

	void randomizeVariables()
	{
		//this randomizes the variables within a certain range of the Barnsley Fern
		//The random values have been chosen such that the images will deviate enough from the norm
		//  yet still look mostly plant like
		LeftLeafCurve = CONST_LeftLeafCurve + (((rand() % 24) - 12) / 100.0f);
		RightLeafCurve = CONST_RightLeafCurve + (((rand() % 24) - 12) / 100.0f);
		LeftLeafSize = CONST_LeftLeafSize + (((rand() % 24) - 12) / 100.0f);
		RightLeafSize = CONST_RightLeafSize + (((rand() % 24) - 12) / 100.0f);
		LeftLeafThinness = CONST_LeftLeafThinness + (((rand() % 24) - 12) / 100.0f);
		RightLeafThickness = CONST_RightLeafThickness + (((rand() % 24) - 12) / 100.0f);
		LeftAngleWithStem = CONST_LeftAngleWithStem + (((rand() % 24) - 12) / 100.0f);
		RightAngleWithStem = CONST_RightAngleWithStem + (((rand() % 24) - 12) / 100.0f);
		LeftLeafSpawnPosition = CONST_LeftLeafSpawnPosition + (((rand() % 24) - 12) / 100.0f);
		RightLeafSpawnPosition = CONST_RightLeafSpawnPosition + (((rand() % 24) - 12) / 100.0f);
		Spikiness = CONST_Spikiness + (((rand() % 20) - 10) / 100.0f);
		Curviness = CONST_Curviness + (((rand() % 20) - 10) / 100.0f);
		Gravity = CONST_Gravity + (((rand() % 10) - 5) / 100.0f);
		Aggressiveness = CONST_Aggressiveness;
		Size = CONST_Size;
	}

	//The following function randomises the variables based on the selected data from the previous generation
	//the int passed chooses how divergant the variables will be from the base data 
	//(lower is more similar, higher is more divergant)
	void randomizeWeightedVariables(int distribution)
	{
		if (distribution == 1)
		{
			LeftLeafCurve = AvgLeftLeafCurve + (((rand() % 8) - 4) / 100.0f);
			RightLeafCurve = AvgRightLeafCurve + (((rand() % 8) - 4) / 100.0f);
			LeftLeafSize = AvgLeftLeafSize + (((rand() % 8) - 4) / 100.0f);
			RightLeafSize = AvgRightLeafSize + (((rand() % 8) - 4) / 100.0f);
			LeftLeafThinness = AvgLeftLeafThinness + (((rand() % 8) - 4) / 100.0f);
			RightLeafThickness = AvgRightLeafThickness + (((rand() % 8) - 4) / 100.0f);
			LeftAngleWithStem = AvgLeftAngleWithStem + (((rand() % 8) - 4) / 100.0f);
			RightAngleWithStem = AvgRightAngleWithStem + (((rand() % 8) - 4) / 100.0f);
			LeftLeafSpawnPosition = AvgLeftLeafSpawnPosition + (((rand() % 8) - 4) / 100.0f);
			RightLeafSpawnPosition = AvgRightLeafSpawnPosition + (((rand() % 8) - 4) / 100.0f);
			Spikiness = AvgSpikiness + (((rand() % 6) - 3) / 100.0f);
			Curviness = AvgCurviness + (((rand() % 6) - 3) / 100.0f);
			Gravity = AvgGravity + (((rand() % 4) - 2) / 100.0f);
			Aggressiveness = AvgAggressiveness;
			Size = AvgSize;
		}
		else if (distribution == 2)
		{
			LeftLeafCurve = AvgLeftLeafCurve + (((rand() % 12) - 6) / 100.0f);
			RightLeafCurve = AvgRightLeafCurve + (((rand() % 12) - 6) / 100.0f);
			LeftLeafSize = AvgLeftLeafSize + (((rand() % 12) - 6) / 100.0f);
			RightLeafSize = AvgRightLeafSize + (((rand() % 12) - 6) / 100.0f);
			LeftLeafThinness = AvgLeftLeafThinness + (((rand() % 12) - 6) / 100.0f);
			RightLeafThickness = AvgRightLeafThickness + (((rand() % 12) - 6) / 100.0f);
			LeftAngleWithStem = AvgLeftAngleWithStem + (((rand() % 12) - 6) / 100.0f);
			RightAngleWithStem = AvgRightAngleWithStem + (((rand() % 12) - 6) / 100.0f);
			LeftLeafSpawnPosition = AvgLeftLeafSpawnPosition + (((rand() % 12) - 6) / 100.0f);
			RightLeafSpawnPosition = AvgRightLeafSpawnPosition + (((rand() % 12) - 6) / 100.0f);
			Spikiness = AvgSpikiness + (((rand() % 10) - 5) / 100.0f);
			Curviness = AvgCurviness + (((rand() % 10) - 5) / 100.0f);
			Gravity = AvgGravity + (((rand() % 6) - 3) / 100.0f);
			Aggressiveness = AvgAggressiveness;
			Size = AvgSize;
		}
		else if (distribution == 3)
		{
			LeftLeafCurve = AvgLeftLeafCurve + (((rand() % 24) - 12) / 100.0f);
			RightLeafCurve = AvgRightLeafCurve + (((rand() % 24) - 12) / 100.0f);
			LeftLeafSize = AvgLeftLeafSize + (((rand() % 24) - 12) / 100.0f);
			RightLeafSize = AvgRightLeafSize + (((rand() % 24) - 12) / 100.0f);
			LeftLeafThinness = AvgLeftLeafThinness + (((rand() % 24) - 12) / 100.0f);
			RightLeafThickness = AvgRightLeafThickness + (((rand() % 24) - 12) / 100.0f);
			LeftAngleWithStem = AvgLeftAngleWithStem + (((rand() % 24) - 12) / 100.0f);
			RightAngleWithStem = AvgRightAngleWithStem + (((rand() % 24) - 12) / 100.0f);
			LeftLeafSpawnPosition = AvgLeftLeafSpawnPosition + (((rand() % 24) - 12) / 100.0f);
			RightLeafSpawnPosition = AvgRightLeafSpawnPosition + (((rand() % 24) - 12) / 100.0f);
			Spikiness = AvgSpikiness + (((rand() % 20) - 10) / 100.0f);
			Curviness = AvgCurviness + (((rand() % 20) - 10) / 100.0f);
			Gravity = AvgGravity + (((rand() % 10) - 5) / 100.0f);
			Aggressiveness = AvgAggressiveness;
			Size = AvgSize;
		}
	}

	//this generates the average fern of the chosen ferns from the previous generation
	void getAverageFern()
	{
		LeftLeafCurve = AvgLeftLeafCurve;
		RightLeafCurve = AvgRightLeafCurve;
		LeftLeafSize = AvgLeftLeafSize;
		RightLeafSize = AvgRightLeafSize;
		LeftLeafThinness = AvgLeftLeafThinness;
		RightLeafThickness = AvgRightLeafThickness;
		LeftAngleWithStem = AvgLeftAngleWithStem;
		RightAngleWithStem = AvgRightAngleWithStem;
		LeftLeafSpawnPosition = AvgLeftLeafSpawnPosition;
		RightLeafSpawnPosition = AvgRightLeafSpawnPosition;
		Spikiness = AvgSpikiness;
		Curviness = AvgCurviness;
		Gravity = AvgGravity;
		Aggressiveness = AvgAggressiveness;
		Size = AvgSize;
	}

	//must comment this 
	void getXY(float& x, float& y) 
	{
		//fern generation
		float g, xl, yl;
		g = rnd();
		if (g < .01f) { xl = 0; yl = .16f * y; }
		else if (g < .07f) {
			xl = LeftLeafCurve * x - LeftLeafSize * y;
			yl = LeftLeafThinness * x + LeftAngleWithStem * y + LeftLeafSpawnPosition;
		}
		else if (g < .14f) {
			xl = -RightLeafCurve * x + RightLeafThickness* y;
			yl = RightLeafSize * x + RightAngleWithStem * y + RightLeafSpawnPosition;
		}
		else {
			xl = Spikiness * x + Curviness * y;
			yl = -Gravity * x + Aggressiveness * y + Size;
		}
		x = xl; y = yl;
	}
	float rnd() {
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}
};
int main(int argc, char* argv[]) {
	srand(static_cast<unsigned>(time(0)));

	std::fstream fernDataFile("FernData.txt"); //load in the data file
	int isFern = 0;
	fernDataFile >> isFern;

	if (isFern == 0) {
		//we create 1 fern, then re-generate it 20 times and save the image/data after each pass
		fern f;
		std::cout << "Generating Ferns, Please Wait..." << std::endl;

		//the next line calls the function that checks if the fern generation should be weighted (and then does the weighting)
		f.getPreGen();

		//draw() calls the function that generates all the images.
		f.draw();
	}
	else
	{
		std::cout << "Generating Trees, Please Wait..." << std::endl;
		fractalTree tree;
		tree.draw();
	}
	return 0;
}
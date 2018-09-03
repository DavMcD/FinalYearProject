#include "fractalTree.h"



fractalTree::fractalTree()
{
	_ang = DegToRadian(angDegrees);
}

void fractalTree::getPreGen()
{
	//vector of bools indicating which of the last 20 have been selected (true means the were selected)
	std::vector<bool> selectedTrees(20, 0);

	std::vector<std::vector<float>> selectedData; //a list of sets of tree data to be passed to the number generator
	std::fstream fernDataFile("TreeData.txt"); //load in the data file

	int temp = 0;

	//runs 20 times (the number of ferns generated currently)
	for (int i = 0; i < selectedTrees.size(); i++)
	{
		bool tmp;
		fernDataFile >> tmp; //this saves the first variable in the txt file then iterates to the next variable and does the same
		selectedTrees[i] = tmp;
		if (tmp == 1)
		{
			selectedData.push_back(std::vector<float>(5, 0)); //add a vector of 0's of the appropriatesize to fit the data for every selected fern
		}
	}

	//iterator for selected data vector
	int selectDataIter = 0;
	//runs 20 times (the number of trees generated currently)
	for (int i = 0; i < selectedTrees.size(); i++)
	{
		double temp;
		if (selectedTrees[i])
		{
			for (int it = 0; it < 5; it++)
			{
				//this goes though each variable then adds it to the according part of the vector
				//at the end of the loop avgValues will contain the sum of each variable of the selected previous generation
				//this will need to be divided at the end to get the true average variable value
				fernDataFile >> temp;
				selectedData[selectDataIter][it] = temp;
			}
			//after assigning all the values to the nested vector of values, go to the next vector
			selectDataIter++;
		}
		else
		{
			for (int it = 0; it < 5; it++)
			{
				//this is done as the >> operator not only saves the data but also iterates to the next variable
				//the data is "saved" then immediately discarded then the program iterates to the next piece of data
				//this is done the same number of times as there are data in every set of ferns so it skips to the next fern
				fernDataFile >> temp;
			}
		}
	}

	if (selectDataIter > 0)
	{
		//initialise the ranomisation class and pass it the previous data
		randFern.Init(selectedData);

		userGuided = true; //this is a bool used to determine whether the draw()
	}
}

void fractalTree::setWeightedVariables(std::vector<float> newVars)
{
	angDegrees = newVars[0];
	rightLineMod = newVars[1];
	leftLineMod = newVars[2];
	lineLenMin = newVars[3];
	line_len = newVars[4];

	_ang = DegToRadian(angDegrees);
}

void fractalTree::randomizeVariables()
{
	angDegrees = CONST_angDegrees + ((rand() % 30) - 15);
	rightLineMod = CONST_rightLineMod + (((rand() % 2) - 1) / 10.0f);
	leftLineMod = CONST_leftLineMod + (((rand() % 2) - 1) / 10.0f);
	lineLenMin = CONST_lineLenMin + (((rand() % 2) - 1));
	line_len = CONST_line_len + ((rand() % 40) - 20);

	_ang = DegToRadian(angDegrees);
}

void fractalTree::create(Bitmap * bmp)
{
	_bmp = bmp;


	vector2Helper sp(_bmp->getWidth() / 2, _bmp->getHeight() - 1);

	//traslation to the co ords of the bitmap
	MoveToEx(_bmp->getDC(), sp.x, sp.y, NULL);

	//next two lines draw the "trunk" of the tree. Move up (sp.y - line_len), then draw to new point
	sp.y -= static_cast<int>(line_len);
	LineTo(_bmp->getDC(), sp.x, sp.y);


	drawRL(&sp, line_len, 0, true);
	drawRL(&sp, line_len, 0, false);
}

float fractalTree::DegToRadian(float degree)
{
	return degree * (PI / 180.0f);
}

void fractalTree::render()
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
		std::cout << std::to_string((i * 5)) << "% Complete" << std::endl;
		if (!userGuided)
		{
			randomizeVariables();
		}
		else
		{
			if (i == 0)
			{
				setWeightedVariables(randFern.GenerateVariables(1));
			}
			else if (i < 6)
			{
				setWeightedVariables(randFern.GenerateVariables(25));
			}
			else if (i < 11)
			{
				setWeightedVariables(randFern.GenerateVariables(50));
			}
			else if (i < 16)
			{
				setWeightedVariables(randFern.GenerateVariables(75));
			}
			else
			{
				setWeightedVariables(randFern.GenerateVariables(100));
			}
		}

		//the following code was found at https://rosettacode.org/wiki/Fractal_tree
		//this does the actual generation of the image
		create(&bmp);
		bmp.saveBitmap("./tree" + std::to_string(i) + ".bmp");
		bmp.clear();

		fernDataFile << angDegrees << " " << rightLineMod << " " << leftLineMod << " " << lineLenMin << " " << line_len << " " << std::endl;

	}
	//BitBlt(GetDC(GetConsoleWindow()), 0, 20, 648, 512, bmp.getDC(), 0, 0, SRCCOPY);
	system("PAUSE");
}

void fractalTree::drawRL(vector2Helper* sp, float line_len, float a, bool rg)
{
	float left_line = line_len;
	line_len *= rightLineMod;
	left_line *= leftLineMod;

	if (line_len < lineLenMin)
		return;


	MoveToEx(_bmp->getDC(), sp->x, sp->y, NULL);
	vector2Helper r(0, static_cast<int>(line_len));

	if (rg)
	{
		a -= _ang;
	}
	else
	{
		a += _ang;
	}


	r.rotate(a);
	r.x += sp->x; r.y = sp->y - r.y;

	LineTo(_bmp->getDC(), r.x, r.y);


	drawRL(&r, line_len, a, true);
	drawRL(&r, left_line, a, false);

}


fractalTree::~fractalTree()
{
}

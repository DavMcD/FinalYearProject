#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "Bitmap.h"
#include "fractalFern.h"
#include "fractalTree.h"


const float PI = 3.1415926536f;




int main(int argc, char* argv[]) {
	srand(static_cast<unsigned>(time(0)));

	std::fstream fernDataFile("FernData.txt"); //load in the data file
	int isFern = 0;
	fernDataFile >> isFern;

	if (isFern == 0) {
		//we create 1 fern, then re-generate it 20 times and save the image/data after each pass
		fractalFern f;
		std::cout << "Generating Ferns, Please Wait..." << std::endl;

		//the next line calls the function that checks if the fern generation should be weighted (and then does the weighting)
		f.getPreGen();

		//draw() calls the function that generates all the images.
		f.render();
	}
	else
	{
		std::cout << "Generating Trees, Please Wait..." << std::endl;
		fractalTree tree;
		tree.render();
	}
	return 0;
}
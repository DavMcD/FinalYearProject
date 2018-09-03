#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "Bitmap.h"
#include "fractalFern.h"
#include "fractalTree.h"
#include "OBJCreator.h"



const float PI = 3.1415926536f;




int main(int argc, char* argv[]) {
	srand(static_cast<unsigned>(time(0)));

	std::fstream fernDataFile("FernData.txt"); //load in the data file
											   // isFern is a stored in that decided what code block is called
											   // if its between 0 and 19 its an image selection from the GUI that we want to generate an 3D .obj file
											   // if its 100 we want to render 20 new fractal ferns
											   // if its 200 we want to render 20 new fractal trees
	int isFern = 0;
	//retiving the data from the fernData file
	fernDataFile >> isFern;
	// if is fern =  100 do fractal fern generation
	if (isFern == 100) {
		//we create 1 fern, then re-generate it 20 times and save the image/data after each pass
		fractalFern f;
		std::cout << "Generating Ferns, Please Wait..." << std::endl;

		//the next line calls the function that checks if the fern generation should be weighted (and then does the weighting)
		f.getPreGen();

		//draw() calls the function that generates all the images.
		f.render();
	}
	// if isFern = 200 do fractal tree generation
	else if (isFern == 200)
	{
		std::cout << "Generating Trees, Please Wait..." << std::endl;
		fractalTree tree;
		tree.render();
	}
	//generate the obj and mtl files with the selected image
	else
	{
		creator->createOBJ("quad" + to_string(isFern), "bf" + to_string(isFern) + ".bmp");
	}

	return 0;
}
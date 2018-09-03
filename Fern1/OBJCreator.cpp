#include "OBJCreator.h"


//constructor for the obj file creator
OBJCreator::OBJCreator()
{
	//sets the % completed
	complete = 0;
}

void OBJCreator::createOBJ(string fileName, string imageFileName)
{
	//calls the create material file method passing the desired file name and image texture name
	createMTLFile(fileName, imageFileName);
	//calls the create wavefront .obj method passing the desired file name 
	createOBJFile(fileName, imageFileName);
}


OBJCreator::~OBJCreator()
{
	// empty deconstructor
}

void OBJCreator::createMTLFile(string fileName, string imageFileName)
{
	//sets the file exstention string to .mtl
	string fileNameExtention = ".mtl";
	//create and open the newly created file with our name and exstention name
	MTLFile.open(fileName + fileNameExtention);
	//saves the string that creates the content of the .mtl file. adding the new image txture name and the end
	MTLFile << "# Blender MTL File: \'None'\# Material Count : 1\n\nnewmtl Material.001\nNs 96.078431\nKa 1.000000 1.000000 1.000000\nKd 0.640000 0.640000 0.640000\nKs 0.500000 0.500000 0.500000\nKe 0.000000 0.000000 0.000000\nNi 1.000000\nd 1.000000\nillum 2\nmap_Kd " << imageFileName << endl;
	//adds 50% to the completion
	complete += 50;
	//printing the % completed
	cout << to_string(complete) << "% Complete" << endl;
}

void OBJCreator::createOBJFile(string fileName, string imageFileName)
{
	//sets the file exstention string to .mtl
	string fileNameExtention = ".obj";
	//create and open the newly created file with our name and exstention name
	OBJFile.open(fileName + fileNameExtention);
	//saves the string that creates the content of the .obj file. linking it to the created .mtl file
	string f = "# Blender v2.79 (sub 0) OBJ File: ''\n# www.blender.org\nmtllib quad.mtl\no Cube\nv 0.010000 -1.000000 -1.000000\nv 0.010000 -1.000000 1.000000\nv -0.010000 -1.000000 1.000000\nv -0.010000 -1.000000 -1.000000\nv 0.010000 1.000000 -0.999999\nv 0.010000 1.000000 1.000001\nv -0.010000 1.000000 1.000000\nv -0.010000 1.000000 -1.000000\nvt 0.000000 0.000000\nvt 0.000000 1.000000\nvt -1.000000 1.000000\nvt -1.000000 0.000000\nvt 1.000000 0.000000\nvt 2.000000 0.000000\nvt 2.000000 1.000000\nvt 1.000000 1.000000\nvt 1.000000 2.000000\nvt 0.000000 2.000000\nvt 0.000000 -2.000000\nvt 1.000000 -2.000000\nvt 1.000000 -1.000000\nvt 0.000000 -1.000000\nvn 0.0000 -1.0000 0.0000\nvn 0.0000 1.0000 0.0000\nvn 1.0000 0.0000 0.0000\nvn -0.0000 -0.0000 1.0000\nvn -1.0000 -0.0000 -0.0000\nvn 0.0000 0.0000 -1.0000\nusemtl Material.001\ns off\nf 1/1/1 2/2/1 3/3/1 4/4/1\nf 5/5/2 8/6/2 7/7/2 6/8/2\nf 1/1/3 5/5/3 6/8/3 2/2/3\nf 2/2/4 6/8/4 7/9/4 3/10/4\nf 3/11/5 7/12/5 8/13/5 4/14/5\nf 5/5/6 1/1/6 4/14/6 8/13/6";
	OBJFile << f << endl;
	//adds 50% to the completion
	complete += 50;
	//printing the % completed
	cout << to_string(complete) << "% Complete" << endl;
}

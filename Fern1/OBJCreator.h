#pragma once
#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
class OBJCreator
{
public:
	OBJCreator();
	void createOBJ(string fileName, string imageFileName);
	~OBJCreator();
private:
	string fileName;
	int complete = 0;
	ofstream MTLFile;
	ofstream OBJFile;
	void createMTLFile(string filename, string imageFileName);
	void createOBJFile(string fileName, string imageFileName);
};


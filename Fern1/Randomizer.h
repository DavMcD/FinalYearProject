#pragma once
#include <vector>
#include <math.h>
#include <random>
class Randomizer
{
public:
	Randomizer();
	std::vector <float> GenerateVariables(int);
	std::vector <float> GenerateVariables();
	void Init(std::vector<std::vector<float>>);
	~Randomizer();
private:
	std::vector<std::vector<float>> ListOfDataSets;
	void CalculateDeviation();
	bool validData = true;
	//array of standard deviations, one for each variable in the array
	std::vector <float> standardDeviation;
	std::vector<float> varMean;
	std::default_random_engine generator;

};


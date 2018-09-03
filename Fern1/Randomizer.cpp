#include "Randomizer.h"



Randomizer::Randomizer()
{
	int i = 0;
}

void Randomizer::Init(std::vector<std::vector<float>> data)
{
	ListOfDataSets = data;
	//if the vector is empty, the data isnt valid
	if (ListOfDataSets.size() == 0)
	{
		validData = false;
	}

	//all vectors need to be the same size, sets a bool to be false if they are not so the class knows
	for (int i = 0; i < ListOfDataSets.size(); i++)
	{
		if (ListOfDataSets[0].size() != ListOfDataSets[i].size())
		{
			validData = false;
			break;
		}
	}

	//calculate mean and deviation for randomising variables
	CalculateDeviation();
}

std::vector<float> Randomizer::GenerateVariables(int weight)
{
	if (weight > 100)
	{
		weight = 100;
	}
	else if (weight < 0)
	{
		weight = 0;
	}

	float stdDisModifier = weight / 50.0f;

	std::vector<float> returnVec;
	if (validData)
	{

		for (int i = 0; i < varMean.size(); i++)
		{
			//this randomises based on Gaussian number distrobution
			std::normal_distribution<float> distribution(varMean[i], (standardDeviation[i]* stdDisModifier));
			returnVec.push_back( distribution(generator));
		}
	}

	return returnVec;
}

std::vector<float> Randomizer::GenerateVariables()
{
	std::vector<float> returnVec;
	if (validData)
	{

		for (int i = 0; i < varMean.size(); i++)
		{
			//this randomises based on Gaussian number distrobution
			std::normal_distribution<float> distribution(varMean[i], (standardDeviation[i]));
			returnVec.push_back(distribution(generator));
		}
	}

	return returnVec;
}




Randomizer::~Randomizer()
{
}

void Randomizer::CalculateDeviation()
{
	//make an array of 0's of the same size as the data sets. This will store the mean of each variable type
	varMean = std::vector<float>(ListOfDataSets[0].size(), 0.0f);
	//first calculate the mean of the values
	//iterate through the list of data sets
	for (int i = 0; i < ListOfDataSets.size(); i++)
	{
		//iterate through the variables, add each to the mean vector to get a list of the sum of the values
		for (int it = 0; it < ListOfDataSets[i].size(); it++)
		{
			varMean[it] = varMean[it] + ListOfDataSets[i][it];
		}
	}
	for (int i = 0; i < varMean.size(); i++)
	{
		//divide by the number of data sets, this gives us the mean
		varMean[i] = (varMean[i] / (float)ListOfDataSets.size());
	}

	std::vector<float> distToMeanSqr = std::vector<float>(ListOfDataSets[0].size(), 0.0f);
	//for each data point, get the difference between the value and the mean and square the result
	//then get the mean of those squared numbers
	for (int i = 0; i < ListOfDataSets.size(); i++)
	{
		for (int it = 0; it < ListOfDataSets[i].size(); it++)
		{
			//first we addup the difference squared and add to the vector
			distToMeanSqr[it] = distToMeanSqr[it] + ((varMean[it] - ListOfDataSets[i][it]) * (varMean[it] - ListOfDataSets[i][it]));
		}
	}
	for (int i = 0; i < distToMeanSqr.size(); i++)
	{
		//then we divide by the number of data sets, and square root that number to get the standard deviations
		distToMeanSqr[i] = (distToMeanSqr[i] / (float)ListOfDataSets.size());

		//cannot take 0 as an argument
		if (sqrt(distToMeanSqr[i]) > 0.000001f)
		{
			standardDeviation.push_back(sqrt(distToMeanSqr[i]));
		}
		else
		{
			standardDeviation.push_back(0.000001f);
		}
		
	}
}

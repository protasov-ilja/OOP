// vector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VectorProcessor.h"

void PrintVector(const std::vector<double>& numbersVector);
void ReadVector(std::vector<double>& numbersVector);

int main()
{
	std::vector<double> numbersVector;
	ReadVector(numbersVector);
	ProcessVector(numbersVector);
	std::sort(numbersVector.begin(), numbersVector.end());
	PrintVector(numbersVector);

	return 0;
}

void ReadVector(std::vector<double>& numbersVector)
{
	copy(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), back_inserter(numbersVector));
}

void PrintVector(const std::vector<double>& numbersVector)
{
	std::cout << std::fixed << std::setprecision(3);
	std::copy(numbersVector.begin(), numbersVector.end(), std::ostream_iterator<double>(std::cout, " "));
	std::cout << std::endl;
}

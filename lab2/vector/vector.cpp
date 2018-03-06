// vector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

void processVector(vector<double>& numbersVector);
void printVector(vector<double>& numbersVector);
bool readVector(vector<double>& numbersVector);

int main()
{
	vector<double> numbersVector;
	bool isEmpty = readVector(numbersVector);
	if (isEmpty)
	{
		cout << "vector is empty" << endl;
		return 1;
	}

	processVector(numbersVector);
	printVector(numbersVector);

	return 0;
}

bool readVector(vector<double>& numbersVector)
{
	std::copy(std::istream_iterator<double>(cin), std::istream_iterator<double>(), std::back_inserter(numbersVector));
	if (numbersVector.empty())
	{
		return true;
	}

	return false;
}

void printVector(vector<double>& numbersVector)
{
	cout << fixed << setprecision(3);
	copy(numbersVector.begin(), numbersVector.end(), ostream_iterator<double>(cout, " "));
	cout << endl;
}

void processVector(vector<double>& numbersVector)
{
	double smallestNumber = *std::min_element(std::begin(numbersVector), std::end(numbersVector));
	for (size_t i = 0; i < numbersVector.size(); ++i)
	{
		numbersVector[i] *= smallestNumber;
	}

	std::sort(numbersVector.begin(), numbersVector.end());
}

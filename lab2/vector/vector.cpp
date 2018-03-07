// vector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

void processVector(vector<double>& numbersVector);
void printVector(const vector<double>& numbersVector);
bool readVector(vector<double>& numbersVector);

int main()
{
	vector<double> numbersVector;
	if (readVector(numbersVector))
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
	copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(numbersVector));
	if (numbersVector.empty())
	{
		return true;
	}

	return false;
}

void printVector(const vector<double>& numbersVector)
{
	cout << fixed << setprecision(3);
	copy(numbersVector.begin(), numbersVector.end(), ostream_iterator<double>(cout, " "));
	cout << endl;
}

void processVector(vector<double>& numbersVector)
{
	sort(numbersVector.begin(), numbersVector.end());
	double smallestNumber = numbersVector[0];
	for (size_t i = 0; i < numbersVector.size(); ++i)
	{
		numbersVector[i] *= smallestNumber;
	}
}

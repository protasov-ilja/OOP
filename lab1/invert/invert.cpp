// invert.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const short MATRIX_SIZE = 3;

bool CheckInputNumber(const char* inputString, int& number);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: invert.exe <input matrix file>\n";
		return 1;
	}

	ifstream fileIn(argv[1]);
	if (!fileIn.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	double matrix[3][3];
	bool ReadStringsInMatrix(fileIn);

	return 0;
}

bool ReadStringsInMatrix(ifstream& fileIn)
{

}

bool CheckInputNumber(const char* inputString, int& number)
{
	try
	{
		number = stoi(inputString);
		if ((number < 0) || (number > 255))
		{
			cout << "Argument " << inputString << " is less then 0 or more than 255\n";
			return false;
		}
	}
	catch (const invalid_argument& isError)
	{
		cout << isError.what() << "\n";
		return false;
	}
	catch (const out_of_range& isError)
	{
		cout << isError.what() << "\n";
		return false;
	}
	return true;
}

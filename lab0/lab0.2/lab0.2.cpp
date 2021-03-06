// lab0.2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int SumDigits(int i);
bool StringToInt(const char* inputString, int& number);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: lab0.2.exe <upper bound>\n";
		return 1;
	}

	int upperBound;
	if (!StringToInt(argv[1], upperBound))
	{
		return 1;
	}

	for (int i = 1; i <= upperBound; ++i)
	{
		int sum = SumDigits(i);
		if ((i % sum) == 0)
		{
			if (i != 1)
			{
				cout << ", ";
			}

			cout << i;
		}
	}

	cout << endl;

	return 0;
}

int SumDigits(int i)
{
	int sum = 0;
	while (i != 0)
	{
		sum += i % 10;
		i /= 10;
	}

	return sum;
}

bool StringToInt(const char* inputString, int& number)
{
	try
	{
		number = stoi(inputString);
		if (number < 1)
		{
			cout << "Argument " << inputString << " is less then 1\n";
			return false;
		}
	}
	catch (const exception& error)
	{
		cout << error.what() << "\n";
		return false;
	}

	return true;
}

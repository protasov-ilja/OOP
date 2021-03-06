// lab0.3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>
#include <string>

using namespace std;

const int LINE_BREAK = 5;

bool StringToInt(const char* inputString, int& number);
void PrintFibNumbers(int upperBound);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: lab0.3.exe <upper bound>\n";
		return 1;
	}

	int sum = 0;
	int i = 1;
	int upperBound;
	if (!StringToInt(argv[i], upperBound))
	{
		return 1;
	}

	PrintFibNumbers(upperBound);

	return 0;
}

void PrintFibNumbers(int upperBound)
{
	int prevNum = 0;
	cout << prevNum << ", ";
	int currNum = 1;
	int lineLen = 2;
	while (upperBound - prevNum >= currNum)
	{
		int nextNum = prevNum + currNum;
		cout << nextNum;
		prevNum = currNum;
		currNum = nextNum;
		if (upperBound - prevNum >= currNum)
		{
			cout << ", ";
		}
		else
		{
			cout << endl;
			break;
		}

		if (lineLen % LINE_BREAK == 0)
		{
			cout << "\n";
			lineLen = 0;
		}

		lineLen++;
	}
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

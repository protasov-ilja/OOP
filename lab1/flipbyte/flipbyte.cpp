// flipbyte.cpp : Defines the entry point for the console application.
// Take int number and Flip bits in it

#include "stdafx.h"

using namespace std;

bool CheckInputNumber(const char* inputString, int& number);
uint8_t FlipByte(uint8_t originalByte);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: flipbyte.exe <input byte>\n";
		return 1;
	}

	int number;
	bool isInt = CheckInputNumber(argv[1], number);
	if (isInt)
	{
		uint8_t byte = static_cast<uint8_t>(number);
		int result = static_cast<int>(FlipByte(byte));
		cout << result << endl;

		return 0;
	}

	return 1;
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

uint8_t FlipByte(uint8_t originalByte)
{
	const int MAX_SHIFT = 8;
	uint8_t newByte = 0;
	uint8_t maskBit = 1;

	for (int i = MAX_SHIFT; i > 0; --i)
	{
		newByte <<= 1;
		newByte |= originalByte & maskBit;
		originalByte >>= 1;
	}
	return newByte;
}

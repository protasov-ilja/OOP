// prime_numbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PrimeNumberSetGenerator.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>

bool CheckInputNumber(const std::string& inputString, int& number);
void PrintPrimeNumbers(std::set<int>& primeNumbersSet);

int main()
{
	std::string upperBoundString;
	std::cin >> upperBoundString;
	int upperBound;
	if (!CheckInputNumber(upperBoundString, upperBound))
	{
		return 1;
	}

	std::set<int> primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	PrintPrimeNumbers(primeNumbersSet);
	std::cout << static_cast<int>(primeNumbersSet.size());

	return 0;
}

void PrintPrimeNumbers(std::set<int>& primeNumbersSet)
{
	std::copy(primeNumbersSet.begin(), primeNumbersSet.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

bool CheckInputNumber(const std::string& inputString, int& number)
{
	try
	{
		number = stoi(inputString);
		if ((number > 100000000) || (number < 2))
		{
			std::cout << "Argument " << inputString << " is less then 2 or more than 100000000\n";
			return false;
		}
	}
	catch (const std::invalid_argument& isError)
	{
		std::cout << isError.what() << "\n";
		return false;
	}
	catch (const std::out_of_range& isError)
	{
		std::cout << isError.what() << "\n";
		return false;
	}

	return true;
}

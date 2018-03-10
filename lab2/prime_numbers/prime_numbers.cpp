// prime_numbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound);
bool CheckInputNumber(const std::string inputString, int& number);
std::set<int> CopyPrimeNumbersInSet(std::vector<int>& numbersCheck);
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

bool CheckInputNumber(const std::string inputString, int& number)
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

std::set<int> CopyPrimeNumbersInSet(std::vector<int>& numbersCheck)
{
	std::set<int> primeNumbers;
	for (size_t i = 2; i < numbersCheck.size(); ++i)
	{
		if (numbersCheck[i])
		{
			primeNumbers.insert(static_cast<int>(i));
		}
	}

	return primeNumbers;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	upperBound++;
	std::vector<int> numbersCheck(upperBound, true);
	for (size_t i = 2; i * i < numbersCheck.size(); ++i)
	{
		if (numbersCheck[i])
		{
			for (size_t j = i * i; j < numbersCheck.size(); j += i)
			{
				numbersCheck[j] = false;
			}
		}
	}

	return CopyPrimeNumbersInSet(numbersCheck);
}

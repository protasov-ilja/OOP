#include "stdafx.h"
#include "PrimeNumberSetGenerator.h"

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

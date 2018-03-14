#include "stdafx.h"
#include "PrimeNumberSetGenerator.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	upperBound++;
	std::vector<bool> sieveForNumbers(upperBound, true);
	for (size_t i = 2; i * i < sieveForNumbers.size(); ++i)
	{
		if (sieveForNumbers[i])
		{
			for (size_t j = i * i; j < sieveForNumbers.size(); j += i)
			{
				sieveForNumbers[j] = false;
			}
		}
	}

	return CopyPrimeNumbersInSet(sieveForNumbers);
}

std::set<int> CopyPrimeNumbersInSet(const std::vector<bool>& numbersCheck)
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

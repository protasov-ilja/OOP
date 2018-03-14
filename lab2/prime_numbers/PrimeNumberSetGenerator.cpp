#include "stdafx.h"
#include "PrimeNumberSetGenerator.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<bool> sieveForNumbers(upperBound + 1, true);
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

	return CopyPrimeNumbersToSet(sieveForNumbers);
}

std::set<int> CopyPrimeNumbersToSet(const std::vector<bool>& numbersCheck)
{
	std::set<int> primeNumbers;
	for (size_t i = 2; i < numbersCheck.size(); ++i)
	{
		if (numbersCheck[i])
		{
			primeNumbers.insert(primeNumbers.end(), static_cast<int>(i));
		}
	}

	return primeNumbers;
}

#include "stdafx.h"
#include "VectorProcessor.h"

void ProcessVector(std::vector<double>& numbersVector)
{
	if (!numbersVector.empty())
	{
		const double SMALLEST_NUMBER = *std::min_element(begin(numbersVector), end(numbersVector));
		auto MultiplyNumberByMinNumber = [&SMALLEST_NUMBER](const double& number) {
			return number * SMALLEST_NUMBER;
		};

		std::transform(numbersVector.begin(), numbersVector.end(), numbersVector.begin(), MultiplyNumberByMinNumber);
	}
}

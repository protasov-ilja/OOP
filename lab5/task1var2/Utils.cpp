#include "stdafx.h"
#include "Utils.h"

namespace Utils
{
bool CompareDoubleNumbers(double number1, double number2)
{
	double diff = number1 - number2;

	return std::abs(diff) < DBL_EPSILON;
}
} // namespace Utils

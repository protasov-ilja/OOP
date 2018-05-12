#pragma once
#include "stdafx.h"
#include <cmath>
#include "float.h"

namespace Utils
{
	inline bool CompareDoubleNumbers(double number1, double number2)
	{
		double diff = number1 - number2;

		return std::abs(diff) < DBL_EPSILON;
	}

} // namespace Utils
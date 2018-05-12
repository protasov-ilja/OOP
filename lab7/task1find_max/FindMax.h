#pragma once
#include <functional>
#include <vector>

template <typename T, typename Less = std::less<T>>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = Less())
{
	if (arr.empty())
	{
		return false;
	}

	auto maxElemIt = arr.begin();
	for (auto it = arr.begin() + 1; it != arr.end(); ++it)
	{
		if (less(*maxElemIt, *it))
		{
			maxElemIt = it;
		}
	}

	maxValue = *maxElemIt;

	return true;
}
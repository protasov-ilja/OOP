#pragma once
#include <functional>
#include <vector>

template <typename T, typename Less = std::less<T>>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	auto maxElemIt = arr.begin();
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		if (less(*maxElemIt, *it))
		{
			maxElemIt = it;
		}
	}

	maxValue = *maxElemIt;

	return true;
}
//
//template <typename T>
//bool FindMax(std::vector<T> const& arr, T& maxValue)
//{
//	if (arr.empty())
//	{
//		return false;
//	}
//
//	auto maxElemIt = arr.begin();
//	for (auto it = arr.begin(); it != arr.end(); ++it)
//	{
//		if (*maxElemIt < *it)
//		{
//			maxElemIt = it;
//		}
//	}
//
//	maxValue = *maxElemIt;
//
//	return true;
//}
//
//
//template <>
//bool FindMax<const char*>(std::vector<const char*> const& arr, const char*& maxValue)
//{
//	if (arr.empty())
//	{
//		return false;
//	}
//
//	auto maxElemIt = arr.begin();
//	for (auto it = arr.begin(); it != arr.end(); ++it)
//	{
//		if (strcmp(*maxElemIt, *it) < 0)
//		{
//			maxElemIt = it;
//		}
//	}
//
//	maxValue = *maxElemIt;
//	return true;
//}

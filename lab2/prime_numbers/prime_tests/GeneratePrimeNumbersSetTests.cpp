#include "stdafx.h"
#include "..\PrimeNumberSetGenerator.h"
#include <chrono>

using namespace std;

bool SetsAreEqual(set<int> const& x, set<int> const& y)
{
	return x == y;
}

bool SizeSetsAreEqual(size_t x, size_t y)
{
	return x == y;
}

bool ExecutionTimeWithinAllowedValue(int maxTime, int realTime)
{
	return maxTime >= realTime;
}

BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)

	BOOST_AUTO_TEST_CASE(set_with_one_prime_number_on_border)
	{
		set<int> oneElementSet;
		oneElementSet.insert(2);
		set<int> onePrimeNumberSet = GeneratePrimeNumbersSet(2);
		BOOST_CHECK(SetsAreEqual(onePrimeNumberSet, oneElementSet));
	}

	BOOST_AUTO_TEST_CASE(set_with_two_prime_numbers)
	{
		set<int> oneElementSet;
		oneElementSet.insert(2);
		oneElementSet.insert(3);
		set<int> onePrimeNumberSet = GeneratePrimeNumbersSet(3);
		BOOST_CHECK(SetsAreEqual(onePrimeNumberSet, oneElementSet));
	}

	BOOST_AUTO_TEST_CASE(check_for_set_with_max_upper_bound_size_and_speed)
	{
		const int maxUpperBound = 100000000;
		const int MAX_EXECUTION_TIME = 12000;
		const size_t ESTIMATED_SIZE = 5761455;
		chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();
		set<int> maxNumbersSet = GeneratePrimeNumbersSet(maxUpperBound);
		chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
		int receivedTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
		BOOST_CHECK(SizeSetsAreEqual(ESTIMATED_SIZE, maxNumbersSet.size()));
		BOOST_CHECK(ExecutionTimeWithinAllowedValue(MAX_EXECUTION_TIME, receivedTime));
	}
BOOST_AUTO_TEST_SUITE_END()

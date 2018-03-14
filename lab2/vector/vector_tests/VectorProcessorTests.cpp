#include "stdafx.h"
#include "..\VectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

// Функция ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	// Создает пустой вектор из пустого вектора
	BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
	{
		vector<double> emptyVector;
		ProcessVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

	// при обработке вектора с одним числом
	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_one_number)
		// должна умножить это число на само себя
		BOOST_AUTO_TEST_CASE(should_mul_this_number_by_each_element)
		{
			vector<double> numbers = { -1};
			ProcessVector(numbers);

			BOOST_CHECK(VectorsAreEqual( numbers, 
				{ (-1 * -1) }
			));
		}
	BOOST_AUTO_TEST_SUITE_END()

	// при обработке вектора с несколькими элементами
	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_several_elements)
		// должен умножить их минимальный элемент на каждый элемент вектора
		BOOST_AUTO_TEST_CASE(should_mul_min_element_by_each_element_in_vector)
		{
			vector<double> numbers = { -1.2, 1.2, 2.3, 3.2 };
			ProcessVector(numbers);

			const double MIN_NUMBER = -1.2;
			BOOST_CHECK(VectorsAreEqual(numbers,
			{ (-1.2 * MIN_NUMBER), (1.2 * MIN_NUMBER), (2.3 * MIN_NUMBER), (3.2 * MIN_NUMBER) }
			));
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()



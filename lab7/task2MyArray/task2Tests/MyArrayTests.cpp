#include "stdafx.h"
#include "..\MyArray.h"

using namespace std;

struct ArrayItem
{
	ArrayItem(int value = 0)
		: value(value)
	{
	}
	int value;
};

struct EmptyStringArray
{
	CMyArray<ArrayItem> arr;
};

bool ArraysAreEqual(const CMyArray<ArrayItem>& arr1, const CMyArray<ArrayItem>& arr2)
{
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (arr1[i].value != arr2[i].value)
		{
			return false;
		}
	}
	return arr1.GetSize() == arr2.GetSize();
}

BOOST_FIXTURE_TEST_SUITE(MyArray, EmptyStringArray)
	// по умолчанию
	BOOST_AUTO_TEST_SUITE(by_default)
		// пуст
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
		}
		// имеет вместимость 0
		BOOST_AUTO_TEST_CASE(has_0_capacity)
		{
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 0u);
		}

		BOOST_AUTO_TEST_CASE(hasnt_access_by_index)
		{
			ArrayItem item;
			BOOST_CHECK_THROW(item = arr[0], std::out_of_range);
			BOOST_CHECK_THROW(item = arr[-1], std::out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()
	// после добавления элемента
	BOOST_AUTO_TEST_SUITE(after_appending_an_item)
		// увеличитвает свой размер и вместимость
		BOOST_AUTO_TEST_CASE(increases_its_size_and_capacity)
		{
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 1u);
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 2u);
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
		}

		BOOST_AUTO_TEST_CASE(it_becomes_available_at_the_back)
		{
			arr.Append(1);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 1);
			arr.Append(2);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 2);
			arr.Append(3);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 3);
			arr.Append(4);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 4);
		}

		BOOST_AUTO_TEST_CASE(has_access_by_index)
		{
			BOOST_CHECK_NO_THROW(arr.Append(1));
			BOOST_CHECK_EQUAL(arr[0].value, 1);
			BOOST_CHECK_NO_THROW(arr.Append(2));
			BOOST_CHECK_EQUAL(arr[1].value, 2);
			BOOST_CHECK_NO_THROW(arr.Append(3));
			BOOST_CHECK_EQUAL(arr[2].value, 3);
			BOOST_CHECK_NO_THROW(arr.Append(4));
			BOOST_CHECK_EQUAL(arr[3].value, 4);
			BOOST_CHECK_THROW(auto item = arr[4], std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(hasnt_access_and_throw_exception_if_index_is_out_of_range)
		{
			arr.Append(1);
			BOOST_CHECK_THROW(auto item = arr[1], std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(can_be_resized)
		{
			for (auto i = 1; i <= 4; ++i)
			{
				arr.Append(i);
			}

			BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
			BOOST_CHECK_NO_THROW(arr.Resize(10));
			BOOST_CHECK_EQUAL(arr.GetSize(), 10u);
			BOOST_CHECK_EQUAL(arr[9].value, ArrayItem().value);
			BOOST_CHECK_NO_THROW(arr.Resize(2));
			BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
			BOOST_CHECK_EQUAL(arr[1].value, 2);
			BOOST_CHECK_NO_THROW(arr.Resize(4));
			BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
			BOOST_CHECK_THROW(auto item = arr[5], std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			for (auto i = 1; i <= 2; ++i)
			{
				arr.Append(i);
			}

			BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
			BOOST_CHECK_NO_THROW(arr.Clear());
			BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
		}
	BOOST_AUTO_TEST_SUITE_END()

	// после создания копии
	BOOST_AUTO_TEST_SUITE(after_copy_construction)
		// имеет размер, равный размеру исходного массива
		BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
		{
			for (auto i = 0; i < 6; ++i)
			{
				arr.Append(i);
			}

			BOOST_CHECK_NE(arr.GetSize(), arr.GetCapacity());
			auto copy(arr);
			BOOST_CHECK_EQUAL(copy.GetSize(), arr.GetSize());
			BOOST_CHECK_EQUAL(copy.GetCapacity(), arr.GetSize());
		}

		BOOST_AUTO_TEST_CASE(can_use_copying_assignment_operator)
		{
			for (auto i = 0; i < 6; ++i)
			{
				arr.Append(i);
			}

			auto tempCopy(arr);
			arr = arr;
			BOOST_CHECK(ArraysAreEqual(arr, tempCopy));
			auto copyArr = arr;
			BOOST_CHECK(ArraysAreEqual(arr, copyArr));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_moving_construction)
		BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
		{
			for (auto i = 0; i < 6; ++i)
			{
				arr.Append(i);
			}

			BOOST_CHECK_NE(arr.GetSize(), arr.GetCapacity());
			size_t capacity = arr.GetCapacity();
			auto copy(move(arr));
			BOOST_CHECK_EQUAL(copy.GetSize(), 6);
			BOOST_CHECK_EQUAL(copy.GetCapacity(), capacity);
			BOOST_CHECK_EQUAL(arr.GetSize(), 0);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 0);
		}

	BOOST_AUTO_TEST_CASE(changes_data_of_first_arr_to_data_of_second_by_using_moving_assignment_operator)
	{
		arr.Append(1);
		BOOST_CHECK_EQUAL(arr.GetSize(), 1);
		BOOST_CHECK_EQUAL(arr.GetCapacity(), 1);
		CMyArray<ArrayItem> arr2(arr);
		for (auto i = 0; i < 3; ++i)
		{
			arr2.Append(i);
		}

		arr = move(arr2);
		BOOST_CHECK_EQUAL(arr.GetSize(), 4);
		BOOST_CHECK_EQUAL(arr.GetCapacity(), 4);
	}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

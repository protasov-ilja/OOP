#include "stdafx.h"
#include "..\WorkWithDictionary.h"

using namespace std;

bool MapsAreEqual(const DictionaryMap& x, const DictionaryMap& y)
{
	return x == y;
}

BOOST_AUTO_TEST_SUITE(AddTranslationInDictionary_function)

	BOOST_AUTO_TEST_CASE(send_not_empty_word_and_its_translation_and_add_them_in_map)
	{
		DictionaryMap checkMap{
			{ "cat", "���" }
		};

		DictionaryMap sourceMap;
		AddTranslationInDictionary(sourceMap, "cat", "���");
		BOOST_CHECK(MapsAreEqual(sourceMap, checkMap));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RequestTranslation_function)

	BOOST_AUTO_TEST_CASE(send_empty_string_and_does_not_change_map)
	{
		DictionaryMap checkMap{
			{ "hello", "������" },
			{ "world", "���" }
		};

		DictionaryMap sourceMap{
			{ "hello", "������" },
			{ "world", "���" }
		};

		bool isNotEmpty;
		if (isNotEmpty = CheckExistenceOfTranslation("cat", ""))
		{
			AddTranslationInDictionary(sourceMap, "cat", "");
		}

		BOOST_CHECK(isNotEmpty == false);
		BOOST_CHECK(MapsAreEqual(sourceMap, checkMap));
	}

	BOOST_AUTO_TEST_CASE(send_not_empty_string_and_change_map)
	{
		DictionaryMap checkMap{
			{ "cat", "���" }
		};

		DictionaryMap sourceMap;
		bool isNotEmpty;
		if (isNotEmpty = CheckExistenceOfTranslation("cat", "���"))
		{
			AddTranslationInDictionary(sourceMap, "cat", "���");
		}

		BOOST_CHECK(isNotEmpty == true);
		BOOST_CHECK(MapsAreEqual(sourceMap, checkMap));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FindAndDisplayTranslation_function)

	BOOST_AUTO_TEST_CASE(search_for_nonexistent_word_and_return_false)
	{
		DictionaryMap sourceMap{
			{ "cat", "���" },
			{ "world", "���" }
		};

		bool isFound = FindAndDisplayTranslation(sourceMap, "hello");
		BOOST_CHECK(isFound == false);
	}

	BOOST_AUTO_TEST_CASE(search_for_existent_word_and_return_true)
	{
		DictionaryMap sourceMap{
			{ "hello", "������" },
			{ "world", "���" }
		};

		bool isFound = FindAndDisplayTranslation(sourceMap, "hello");
		BOOST_CHECK(isFound == true);
	}
BOOST_AUTO_TEST_SUITE_END()

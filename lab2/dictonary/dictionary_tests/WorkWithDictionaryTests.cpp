#include "stdafx.h"
#include "..\WorkWithDictionary.h"

using namespace std;

bool MapsAreEqual(const std::map<std::string, std::string>& x, const std::map<std::string, std::string>& y)
{
	return x == y;
}

BOOST_AUTO_TEST_SUITE(AddWordAndTranslationInDictionary_function)

	BOOST_AUTO_TEST_CASE(send_empty_string_and_does_not_change_map)
	{
		std::map<std::string, std::string> checkMap{
			{ "hello", "привет" },
			{ "world", "мир" }
		};
		std::map<std::string, std::string> sourceMap{
			{ "hello", "привет" },
			{ "world", "мир" }
		};
		bool isNotEmpty = AddWordAndTranslationInDictionary(sourceMap, "cat", "");
		BOOST_CHECK(isNotEmpty == false);
		BOOST_CHECK(MapsAreEqual(sourceMap, checkMap));
	}

	BOOST_AUTO_TEST_CASE(send_not_empty_string_and_change_map)
	{
		std::map<std::string, std::string> checkMap{
			{ "cat", "кот" }
		};
		std::map<std::string, std::string> sourceMap;
		bool isNotEmpty = AddWordAndTranslationInDictionary(sourceMap, "cat", "кот");
		BOOST_CHECK(isNotEmpty == true);
		BOOST_CHECK(MapsAreEqual(sourceMap, checkMap));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FindAndDisplayTranslation_function)

	BOOST_AUTO_TEST_CASE(search_for_nonexistent_word_and_return_false)
	{
		std::map<std::string, std::string> sourceMap{
			{ "cat", "кот" },
			{ "world", "мир" }
		};
		bool isFound = FindAndDisplayTranslation(sourceMap, "hello");
		BOOST_CHECK(isFound == false);
	}

	BOOST_AUTO_TEST_CASE(search_for_existent_word_and_return_true)
	{
		std::map<std::string, std::string> sourceMap{
			{ "hello", "привет" },
			{ "world", "мир" }
		};
		bool isFound = FindAndDisplayTranslation(sourceMap, "hello");
		BOOST_CHECK(isFound == true);
	}
BOOST_AUTO_TEST_SUITE_END()

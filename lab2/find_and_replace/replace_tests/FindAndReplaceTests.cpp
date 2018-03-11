// TrimBlanksTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../FindAndReplace.h"

namespace
{
	void VerifyFindAndReplace(const std::string& sourceStr, const std::string& searchedStr, const std::string& replacedStrs, const std::string& expectedReplacedString)
	{
		BOOST_CHECK_EQUAL(FindAndReplace(sourceStr, searchedStr, replacedStrs), expectedReplacedString);
	}
} // namespace

BOOST_AUTO_TEST_SUITE(FindAndReplace_function)
	BOOST_AUTO_TEST_CASE(must_convert_empty_string_to_empty_string)
	{
		VerifyFindAndReplace("", "hello", "goodbay", "");
	}

	BOOST_AUTO_TEST_CASE(leaves_string_without_searched_string_unchanged)
	{
		VerifyFindAndReplace("text without replace", "hello", "world", "text without replace");
	}

	BOOST_AUTO_TEST_CASE(replaces_one_character_within_word)
	{
		VerifyFindAndReplace("text with replace", "a", "f", "text with replfce");
	}

	BOOST_AUTO_TEST_CASE(replaces_one_character_separately_from_word)
	{
		VerifyFindAndReplace("h std  ", "h", "f", "f std  ");
	}

	BOOST_AUTO_TEST_CASE(replaces_substring_within_string)
	{
		VerifyFindAndReplace("replaces substring within string", "replaces substring", "replaced", "replaced within string");
	}

	BOOST_AUTO_TEST_CASE(duplicates_symbol_when_replacing)
	{
		VerifyFindAndReplace("duplicates the symbol when replacing", "l", "ll", "dupllicates the symboll when repllacing");
	}
BOOST_AUTO_TEST_SUITE_END()

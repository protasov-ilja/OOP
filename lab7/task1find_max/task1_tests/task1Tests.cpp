#include "stdafx.h"
#include "..\FindMax.h"
#include <string>

// функция FindMax
TEST_CASE("function FindMaxEx")
{
	// для типа int
	SECTION("can return its start point")
	{
		// может вернуть максимальное число, если вектор не пуст
		SECTION("can return its start point")
		{
			std::vector<int> intVector{ 1, 2, 3, 4 };
			int maxElement;
			REQUIRE(FindMax(intVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == 4);
		}

		// может вернуть число, если вектор состоит из 1 элемента
		SECTION("can return its start point")
		{
			std::vector<int> intVector{ 4 };
			int maxElement;
			REQUIRE(FindMax(intVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == 4);
		}

		// не может вернуть число, если вектор пуст
		SECTION("can return its start point")
		{
			std::vector<int> intVector;
			int maxElement;
			REQUIRE_FALSE(FindMax(intVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
		}
	}

	// для типа float
	SECTION("can return its start point")
	{
		// может вернуть максимальное число, если вектор не пуст
		SECTION("can return its start point")
		{
			std::vector<float> floatVector{ 1.2f, 2.2f, 3.3f, 4.3f };
			float maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == 4.3f);
		}

		// может вернуть число, если вектор состоит из 1 элемента
		SECTION("can return its start point")
		{
			std::vector<float> floatVector{ 4.5f };
			float maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == 4.5f);
		}

		// не может вернуть число, если вектор пуст
		SECTION("can return its start point")
		{
			std::vector<float> floatVector;
			float maxElement;
			REQUIRE_FALSE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
		}
	}

	// для типа string
	SECTION("can return its start point")
	{
		// может вернуть наибольшую строку, если вектор не пуст
		SECTION("can return its start point")
		{
			std::vector<std::string> floatVector{ "a", "ab", "abc", "abd" };
			std::string maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == "abd");
		}

		// может вернуть строку, если вектор состоит из 1 элемента
		SECTION("can return its start point")
		{
			std::vector<std::string> floatVector{ "abc" };
			std::string maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == "abc");
		}

		// не может вернуть наибольшую строку, если вектор пуст
		SECTION("can return its start point")
		{
			std::vector<std::string> floatVector;
			std::string maxElement;
			REQUIRE_FALSE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
		}
	}

	// для типа string
	SECTION("can return its start point")
	{
		// может вернуть наибольшую строку, если вектор не пуст
		SECTION("can return its start point")
		{
			std::vector<std::string> floatVector{ "a", "ab", "abc", "abd" };
			std::string maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == "abd");
		}

		// может вернуть строку, если вектор состоит из 1 элемента
		SECTION("can return its start point")
		{
			std::vector<std::string> floatVector{ "abc" };
			std::string maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == "abc");
		}

		// не может вернуть наибольшую строку, если вектор пуст
		SECTION("can return its start point")
		{
			std::vector<std::string> floatVector;
			std::string maxElement;
			REQUIRE_FALSE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
		}
	}

	// для типа const char*
	SECTION("can return its start point")
	{
		// может вернуть наибольшую строку, если вектор не пуст
		SECTION("can return its start point")
		{
			std::vector<const char*> floatVector{ "a", "ab", "abc", "abd" };
			const char* maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return strcmp(x, y) < 0;
			}));
			REQUIRE(maxElement == "abd");
		}

		// может вернуть строку, если вектор состоит из 1 элемента
		SECTION("can return its start point")
		{
			std::vector<const char*> floatVector{ "abc" };
			const char* maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return strcmp(x, y) < 0;
			}));
			REQUIRE(maxElement == "abc");
		}

		// не может вернуть наибольшую строку, если вектор пуст
		SECTION("can return its start point")
		{
			std::vector<const char*> floatVector;
			const char* maxElement;
			REQUIRE_FALSE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return strcmp(x, y) < 0;
			}));
		}
	}

	// для типа someType
	SECTION("can return its start point")
	{
		struct SomeType
		{
			int intElem;
			float floatElem;
			std::string stringElem;
		};

		// может вернуть наибольший элемент, если вектор не пуст
		SECTION("can return its start point")
		{
			std::vector<SomeType> someTypeVector{ { 1, 1.1f, "a" }, { 2, 2.1f, "abd" }, { 3, 4.1f, "abc" }, { 4, 3.1f, "ab" } };
			SomeType maxElement;
			REQUIRE(FindMax(someTypeVector, maxElement, [](const auto& x, const auto& y) {
				return x.intElem < y.intElem;
			}));
			REQUIRE(maxElement.intElem == 4);

			REQUIRE(FindMax(someTypeVector, maxElement, [](const auto& x, const auto& y) {
				return x.floatElem < y.floatElem;
			}));
			REQUIRE(maxElement.floatElem == 4.1f);

			REQUIRE(FindMax(someTypeVector, maxElement, [](const auto& x, const auto& y) {
				return x.stringElem < y.stringElem;
			}));
			REQUIRE(maxElement.stringElem == "abd");
		}

		// может вернуть элемент, если вектор состоит из 1 элемента
		SECTION("can return its start point")
		{
			std::vector<SomeType> someTypeVector{ { 1, 1.1f, "abc" } };
			SomeType maxElement;
			REQUIRE(FindMax(someTypeVector, maxElement, [](const auto& x, const auto& y) {
				return x.intElem < y.intElem;
			}));
			REQUIRE(maxElement.intElem == 1);

			REQUIRE(FindMax(someTypeVector, maxElement, [](const auto& x, const auto& y) {
				return x.floatElem < y.floatElem;
			}));
			REQUIRE(maxElement.floatElem == 1.1f);

			REQUIRE(FindMax(someTypeVector, maxElement, [](const auto& x, const auto& y) {
				return x.stringElem < y.stringElem;
			}));
			REQUIRE(maxElement.stringElem == "abc");
		}

		// не может вернуть наибольший элемент, если вектор пуст
		SECTION("can return its start point")
		{
			std::vector<SomeType> someTypeVector;
			SomeType maxElement;
			REQUIRE_FALSE(FindMax(someTypeVector, maxElement, [](const auto& x, const auto& y) {
				return x.stringElem < y.stringElem;
			}));
			REQUIRE_FALSE(FindMax(someTypeVector, maxElement, [](const auto& x, const auto& y) {
				return x.intElem < y.intElem;
			}));
			REQUIRE_FALSE(FindMax(someTypeVector, maxElement, [](const auto& x, const auto& y) {
				return x.floatElem < y.floatElem;
			}));
		}
	}
}

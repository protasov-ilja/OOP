#include "stdafx.h"
#include "..\FindMax.h"
#include <string>

// ������� FindMax
TEST_CASE("function FindMax")
{
	// ��� ���� int
	SECTION("for type int")
	{
		// ����� ������� ������������ �����, ���� ������ �� ����
		SECTION("can return maximum number if vector isnt empty")
		{
			std::vector<int> intVector{ 1, 2, 3, 4 };
			int maxElement;
			REQUIRE(FindMax(intVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == 4);
		}

		// ����� ������� �����, ���� ������ ������� �� 1 ��������
		SECTION("can return number if vector consists of 1 element")
		{
			std::vector<int> intVector{ 4 };
			int maxElement;
			REQUIRE(FindMax(intVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == 4);
		}

		// �� ����� ������� �����, ���� ������ ���� ���������� ����
		SECTION("cant return number if vector is empty returns false")
		{
			std::vector<int> intVector;
			int maxElement;
			REQUIRE_FALSE(FindMax(intVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
		}
	}

	// ��� ���� float
	SECTION("for type float")
	{
		// ����� ������� ������������ �����, ���� ������ �� ����
		SECTION("can return maximum number if vector isnt empty")
		{
			std::vector<float> floatVector{ 1.2f, 2.2f, 3.3f, 4.3f };
			float maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == 4.3f);
		}

		// ����� ������� �����, ���� ������ ������� �� 1 ��������
		SECTION("can return number if vector consists of 1 element")
		{
			std::vector<float> floatVector{ 4.5f };
			float maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == 4.5f);
		}

		// �� ����� ������� �����, ���� ������ ����
		SECTION("cant return number if vector is empty returns false")
		{
			std::vector<float> floatVector;
			float maxElement;
			REQUIRE_FALSE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
		}
	}

	// ��� ���� string
	SECTION("for string type")
	{
		// ����� ������� ���������� ������, ���� ������ �� ����
		SECTION("can return largest string if vector isnt empty")
		{
			std::vector<std::string> floatVector{ "a", "ab", "abc", "abd" };
			std::string maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == "abd");
		}

		// ����� ������� ������, ���� ������ ������� �� 1 ��������
		SECTION("can return string if vector consists of 1 element")
		{
			std::vector<std::string> floatVector{ "abc" };
			std::string maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
			REQUIRE(maxElement == "abc");
		}

		// �� ����� ������� ���������� ������, ���� ������ ���� ���������� ����
		SECTION("cant return largest string if vector is empty returns false")
		{
			std::vector<std::string> floatVector;
			std::string maxElement;
			REQUIRE_FALSE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return x < y;
			}));
		}
	}

	// ��� ���� const char*
	SECTION("can return its start point")
	{
		// ����� ������� ���������� ������, ���� ������ �� ����
		SECTION("can return largest string if vector isnt empty")
		{
			std::vector<const char*> floatVector{ "a", "ab", "abc", "abd" };
			const char* maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return strcmp(x, y) < 0;
			}));
			REQUIRE(maxElement == "abd");
		}

		// ����� ������� ������, ���� ������ ������� �� 1 ��������
		SECTION("can return string if vector consists of 1 element")
		{
			std::vector<const char*> floatVector{ "abc" };
			const char* maxElement;
			REQUIRE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return strcmp(x, y) < 0;
			}));
			REQUIRE(maxElement == "abc");
		}

		// �� ����� ������� ���������� ������, ���� ������ ���� ���������� ����
		SECTION("cant return largest string if vector is empty returns false")
		{
			std::vector<const char*> floatVector;
			const char* maxElement;
			REQUIRE_FALSE(FindMax(floatVector, maxElement, [](const auto& x, const auto& y) {
				return strcmp(x, y) < 0;
			}));
		}
	}

	// ��� ���� someType
	SECTION("for someType")
	{
		struct SomeType
		{
			int intElem;
			float floatElem;
			std::string stringElem;
		};

		// ����� ������� ���������� �������, ���� ������ �� ����
		SECTION("can return largest element if vector isnt empty")
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

		// ����� ������� �������, ���� ������ ������� �� 1 ��������
		SECTION("can return element if vector consists of 1 element")
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

		// �� ����� ������� ���������� �������, ���� ������ ���� ���������� ����
		SECTION("cant return largest element if vector is empty returns false")
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

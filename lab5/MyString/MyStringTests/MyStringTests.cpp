#include "stdafx.h"
#include "../CMyString.h"
#include <sstream>

bool AreStringsEqual(const CMyString& string1, const char* string2, size_t length)
{
	if (string1.GetLength() != length)
	{
		return false;
	}

	for (size_t i = 0; i < length; ++i)
	{
		if (string1.GetStringData()[i] != string2[i])
		{
			return false;
		}
	}

	return true;
}

// ������
TEST_CASE("test myString")
{
	// ����� ������� ���� ��������� � �������� �����������
	SECTION("can create its own instance with zero parameters")
	{
		CMyString string;
		REQUIRE(AreStringsEqual(string, "", 0));
	}

	// ����� ������� ���� ��������� �� ������ ������
	SECTION("can create its own instance from empty string")
	{
		CMyString string("");
		REQUIRE(AreStringsEqual(string, "", 0));
		CMyString string1;
		REQUIRE(AreStringsEqual(string1, "\0", 0));
	}

	// ����� ������� ���� ��������� �� �� ������ ������
	SECTION("can create its own instance from non-empty string")
	{
		CMyString string("a");
		REQUIRE(AreStringsEqual(string, "a", 1));
		CMyString string1("testString");
		REQUIRE(AreStringsEqual(string1, "testString", 10));
	}

	// ����� ������� ���� ��������� �� ������ ������ � �� �����
	SECTION("can create its own instance from empty string and its length")
	{
		CMyString string("", 0);
		REQUIRE(AreStringsEqual(string, "", 0));
		CMyString string1("\0", 0);
		REQUIRE(AreStringsEqual(string1, "\0", 0));
	}

	// ����� ������� ���� ��������� �� �� ������ ������ � �� �����
	SECTION("can create its own instance of non-empty string and its length")
	{
		CMyString string("a", 1);
		REQUIRE(AreStringsEqual(string, "a", 1));
		CMyString string1("a\0a", 3);
		REQUIRE(AreStringsEqual(string1, "a\0a", 3));
		CMyString string2("\0aa", 3);
		REQUIRE(AreStringsEqual(string2, "\0aa", 3));
	}

	// ����� ������� ���� ��������� �� ������ ���������� STL
	SECTION("can create its own instance from string of STL library")
	{
		std::string str("");
		CMyString string(str);
		REQUIRE(AreStringsEqual(string, str.c_str(), str.length()));
		str = "abc";
		CMyString string1(str);
		REQUIRE(AreStringsEqual(string1, str.c_str(), str.length()));
	}

	// ����� ������� ���� ��������� �� ������� ���������� CMyString ��������� ����������� �����������
	SECTION("can create its own instance from another CMyString instance using copy constructor")
	{
		CMyString string("test");
		CMyString string1(string);
		REQUIRE(AreStringsEqual(string1, string.GetStringData(), string.GetLength()));
	}

	// ����� ������� ���� ��������� �� ������� ���������� CMyString ��������� ����������� �����������
	SECTION("can create its own instance from another CMyString instance using move constructor")
	{
		CMyString string("test");
		CMyString string1(std::move(string));
		REQUIRE(AreStringsEqual(string1, "test", 4));
	}
}

// ����� �������� �����
TEST_CASE("GetLength method")
{
	// ����� ������� ����� ������
	SECTION("can return length of string")
	{
		CMyString string("test");
		REQUIRE(string.GetLength() == 4);
		CMyString emptyString("");
		REQUIRE(emptyString.GetLength() == 0);
		CMyString emptyString1;
		REQUIRE(emptyString1.GetLength() == 0);
	}
}

// ����� �������� ������ ������
TEST_CASE("GetStringData method")
{
	// ����� ������� ��������� �� ������ �������� ������
	SECTION("can return pointer to array of string characters")
	{
		CMyString string("test");
		REQUIRE(string.GetStringData()[0] == string[0]);
		REQUIRE(string.GetStringData()[2] == string[2]);
		REQUIRE(string.GetStringData()[4] == '\0');
	}
}

// ����� ���������
TEST_CASE("SubString method")
{
	// ����� ������� ��������� �������� ��������� �������� � ������
	SECTION("can return substring specified by starting position and length")
	{
		CMyString string("testSrting");
		REQUIRE(string.SubString(0, 1) == "t");
		REQUIRE(string.SubString(0, 10) == "testSrting");
		REQUIRE(string.SubString(2, 6) == "stSrti");
		CMyString emptyString("");
		REQUIRE(emptyString.SubString(0, 0) == "");
		REQUIRE(string.SubString(9, 0) == "");
	}

	// ���������� ��������� �� ��������� ������� ����������� �� m_length ���� ��������� ������� ����������� + ����� ��������� > max_size ��� m_length
	SECTION("cant return substring if initial copy position is < 0 or >= m_length")
	{
		CMyString string("string");
		REQUIRE(string.SubString(0, SIZE_MAX) == "string");
		REQUIRE(string.SubString(3, SIZE_MAX) == "ing");
		REQUIRE(string.SubString(3, 5) == "ing");
	}

	// ����� ������� ������ ������ ���� ��������� ������� ����������� ������ ����� �������� ������
	SECTION("cant return substring if initial copy position is >= m_length")
	{
		CMyString string("string");
		REQUIRE(string.SubString(7, 3) == "");
		REQUIRE(string.SubString(22, 2) == "");
		REQUIRE(string.SubString(6, 1) == "");
	}
}

// ����� �������
TEST_CASE("Clear method")
{
	// ����� �������� ������
	SECTION("can clear string")
	{
		CMyString string("test");
		REQUIRE(AreStringsEqual(string, "test", 4));
		string.Clear();
		REQUIRE(AreStringsEqual(string, "", 0));
	}
}

struct CMyStringFixture
{
	size_t stringLength = 6;
	CMyString string;
	CMyStringFixture()
		: string("string", stringLength)
	{
	}
};

// ������������� ��������
TEST_CASE_METHOD(CMyStringFixture, "overloaded operator")
{
	// ������������
	SECTION("=")
	{
		// �� ������ ������ ������ ��� ������������ ����� ����
		SECTION("doesnt change data of string when assigning itself")
		{
			string = string;
			REQUIRE(AreStringsEqual(string, "string", stringLength));
		}

		// ������ ������ ������ ������ �� ������ ������
		SECTION("changes data of first string to the data of second")
		{
			string = "new str";
			REQUIRE(AreStringsEqual(string, "new str", 7));
			CMyString str2("str");
			string = str2;
			REQUIRE(AreStringsEqual(string, "str", 3));
		}
	}

	// �������� ����
	SECTION("+")
	{
		// ����� ���������� ��������� �������� ���� ����������� ������ CMyString
		SECTION("can return result of addition of two instances of class CMyString")
		{
			string = "string";
			CMyString emptyStr("");
			CMyString string2("string2");
			CMyString string3("str");
			CMyString str = emptyStr + string2;
			REQUIRE(str == "string2");
			REQUIRE(AreStringsEqual(str, "string2", 7));
			str = emptyStr + emptyStr;
			REQUIRE(str == "");
			REQUIRE(AreStringsEqual(str, "", 0));
			str = string3 + emptyStr;
			REQUIRE(str == "str");
			REQUIRE(AreStringsEqual(str, "str", 3));
			str = string + string2 + string3;
			REQUIRE(str == "stringstring2str");
			REQUIRE(AreStringsEqual(str, "stringstring2str", 16));
		}

		// ����� ���������� ��������� �������� ���������� ������ CMyString � ������ std::string
		SECTION("can return result of adding instance of class CMyString and class std::string")
		{
			std::string string2("string2");
			CMyString str1 = string + string2;
			CMyString str2 = string2 + string;
			REQUIRE(AreStringsEqual(str1, "stringstring2", 13));
			REQUIRE(AreStringsEqual(str2, "string2string", 13));
		}

		// ����� ���������� ��������� �������� ���������� ������ CMyString � const char*
		SECTION("can return result of adding instance of class CMyString and const char*")
		{
			CMyString str1 = string + "string2";
			CMyString str2 = "string2" + string;
			REQUIRE(AreStringsEqual(str1, "stringstring2", 13));
			REQUIRE(AreStringsEqual(str2, "string2string", 13));
		}
	}

	// ������������ � �������������
	SECTION("+=")
	{
		// ����� ��������� � ������1 ������2 ������ CMyString
		SECTION("can add to string1 the string2 of the class CMyString")
		{
			CMyString string1("string1");
			string1 += string;
			REQUIRE(AreStringsEqual(string1, "string1string", 13));
		}
	}

	// ���������
	SECTION("==")
	{
		// ��� ��������� ���� ����� ���������� ������ ��� �� ���������
		SECTION("when comparing two strings returns true if they are equal")
		{
			CMyString string2("string");
			REQUIRE(string == string2);
			REQUIRE(AreStringsEqual(string, string2.GetStringData(), 6));
			CMyString string3("");
			string2 = "";
			REQUIRE(string2 == string3);
			REQUIRE(AreStringsEqual(string2, string3.GetStringData(), 0));
		}

		// ��� ��������� ���� ����� ���������� ���� ��� �� �� ���������
		SECTION("when comparing two strings returns false if they dont equal")
		{
			CMyString string2("strinh");
			REQUIRE_FALSE((string == string2));
			REQUIRE_FALSE(AreStringsEqual(string, string2.GetStringData(), 6));
			string2 = "tes";
			REQUIRE_FALSE((string == string2));
			REQUIRE_FALSE(AreStringsEqual(string, string2.GetStringData(), 3));
			string2 = "string1";
			REQUIRE_FALSE((string == string2));
			REQUIRE_FALSE(AreStringsEqual(string, string2.GetStringData(), 7));
		}
	}

	// �����������
	SECTION("!=")
	{
		// ��� ��������� ���� ����� ���������� ������ ��� �� �� ���������
		SECTION("when comparing two strings returns true if they dont equal")
		{
			CMyString string2("strinh");
			REQUIRE(string != string2);
			REQUIRE_FALSE(AreStringsEqual(string, string2.GetStringData(), 6));
			string2 = "tes";
			REQUIRE(string != string2);
			REQUIRE_FALSE(AreStringsEqual(string, string2.GetStringData(), 3));
			string2 = "string1";
			REQUIRE(string != string2);
			REQUIRE_FALSE(AreStringsEqual(string, string2.GetStringData(), 7));
		}

		// ��� ��������� ���� ����� ���������� ���� ��� �� ���������
		SECTION("when comparing two strings returns false if they are equal")
		{
			CMyString string2("string");
			REQUIRE_FALSE(string != string2);
			REQUIRE(AreStringsEqual(string, string2.GetStringData(), 6));
		}
	}

	// ���������������� ������� � �������� ������ �� �������������� ������� ��� ������
	SECTION("[]")
	{
		// ����� �� ������� ��������� ������ �� ������
		SECTION("can read character from string by index")
		{
			auto ch = string[0];
			REQUIRE(ch == 's');
			ch = string[5];
			REQUIRE(ch == 'g');
			ch = string[2];
			REQUIRE(ch == 'r');
		}

		// �� ����� ��������� ������ �� ������ ���� ������ < 0 ��� >= ����� ������
		SECTION("cant read character from string if index is < 0 or > = length of string")
		{
			try
			{
				auto ch = string[-1];
			}
			catch (std::out_of_range const& error)
			{
				REQUIRE(static_cast<const std::string&>("index is out of range") == error.what());
			}
			
			try
			{
				auto ch = string[6];
			}
			catch (std::out_of_range const& error)
			{
				REQUIRE(static_cast<const std::string&>("index is out of range") == error.what());
			}

			try
			{
				auto ch = string[100];
			}
			catch (std::out_of_range const& error)
			{
				REQUIRE(static_cast<const std::string&>("index is out of range") == error.what());
			}
		}
	}

	// ���������������� ������� � �������� ������ �� �������������� ������� ��� ������
	SECTION("[]")
	{
		// ����� �� ������� ���������� ������ � ������
		SECTION("can write character in string by index")
		{
			CMyString str("string");
			auto ch = 'g';
			str[0] = ch;
			REQUIRE(str[0] == 'g');
			str[2] = ch;
			REQUIRE(str[2] == 'g');
			str[5] = 's';
			REQUIRE(str[5] == 's');
		}

		// �� ����� ���������� ������ � ������ ���� ������ < 0 ��� >= ����� ������
		SECTION("cant write character to string if index is < 0 or > = length of string")
		{
			CMyString str("string");
			auto ch = 'g';
			try
			{
				str[-1] = ch;
			}
			catch (std::out_of_range const& error)
			{
				REQUIRE(static_cast<const std::string&>("index is out of range") == error.what());
			}

			try
			{
				str[6] = ch;
			}
			catch (std::out_of_range const& error)
			{
				REQUIRE(static_cast<const std::string&>("index is out of range") == error.what());
			}

			try
			{
				str[7] = ch;
			}
			catch (std::out_of_range const& error)
			{
				REQUIRE(static_cast<const std::string&>("index is out of range") == error.what());
			}
		}
	}

	// <
	SECTION("< ")
	{
		// ����� ������� ������ ���� ������ 1 ������ ������ 2
		SECTION("can return true if string 1 is less than string 2")
		{
			CMyString string2("string1");
			REQUIRE(string < string2);
			string2 = "strink";
			REQUIRE(string < string2);
		}

		// ����� ������� ���� ���� ������ 1 �� ������ ������ 2
		SECTION("can return false if string 1 isnt less than string 2")
		{
			CMyString string2("strin");
			REQUIRE_FALSE(string < string2);
			string2 = "string";
			REQUIRE_FALSE(string < string2);
			string2 = "strina";
			REQUIRE_FALSE(string < string2);
			string2 = "";
			REQUIRE_FALSE(string < string2);
		}
	}

	// >=
	SECTION(">=")
	{
		// ����� ������� ������ ���� ������ 1 ������ ��� ����� ������ 2
		SECTION("can return true if string 1 is greater than or equal to string 2")
		{
			CMyString string2("strin");
			REQUIRE(string >= string2);
			string2 = "strina";
			REQUIRE(string >= string2);
			string2 = "string";
			REQUIRE(string >= string2);
		}

		// ����� ������� ���� ���� ������ 1 ������ ������ 2
		SECTION("can return false if string 1 is less than string 2")
		{
			CMyString string2("string1");
			REQUIRE_FALSE(string >= string2);
			string2 = "strink";
			REQUIRE_FALSE(string >= string2);
		}
	}

	// >
	SECTION("> ")
	{
		// ����� ������� ������ ���� ������ 1 ������ ������ 2
		SECTION("can return true if string 1 is greater than string 2")
		{
			CMyString string2("strin");
			REQUIRE(string > string2);
			string2 = "strina";
			REQUIRE(string > string2);
			string2 = "";
			REQUIRE(string > string2);
		}

		// ����� ������� ���� ���� ������ 1 �� ������ ������ 2
		SECTION("can return false if string 1 isnt greater than string 2")
		{
			CMyString string2("string1");
			REQUIRE_FALSE(string > string2);
			string2 = "strink";
			REQUIRE_FALSE(string > string2);
			string2 = "string";
			REQUIRE_FALSE(string > string2);
		}
	}

	// <=
	SECTION("<=")
	{
		// ����� ������� ������ ���� ������ 1 ������ ��� ����� ������ 2
		SECTION("can return true if string 1 is less than or equal to string 2")
		{
			CMyString string2("string1");
			REQUIRE(string <= string2);
			string2 = "strink";
			REQUIRE(string <= string2);
			string2 = "string";
			REQUIRE(string <= string2);
		}

		// ����� ������� ���� ���� ������ 1 ������ ������ 2
		SECTION("can return false if string 1 is greater than string 2")
		{
			CMyString string2("strin");
			REQUIRE_FALSE(string <= string2);
			string2 = "strina";
			REQUIRE_FALSE(string <= string2);
		}
	}

	// ���������� �� ������
	SECTION(">>")
	{
		// ����� ��������� ������ �� ������
		SECTION("can read string from the stream")
		{
			std::stringstream strm("string");
			CMyString str;
			strm >> str;
			REQUIRE(AreStringsEqual(str, "string", 6));
		}
	}

	// ������ � �����
	SECTION("<<")
	{
		// ����� �������� ������ � �����
		SECTION("can write string into stream")
		{
			std::stringstream strm;
			strm << string;
			REQUIRE(strm.str() == "string");
		}
	}
}

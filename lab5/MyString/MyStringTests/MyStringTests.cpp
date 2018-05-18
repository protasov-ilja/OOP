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

// строка
TEST_CASE("test myString")
{
	// может создать свой экземпляр с нулевыми параметрами
	SECTION("can create its own instance with zero parameters")
	{
		CMyString string;
		REQUIRE(AreStringsEqual(string, "", 0));
	}

	// может создать свой экземпляр из пустой строки
	SECTION("can create its own instance from empty string")
	{
		CMyString string("");
		REQUIRE(AreStringsEqual(string, "", 0));
		CMyString string1;
		REQUIRE(AreStringsEqual(string1, "\0", 0));
	}

	// может создать свой экземпляр из не пустой строки
	SECTION("can create its own instance from non-empty string")
	{
		CMyString string("a");
		REQUIRE(AreStringsEqual(string, "a", 1));
		CMyString string1("testString");
		REQUIRE(AreStringsEqual(string1, "testString", 10));
	}

	// может создать свой экземпляр из пустой строки и ее длины
	SECTION("can create its own instance from empty string and its length")
	{
		CMyString string("", 0);
		REQUIRE(AreStringsEqual(string, "", 0));
		CMyString string1("\0", 0);
		REQUIRE(AreStringsEqual(string1, "\0", 0));
	}

	// может создать свой экземпляр из не пустой строки и ее длины
	SECTION("can create its own instance of non-empty string and its length")
	{
		CMyString string("a", 1);
		REQUIRE(AreStringsEqual(string, "a", 1));
		CMyString string1("a\0a", 3);
		REQUIRE(AreStringsEqual(string1, "a\0a", 3));
		CMyString string2("\0aa", 3);
		REQUIRE(AreStringsEqual(string2, "\0aa", 3));
	}

	// может создать свой экземпляр из строки библиотеки STL
	SECTION("can create its own instance from string of STL library")
	{
		std::string str("");
		CMyString string(str);
		REQUIRE(AreStringsEqual(string, str.c_str(), str.length()));
		str = "abc";
		CMyString string1(str);
		REQUIRE(AreStringsEqual(string1, str.c_str(), str.length()));
	}

	// может создать свой экземпляр из другого экземпляра CMyString используя конструктор копирования
	SECTION("can create its own instance from another CMyString instance using copy constructor")
	{
		CMyString string("test");
		CMyString string1(string);
		REQUIRE(AreStringsEqual(string1, string.GetStringData(), string.GetLength()));
	}

	// может создать свой экземпляр из другого экземпляра CMyString используя конструктор перемещения
	SECTION("can create its own instance from another CMyString instance using move constructor")
	{
		CMyString string("test");
		CMyString string1(std::move(string));
		REQUIRE(AreStringsEqual(string1, "test", 4));
	}
}

// метод получить длину
TEST_CASE("GetLength method")
{
	// может вернуть длину строки
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

// метод получить данные строки
TEST_CASE("GetStringData method")
{
	// может вернуть указатель на массив символов строки
	SECTION("can return pointer to array of string characters")
	{
		CMyString string("test");
		REQUIRE(string.GetStringData()[0] == string[0]);
		REQUIRE(string.GetStringData()[2] == string[2]);
		REQUIRE(string.GetStringData()[4] == '\0');
	}
}

// метод подстрока
TEST_CASE("SubString method")
{
	// может вернуть подстроку заданную начальной позицией и длиной
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

	// возвращает подстроку от начальной позиции копирования до m_length если начальная позиция копирования + длина подстроки > max_size или m_length
	SECTION("cant return substring if initial copy position is < 0 or >= m_length")
	{
		CMyString string("string");
		REQUIRE(string.SubString(0, SIZE_MAX) == "string");
		REQUIRE(string.SubString(3, SIZE_MAX) == "ing");
		REQUIRE(string.SubString(3, 5) == "ing");
	}

	// может вернуть пустую строку если начальная позиция копирования больше длины исходной строки
	SECTION("cant return substring if initial copy position is >= m_length")
	{
		CMyString string("string");
		REQUIRE(string.SubString(7, 3) == "");
		REQUIRE(string.SubString(22, 2) == "");
		REQUIRE(string.SubString(6, 1) == "");
	}
}

// метод очистка
TEST_CASE("Clear method")
{
	// может очистить строку
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

// перегруженный оператор
TEST_CASE_METHOD(CMyStringFixture, "overloaded operator")
{
	// присваивания
	SECTION("=")
	{
		// не меняет данных строки при присваивании самой себе
		SECTION("doesnt change data of string when assigning itself")
		{
			string = string;
			REQUIRE(AreStringsEqual(string, "string", stringLength));
		}

		// меняет данные первой строки на данные второй
		SECTION("changes data of first string to the data of second")
		{
			string = "new str";
			REQUIRE(AreStringsEqual(string, "new str", 7));
			CMyString str2("str");
			string = str2;
			REQUIRE(AreStringsEqual(string, "str", 3));
		}
	}

	// бинарный плюс
	SECTION("+")
	{
		// может возвращать результат сложения двух экземпляров класса CMyString
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

		// может возвращать результат сложения экземпляра класса CMyString и класса std::string
		SECTION("can return result of adding instance of class CMyString and class std::string")
		{
			std::string string2("string2");
			CMyString str1 = string + string2;
			CMyString str2 = string2 + string;
			REQUIRE(AreStringsEqual(str1, "stringstring2", 13));
			REQUIRE(AreStringsEqual(str2, "string2string", 13));
		}

		// может возвращать результат сложения экземпляра класса CMyString и const char*
		SECTION("can return result of adding instance of class CMyString and const char*")
		{
			CMyString str1 = string + "string2";
			CMyString str2 = "string2" + string;
			REQUIRE(AreStringsEqual(str1, "stringstring2", 13));
			REQUIRE(AreStringsEqual(str2, "string2string", 13));
		}
	}

	// конкатенации с присваиванием
	SECTION("+=")
	{
		// может прибавить к строке1 строку2 класса CMyString
		SECTION("can add to string1 the string2 of the class CMyString")
		{
			CMyString string1("string1");
			string1 += string;
			REQUIRE(AreStringsEqual(string1, "string1string", 13));
		}
	}

	// равенства
	SECTION("==")
	{
		// при сравнении двух строк возвращает истину при их равенстве
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

		// при сравнении двух строк возвращает ложь при их не равенстве
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

	// неравенства
	SECTION("!=")
	{
		// при сравнении двух строк возвращает истину при их не равенстве
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

		// при сравнении двух строк возвращает ложь при их равенстве
		SECTION("when comparing two strings returns false if they are equal")
		{
			CMyString string2("string");
			REQUIRE_FALSE(string != string2);
			REQUIRE(AreStringsEqual(string, string2.GetStringData(), 6));
		}
	}

	// Индексированного доступа к символам строки по целочисленному индексу для чтения
	SECTION("[]")
	{
		// может по индексу считывать символ из строки
		SECTION("can read character from string by index")
		{
			auto ch = string[0];
			REQUIRE(ch == 's');
			ch = string[5];
			REQUIRE(ch == 'g');
			ch = string[2];
			REQUIRE(ch == 'r');
		}

		// не может считывать символ из строки если индекс < 0 или >= длине строки
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

	// Индексированного доступа к символам строки по целочисленному индексу для записи
	SECTION("[]")
	{
		// может по индексу записывать символ в строку
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

		// не может записывать символ в строку если индекс < 0 или >= длине строки
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
		// может вернуть истину если строка 1 меньше строки 2
		SECTION("can return true if string 1 is less than string 2")
		{
			CMyString string2("string1");
			REQUIRE(string < string2);
			string2 = "strink";
			REQUIRE(string < string2);
		}

		// может вернуть ложь если строка 1 не меньше строки 2
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
		// может вернуть истину если строка 1 больше или равна строке 2
		SECTION("can return true if string 1 is greater than or equal to string 2")
		{
			CMyString string2("strin");
			REQUIRE(string >= string2);
			string2 = "strina";
			REQUIRE(string >= string2);
			string2 = "string";
			REQUIRE(string >= string2);
		}

		// может вернуть ложь если строка 1 меньше строки 2
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
		// может вернуть истину если строка 1 больше строки 2
		SECTION("can return true if string 1 is greater than string 2")
		{
			CMyString string2("strin");
			REQUIRE(string > string2);
			string2 = "strina";
			REQUIRE(string > string2);
			string2 = "";
			REQUIRE(string > string2);
		}

		// может вернуть ложь если строка 1 не больше строки 2
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
		// может вернуть истину если строка 1 меньше или равна строке 2
		SECTION("can return true if string 1 is less than or equal to string 2")
		{
			CMyString string2("string1");
			REQUIRE(string <= string2);
			string2 = "strink";
			REQUIRE(string <= string2);
			string2 = "string";
			REQUIRE(string <= string2);
		}

		// может вернуть ложь если строка 1 больше строки 2
		SECTION("can return false if string 1 is greater than string 2")
		{
			CMyString string2("strin");
			REQUIRE_FALSE(string <= string2);
			string2 = "strina";
			REQUIRE_FALSE(string <= string2);
		}
	}

	// считывания из потока
	SECTION(">>")
	{
		// может считывать строку из потока
		SECTION("can read string from the stream")
		{
			std::stringstream strm("string");
			CMyString str;
			strm >> str;
			REQUIRE(AreStringsEqual(str, "string", 6));
		}
	}

	// записи в поток
	SECTION("<<")
	{
		// может записать строку в поток
		SECTION("can write string into stream")
		{
			std::stringstream strm;
			strm << string;
			REQUIRE(strm.str() == "string");
		}
	}
}

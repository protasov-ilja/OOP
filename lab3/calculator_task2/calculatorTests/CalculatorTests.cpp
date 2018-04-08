#include "stdafx.h"
#include "..\CCalculator.h"

using namespace std;

struct CalculatorFixture
{
	CCalculator calculator;
};

bool CheckNAN(double x, double y)
{
	return x == y;
}

//Калькулятор
BOOST_FIXTURE_TEST_SUITE(Calculator, CalculatorFixture)
// может принять неинициализированную переменную
BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
{
	BOOST_CHECK(calculator.SetUndeclaratedVariable("x"));
}

// не может принять переменную с уже существующим именем
BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
{
	BOOST_CHECK(calculator.SetUndeclaratedVariable("x"));
	BOOST_CHECK(!calculator.SetUndeclaratedVariable("x"));
}

// возвращает nan у не инициализированной переменной
BOOST_AUTO_TEST_CASE(displays_variale)
{
	BOOST_CHECK(calculator.SetUndeclaratedVariable("x"));
	BOOST_CHECK(CheckNAN(calculator.GetValue("x"), 1));
}

// возвращает значение переменнгой если оно есть иначе выводит nan
//BOOST_AUTO_TEST_CASE(displays_variale)
//{
//	BOOST_CHECK(calculator.SetUndeclaratedVariable("x"));
//	BOOST_CHECK_EQUAL(calculator.GetVariable("x"));
//	BOOST_CHECK(calculator.SetDeclaratedVariable("x", 1.2));
//}


// Может принять переменную с заданым значением
BOOST_AUTO_TEST_CASE(can_be_turned_on)
{
	BOOST_CHECK(calculator.SetDeclaratedVariable("x", 1.2));
}

// может принять переменную с уже существующим именем и задать ей значение
BOOST_AUTO_TEST_CASE(displays_cahnnel_0_by_default)
{
	BOOST_CHECK(calculator.SetUndeclaratedVariable("x"));
	BOOST_CHECK(calculator.SetDeclaratedVariable("x", 1.2));
}

// не может принять переменную с другой неинициализированной переменной
BOOST_AUTO_TEST_CASE(cant_select_previous_channel_when_turned_off)
{
	
}

BOOST_AUTO_TEST_SUITE_END()

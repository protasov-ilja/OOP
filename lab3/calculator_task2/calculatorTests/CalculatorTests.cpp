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

//�����������
BOOST_FIXTURE_TEST_SUITE(Calculator, CalculatorFixture)
// ����� ������� �������������������� ����������
BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
{
	BOOST_CHECK(calculator.SetUndeclaratedVariable("x"));
}

// �� ����� ������� ���������� � ��� ������������ ������
BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
{
	BOOST_CHECK(calculator.SetUndeclaratedVariable("x"));
	BOOST_CHECK(!calculator.SetUndeclaratedVariable("x"));
}

// ���������� nan � �� ������������������ ����������
BOOST_AUTO_TEST_CASE(displays_variale)
{
	BOOST_CHECK(calculator.SetUndeclaratedVariable("x"));
	//BOOST_CHECK(std::isnan(calculator.GetValue("x")));
	//bool inte = std::isnan(calculator.GetValue("x"));
	double x = calculator.GetValue("x");
	//BOOST_CHECK(calculator.GetValue("x") != calculator.GetValue("x"));
}

// ���������� �������� ����������� ���� ��� ���� ����� ������� nan
//BOOST_AUTO_TEST_CASE(displays_variale)
//{
//	BOOST_CHECK(calculator.SetUndeclaratedVariable("x"));
//	BOOST_CHECK_EQUAL(calculator.GetVariable("x"));
//	BOOST_CHECK(calculator.SetDeclaratedVariable("x", 1.2));
//}


// ����� ������� ���������� � ������� ���������
BOOST_AUTO_TEST_CASE(can_be_turned_on)
{
	BOOST_CHECK(calculator.SetDeclaratedVariable("x", 1.2));
}

// ����� ������� ���������� � ��� ������������ ������ � ������ �� ��������
BOOST_AUTO_TEST_CASE(displays_cahnnel_0_by_default)
{
	BOOST_CHECK(calculator.SetUndeclaratedVariable("x"));
	BOOST_CHECK(calculator.SetDeclaratedVariable("x", 1.2));
}

// �� ����� ������� ���������� � ������ �������������������� ����������
BOOST_AUTO_TEST_CASE(cant_select_previous_channel_when_turned_off)
{
	
}

BOOST_AUTO_TEST_SUITE_END()

#include "stdafx.h"
#include "..\CTVSet.h"

using namespace std;

struct TVSetFixture
{
	CTVSet tv;
};

bool StringsAreEqual(const std::string& infoString, const std::string& expectedString)
{
	return infoString == expectedString;
}

//���������
BOOST_FIXTURE_TEST_SUITE(TVSet, TVSetFixture)
	// ���������� ��������
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!tv.IsTurnedOn());
	}

	// �� ����� ����������� ����� � ����������� ���������
	BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
	{
		BOOST_CHECK(!tv.IsTurnedOn());
		BOOST_CHECK(!tv.SelectChannel(87));
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}

	// ����� ���� �������
	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		tv.TurnOn();
		BOOST_CHECK(tv.IsTurnedOn());
	}

	// ���������� ���������� 0 �����
	BOOST_AUTO_TEST_CASE(displays_cahnnel_0_by_default)
	{
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}

	// �� ����� ����������� �� ���������� ����� � ����������� ���������
	BOOST_AUTO_TEST_CASE(cant_select_previous_channel_when_turned_off)
	{
		BOOST_CHECK(!tv.IsTurnedOn());
		BOOST_CHECK(!tv.SelectPreviousChannel());
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}

	struct when_turned_on_ : TVSetFixture
	{
		when_turned_on_()
		{
			tv.TurnOn();
		}
	};

	// ����� ���������
	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
		// ���������� ����� 1
		BOOST_AUTO_TEST_CASE(displays_channel_one)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
		}

		// �� ����� ����������� ����� �� ���������� ����� ��� ������ ���������
		BOOST_AUTO_TEST_CASE(cant_select_previous_channel_when_when_it_is_first_turned_on)
		{
			BOOST_CHECK(tv.SelectPreviousChannel());
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
		}

		// ����� ���������
		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			tv.TurnOff();
			BOOST_CHECK(!tv.IsTurnedOn());
		}

		// ��������� ������� ����� �� 1 �� 99
		BOOST_AUTO_TEST_CASE(can_select_channel_from_1_to_99)
		{
			BOOST_CHECK(tv.SelectChannel(1));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);

			BOOST_CHECK(tv.SelectChannel(99));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 99);

			// �������� ����� ����� 1 � 99
			BOOST_CHECK(tv.SelectChannel(45));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 45);

			// ��� ������� ������� ����� �� ��������� [1; 99]
			// ��������� �� ������ ������ ���� �����
			BOOST_CHECK(!tv.SelectChannel(100));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 45);

			BOOST_CHECK(!tv.SelectChannel(0));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 45);
		}

		// ��������� ������� ���������� �����
		BOOST_AUTO_TEST_CASE(can_select_previous_channel)
		{
			BOOST_CHECK(tv.SelectChannel(45));
			BOOST_CHECK(tv.SelectPreviousChannel());
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_subsequent_turning_on_ : when_turned_on_
	{
		after_subsequent_turning_on_()
		{
			tv.SelectChannel(5);
			tv.TurnOff();
			tv.TurnOn();
		}
	};

	// ����� ���������� ���������
	BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on, after_subsequent_turning_on_)
		// ���������������� ��������� ��������� �����
		BOOST_AUTO_TEST_CASE(restore_last_selected_channel)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 5);
		}

		// ��������� ������� ���������� �����
		BOOST_AUTO_TEST_CASE(can_select_previous_channel)
		{
			BOOST_CHECK(tv.SelectChannel(45));
			BOOST_CHECK(tv.SelectPreviousChannel());
			BOOST_CHECK_EQUAL(tv.GetChannel(), 5);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#include "stdafx.h"
#include "..\CTVSet.h"

using namespace std;

struct TVSetFixture
{
	CTVSet tv;
};
//Телевизор
BOOST_FIXTURE_TEST_SUITE(TVSet, TVSetFixture)
	// изначально выключен
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!tv.IsTurnedOn());
	}
	// не может переключать канал в выключенном состоянии
	BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
	{
		BOOST_CHECK(!tv.IsTurnedOn());
		BOOST_CHECK(!tv.SelectChannel(87));
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}

	// может быть включен
	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		tv.TurnOn();
		BOOST_CHECK(tv.IsTurnedOn());
	}
BOOST_AUTO_TEST_SUITE_END()

//BOOST_AUTO_TEST_SUITE(AddTranslationInDictionary_function)
//
//BOOST_AUTO_TEST_CASE(send_not_empty_word_and_its_translation_and_add_them_in_map)
//{
//	BOOST_CHECK();
//}

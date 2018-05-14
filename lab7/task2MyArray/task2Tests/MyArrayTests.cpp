#include "stdafx.h"
#include "..\MyArray.h"

using namespace std;






BOOST_AUTO_TEST_SUITE(ParseURL_function)
	BOOST_AUTO_TEST_CASE(takes_url_without_document_and_returns_true)
	{
		BOOST_CHECK("http://www.mysite.com", 80, "", "www.mysite.com", true);
	}
BOOST_AUTO_TEST_SUITE_END()

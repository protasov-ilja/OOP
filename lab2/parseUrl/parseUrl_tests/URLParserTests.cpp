#include "stdafx.h"
#include "..\URLParser.h"

using namespace std;

void CheckUrlParsing(const std::string& url, int expectedPort, const std::string& expectedDoc, const std::string& expecteddHost, bool expectedResult)
{
	Protocol protocol;
	int port = 0;
	string host = "";
	string document = "";
	BOOST_CHECK(expectedResult == ParseURL(url, protocol, port, host, document));
	BOOST_CHECK_EQUAL(port, expectedPort);
	BOOST_CHECK_EQUAL(document, expectedDoc);
	BOOST_CHECK_EQUAL(host, expecteddHost);
}

BOOST_AUTO_TEST_SUITE(ParseURL_function)
	// берет пустую строку и возвращает false
	BOOST_AUTO_TEST_CASE(takes_empty_string_and_returns_false)
	{
		CheckUrlParsing("", 0, "", "", false);
	}

	// берет неверный url и возвращает false
	BOOST_AUTO_TEST_CASE(takes_invalid_url_and_returns_false)
	{
		CheckUrlParsing("http:/www.mysite.com/docs", 0, "", "", false);
		CheckUrlParsing("https//www.mysite.com/docs", 0, "", "", false);
		CheckUrlParsing("ftpwww.mysite.com/docs", 0, "", "", false);
	}

	// берет url без протокола или с неверным протоколом и возвращает false
	BOOST_AUTO_TEST_CASE(takes_url_without_protocol_or_with_invalid_protocol_and_returns_false)
	{
		CheckUrlParsing("://www.mysite.com/docs", 0, "", "", false);
		CheckUrlParsing("httpss://www.mysite.com/docs", 0, "", "", false);
		CheckUrlParsing("ftps://www.mysite.com/docs", 0, "", "", false);
	}

	// берет url без хоста или с неверным хостом и возвращает false
	BOOST_AUTO_TEST_CASE(takes_url_without_host_or_with_invalid_host_and_returns_false)
	{
		CheckUrlParsing("http://www__mysite_com/docs", 0, "", "", false);
		CheckUrlParsing("https://www.?%$mysite.com/docs", 0, "", "", false);
		CheckUrlParsing("ftp:///docs/document1.html", 0, "", "", false);
	}

	// берет корректный url, парсит его и возвращает true
	BOOST_AUTO_TEST_CASE(takes_correct_url_parses_it_and_returns_true)
	{
		CheckUrlParsing("Http://www.mysite.com:123/docs", 123, "docs", "www.mysite.com", true);
		CheckUrlParsing("hTTps://www.mysite.com:1/docs", 1, "docs", "www.mysite.com", true);
		CheckUrlParsing("FTP://www.mysite.com:65535/docs", 65535, "docs", "www.mysite.com", true);
	}

	// берет url без явного указания порта и возвращает true
	BOOST_AUTO_TEST_CASE(takes_url_without_explicitly_specifying_port_and_returns_true)
	{
		CheckUrlParsing("FTP://www.mysite.com/docs", 21, "docs", "www.mysite.com", true);
		CheckUrlParsing("HttPs://www.mysite.com/docs", 443, "docs", "www.mysite.com", true);
		CheckUrlParsing("http://www.mysite.com/docs", 80, "docs", "www.mysite.com", true);
	}

	// берет url без документа и возвращает true
	BOOST_AUTO_TEST_CASE(takes_url_without_document_and_returns_true)
	{
		CheckUrlParsing("http://www.mysite.com", 80, "", "www.mysite.com", true);
	}
BOOST_AUTO_TEST_SUITE_END()

bool AreProtocolsEquals(const Protocol& x, const Protocol& y)
{
	return x == y;
}

BOOST_AUTO_TEST_SUITE(CheckProtocol_function)
	// берет строку протокола и возвращает его тип
	BOOST_AUTO_TEST_CASE(takes_protocol_string_and_returns_its_type)
	{
		BOOST_CHECK(CheckProtocol("http") == Protocol::HTTP);
		BOOST_CHECK(CheckProtocol("https") == Protocol::HTTPS);
		BOOST_CHECK(CheckProtocol("ftp") == Protocol::FTP);
		BOOST_CHECK(CheckProtocol("invalid") == Protocol::NotValid);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CheckPortNumber_function)
	// берет строку цифр и возвращает true, если может представить ее ввиде числа в диапазоне от 1 до 655456
	BOOST_AUTO_TEST_CASE(takes_string_of_digits_and_returns_true_if_can_represent_it_as_number_in_range_from_1_to_65535)
	{
		int portNumber;
		BOOST_CHECK(CheckPortNumber("1", portNumber));
		BOOST_CHECK_EQUAL(portNumber, 1);
		BOOST_CHECK(CheckPortNumber("65535", portNumber));
		BOOST_CHECK_EQUAL(portNumber, 65535);
		BOOST_CHECK(CheckPortNumber("1234", portNumber));
		BOOST_CHECK_EQUAL(portNumber, 1234);

		// неверные входные данные
		BOOST_CHECK(!CheckPortNumber("123213213121", portNumber));
		BOOST_CHECK(!CheckPortNumber("65536", portNumber));
		BOOST_CHECK(!CheckPortNumber("0", portNumber));
		BOOST_CHECK(!CheckPortNumber("sdsd", portNumber));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CheckPort_function)
	// берет строку цифр и возвращает true если она в диапазоне от 1 до 65535 или пустая
	BOOST_AUTO_TEST_CASE(takes_string_of_digits_and_returns_true_if_it_is_in_range_from_1_to_65535_or_empty)
	{
		int port;
		BOOST_CHECK(CheckPort(port, "123", Protocol::HTTP));
		BOOST_CHECK_EQUAL(port, 123);
		BOOST_CHECK(CheckPort(port, "", Protocol::HTTP));
		BOOST_CHECK_EQUAL(port, 80);
	}
BOOST_AUTO_TEST_SUITE_END()

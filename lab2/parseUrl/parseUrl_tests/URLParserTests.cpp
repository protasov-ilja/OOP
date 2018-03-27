#include "stdafx.h"
#include "..\URLParser.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ParseURL_function)
	// берет пустую строку и возвращает false
	BOOST_AUTO_TEST_CASE(takes_empty_string_and_returns_false)
	{
		Protocol protocol;
		int port;
		string host;
		string document;
		BOOST_CHECK(!ParseURL("", protocol, port, host, document));
	}

	// берет url без протокола или с неверным протоколом и возвращает false
	BOOST_AUTO_TEST_CASE(takes_url_without_protocol_or_with_invalid_protocol_and_returns_false)
	{
		Protocol protocol;
		int port;
		string host;
		string document;
		BOOST_CHECK(!ParseURL("://www.mysite.com/docs", protocol, port, host, document));
		BOOST_CHECK(!ParseURL("httpss://www.mysite.com/docs", protocol, port, host, document));
		BOOST_CHECK(!ParseURL("ftps://www.mysite.com/docs", protocol, port, host, document));
	}

	// берет url без хоста или с неверным хостом и возвращает false
	BOOST_AUTO_TEST_CASE(takes_url_without_host_or_with_invalid_host_and_returns_false)
	{
		Protocol protocol;
		int port;
		string host;
		string document;
		BOOST_CHECK(!ParseURL("http://www__mysite_com/docs", protocol, port, host, document));
		BOOST_CHECK(!ParseURL("https://www.?%$mysite.com/docs", protocol, port, host, document));
		BOOST_CHECK(!ParseURL("ftp:///docs/document1.html", protocol, port, host, document));
	}

	// берет корректный url, парсит его и возвращает true
	BOOST_AUTO_TEST_CASE(takes_correct_url_parses_it_and_returns_true)
	{
		Protocol protocol;
		int port;
		string host;
		string document;
		BOOST_CHECK(ParseURL("Http://www.mysite.com:123/docs", protocol, port, host, document));
		BOOST_CHECK_EQUAL(port, 123);
		BOOST_CHECK_EQUAL(document, "docs");
		BOOST_CHECK_EQUAL(host, "www.mysite.com");
		BOOST_CHECK(ParseURL("hTTps://www.mysite.com:1/docs", protocol, port, host, document));
		BOOST_CHECK_EQUAL(port, 1);
		BOOST_CHECK_EQUAL(document, "docs");
		BOOST_CHECK_EQUAL(host, "www.mysite.com");
		BOOST_CHECK(ParseURL("FTP://www.mysite.com:65535/docs", protocol, port, host, document));
		BOOST_CHECK_EQUAL(port, 65535);
		BOOST_CHECK_EQUAL(document, "docs");
		BOOST_CHECK_EQUAL(host, "www.mysite.com");
	}

	// берет url без явного указания порта и возвращает true
	BOOST_AUTO_TEST_CASE(takes_url_without_explicitly_specifying_port_and_returns_true)
	{
		Protocol protocol;
		int port;
		string host;
		string document;
		BOOST_CHECK(ParseURL("FTP://www.mysite.com/docs", protocol, port, host, document));
		BOOST_CHECK_EQUAL(port, 21);
		BOOST_CHECK(ParseURL("HttPs://www.mysite.com/docs", protocol, port, host, document));
		BOOST_CHECK_EQUAL(port, 443);
		BOOST_CHECK(ParseURL("http://www.mysite.com/docs", protocol, port, host, document));
		BOOST_CHECK_EQUAL(port, 80);
	}

	// берет url без документа и возвращает true
	BOOST_AUTO_TEST_CASE(takes_url_without_document_and_returns_true)
	{
		Protocol protocol;
		int port;
		string host;
		string document;
		BOOST_CHECK(ParseURL("http://www.mysite.com", protocol, port, host, document));
		BOOST_CHECK_EQUAL(document, "");
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
		BOOST_CHECK(AreProtocolsEquals(CheckProtocol("http"), Protocol::HTTP));
		BOOST_CHECK(AreProtocolsEquals(CheckProtocol("https"), Protocol::HTTPS));
		BOOST_CHECK(AreProtocolsEquals(CheckProtocol("ftp"), Protocol::FTP));
		BOOST_CHECK(AreProtocolsEquals(CheckProtocol("invalid"), Protocol::NotValid));
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

#include "stdafx.h"
#include "..\CHttpUrl.h"
#include "..\CUrlParsingError.h"

using namespace std;

void CheckUrlParsingFromString(const std::string& url, const std::string& expectedDomain, Protocol expectedProtocol, unsigned short expectedPort, const std::string& expectedDoc)
{
	CHttpUrl urlParser(url);
	BOOST_REQUIRE_NO_THROW(CHttpUrl urlParser(url));
	BOOST_CHECK(urlParser.GetProtocol() == expectedProtocol);
	BOOST_CHECK_EQUAL(urlParser.GetDomain(), expectedDomain);
	BOOST_CHECK_EQUAL(urlParser.GetPort(), expectedPort);
	BOOST_CHECK_EQUAL(urlParser.GetDocument(), expectedDoc);
	BOOST_CHECK_EQUAL(urlParser.GetURL(), url);
}

void CheckUrlParsingWithoutPort(const std::string& url, const std::string& expectedDomain, const std::string& expectedDoc, Protocol expectedProtocol)
{
	CHttpUrl urlParser(expectedDomain, expectedDoc, expectedProtocol);
	BOOST_REQUIRE_NO_THROW(CHttpUrl urlParser(expectedDomain, expectedDoc, expectedProtocol));
	BOOST_CHECK(urlParser.GetProtocol() == expectedProtocol);
	BOOST_CHECK_EQUAL(urlParser.GetDomain(), expectedDomain);
	BOOST_CHECK_EQUAL(urlParser.GetPort(), static_cast<unsigned short>(expectedProtocol));
	std::string doc = (expectedDoc == "") ? "/" + expectedDoc : expectedDoc;
	BOOST_CHECK_EQUAL(urlParser.GetDocument(), doc);
	BOOST_CHECK_EQUAL(urlParser.GetURL(), url);
}

void CheckUrlParsingWithPort(const std::string& url, const std::string& expectedDomain, const std::string& expectedDoc, Protocol expectedProtocol, unsigned short expectedPort)
{
	CHttpUrl urlParser(expectedDomain, expectedDoc, expectedProtocol, expectedPort);
	BOOST_REQUIRE_NO_THROW(CHttpUrl urlParser(expectedDomain, expectedDoc, expectedProtocol, expectedPort));
	BOOST_CHECK(urlParser.GetProtocol() == expectedProtocol);
	BOOST_CHECK_EQUAL(urlParser.GetDomain(), expectedDomain);
	BOOST_CHECK_EQUAL(urlParser.GetPort(), expectedPort);
	std::string doc = (expectedDoc == "") ? "/" + expectedDoc : expectedDoc;
	BOOST_CHECK_EQUAL(urlParser.GetDocument(), doc);
	BOOST_CHECK_EQUAL(urlParser.GetURL(), url);
}

// HttpUrl
BOOST_AUTO_TEST_SUITE(httpUrl_class)
	// если на входе строка
	BOOST_AUTO_TEST_SUITE(in_string)
		// не может быть создан и выбрасывает исключение
		BOOST_AUTO_TEST_SUITE(cant_be_created)
			// если url пуст
			BOOST_AUTO_TEST_CASE(takes_empty_string_and_returns_false)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser(""), CUrlParsingError);
			}

			// если структура url-а нарушена
			BOOST_AUTO_TEST_CASE(invalid_url)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http:/www.mysite.com:65531/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:1docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http//www.mysite.com:1/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Httpwww.mysite.com:1/docs"), CUrlParsingError);
			}

			// если протокол не равен http или https
			BOOST_AUTO_TEST_CASE(invalid_protocol1)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("://www.mysite.com/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("httpss://www.mysite.com/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("ftpwww.mysite.com/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("hhttp://www.mysite.com/docs"), CUrlParsingError);
			}

			// если домен пуст или содержит недопустимые символы
			BOOST_AUTO_TEST_CASE(invalid_domain1)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("http://www__mysite_com/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("https://www.?%$mysite.com/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("http:///docs/document1.html"), CUrlParsingError);
			}

			// если порт не является числом
			BOOST_AUTO_TEST_CASE(invalid_port1)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:d65535/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:fff/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:12f/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:1f2/docs"), CUrlParsingError);
			}

			// если порт не принадлежит диапазаону от 1 до 65535
			BOOST_AUTO_TEST_CASE(invalid_port2)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:65536/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:0/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:-1/docs"), CUrlParsingError);
			}
		BOOST_AUTO_TEST_SUITE_END()

		// может быть создан
		BOOST_AUTO_TEST_SUITE(can_be_created)
			// если url коректен и содержит порт и документ
			BOOST_AUTO_TEST_CASE(correct_url)
			{
				CheckUrlParsingFromString("Http://www.mysite.com:23/docs", "www.mysite.com", Protocol::HTTP, 23, "/docs");
				CheckUrlParsingFromString("Http://www.mysite.com:1/docs", "www.mysite.com", Protocol::HTTP, 1, "/docs");
				CheckUrlParsingFromString("Http://www.mysite.com:65535/docs", "www.mysite.com", Protocol::HTTP, 65535, "/docs");
			}

			// если url коректен и не содержит документ
			BOOST_AUTO_TEST_CASE(correct_url2)
			{
				CheckUrlParsingFromString("Http://www.mysite.com:23/", "www.mysite.com", Protocol::HTTP, 23, "/");
				CheckUrlParsingFromString("Https://www.mysite.com:23", "www.mysite.com", Protocol::HTTPS, 23, "/");
				CheckUrlParsingFromString("Http://www.mysite.com:1", "www.mysite.com", Protocol::HTTP, 1, "/");
				CheckUrlParsingFromString("Http://www.mysite.com:65535", "www.mysite.com", Protocol::HTTP, 65535, "/");
			}

			// если url коректен и не содержит порта
			BOOST_AUTO_TEST_CASE(correct_url3)
			{
				CheckUrlParsingFromString("Http://www.mysite.com", "www.mysite.com", Protocol::HTTP, 80, "/");
				CheckUrlParsingFromString("Https://www.mysite.com/docs", "www.mysite.com", Protocol::HTTPS, 443, "/docs");
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	// если на входе domain, document и protocol
	BOOST_AUTO_TEST_SUITE(in_args)
		// не может быть создан и выбрасывает исключение
		BOOST_AUTO_TEST_SUITE(cant_be_created)
			// если домен пуст или содержит недопустимые символы
			BOOST_AUTO_TEST_CASE(invalid_domain1)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("", "/", Protocol::HTTP), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("sd$#@", "/docs", Protocol::HTTPS), CUrlParsingError);
			}
		BOOST_AUTO_TEST_SUITE_END()

		// может быть создан
		BOOST_AUTO_TEST_SUITE(can_be_created)
			// если url коректен содержит не пустой документ
			BOOST_AUTO_TEST_CASE(correct_url)
			{
				CheckUrlParsingWithoutPort("http://www.mysite.com/docs", "www.mysite.com", "/docs", Protocol::HTTP);
				CheckUrlParsingWithoutPort("https://www.mysite.com/docs", "www.mysite.com", "/docs", Protocol::HTTPS);
				CheckUrlParsingWithoutPort("https://www.mysite.com/", "www.mysite.com", "/", Protocol::HTTPS);
			}

			// если url коректен и содержит пустой документ
			BOOST_AUTO_TEST_CASE(correct_url2)
			{
				CheckUrlParsingWithoutPort("http://www.mysite.com/", "www.mysite.com", "", Protocol::HTTP);
				CheckUrlParsingWithoutPort("https://www.mysite.com/", "www.mysite.com", "", Protocol::HTTPS);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	// если на входе domain, document, protocol и port
	BOOST_AUTO_TEST_SUITE(in_args1)
		// не может быть создан и выбрасывает исключение
		BOOST_AUTO_TEST_SUITE(cant_be_created)
			// если домен пуст или содержит недопустимые символы
			BOOST_AUTO_TEST_CASE(invalid_domain1)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("", "/", Protocol::HTTP), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("sd$#@", "/docs", Protocol::HTTPS), CUrlParsingError);
			}

			// если порт не принадлежит диапазаону от 1 до 65535
			BOOST_AUTO_TEST_CASE(invalid_port2)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("www.mysite.com", "/docs", Protocol::HTTP, 65536), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("www.mysite.com", "/docs", Protocol::HTTPS, 0), CUrlParsingError);
			}
		BOOST_AUTO_TEST_SUITE_END()

		// может быть создан
		BOOST_AUTO_TEST_SUITE(can_be_created)
			// если url коректен содержит не пустой документ
			BOOST_AUTO_TEST_CASE(correct_url)
			{
				CheckUrlParsingWithPort("http://www.mysite.com:32/docs", "www.mysite.com", "/docs", Protocol::HTTP, 32);
				CheckUrlParsingWithPort("https://www.mysite.com:32/docs", "www.mysite.com", "/docs", Protocol::HTTPS, 32);
				CheckUrlParsingWithPort("https://www.mysite.com:32/", "www.mysite.com", "/", Protocol::HTTPS, 32);
			}

			// если url коректен и содержит пустой документ
			BOOST_AUTO_TEST_CASE(correct_url2)
			{
				CheckUrlParsingWithPort("http://www.mysite.com:32/", "www.mysite.com", "", Protocol::HTTP, 32);
				CheckUrlParsingWithPort("https://www.mysite.com:32/", "www.mysite.com", "", Protocol::HTTPS, 32);
			}

			// если порт принадлежит диапазаону от 1 до 65535
			BOOST_AUTO_TEST_CASE(correct_url3)
			{
				CheckUrlParsingWithPort("http://www.mysite.com:23/docs", "www.mysite.com", "/docs", Protocol::HTTP, 23);
				CheckUrlParsingWithPort("https://www.mysite.com:1/docs", "www.mysite.com", "/docs", Protocol::HTTPS, 1);
				CheckUrlParsingWithPort("https://www.mysite.com:65535/docs", "www.mysite.com", "/docs", Protocol::HTTPS, 65535);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

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
	// ���� �� ������� ��������� ��������� ������
	BOOST_AUTO_TEST_SUITE(if_input_parameter_contains_string)
		// �� ����� ���� ������ � ����������� ����������
		BOOST_AUTO_TEST_SUITE(cant_be_created_and_throws_exception)
			// ���� url ����
			BOOST_AUTO_TEST_CASE(if_url_is_empty)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser(""), CUrlParsingError);
			}

			// ���� ��������� url-� ��������
			BOOST_AUTO_TEST_CASE(if_url_structure_is_violated)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http:/www.mysite.com:65531/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:1docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http//www.mysite.com:1/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Httpwww.mysite.com:1/docs"), CUrlParsingError);
			}

			// ���� �������� �� ����� http ��� https
			BOOST_AUTO_TEST_CASE(if_protocol_isnt_http_or_https)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("://www.mysite.com/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("httpss://www.mysite.com/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("ftpwww.mysite.com/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("hhttp://www.mysite.com/docs"), CUrlParsingError);
			}

			// ���� ����� ���� ��� �������� ������������ �������
			BOOST_AUTO_TEST_CASE(if_domain_is_empty_or_contains_invalid_characters)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("http://www__mysite_com/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("https://www.?%$mysite.com/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("http:///docs/document1.html"), CUrlParsingError);
			}

			// ���� ���� �� �������� ������
			BOOST_AUTO_TEST_CASE(if_port_isnt_number)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:d65535/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:fff/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:12f/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:1f2/docs"), CUrlParsingError);
			}

			// ���� ���� �� � ���������� �� 1 �� 65535
			BOOST_AUTO_TEST_CASE(if_port_isnt_in_range_from_1_to_65535)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:65536/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:0/docs"), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("Http://www.mysite.com:-1/docs"), CUrlParsingError);
			}
		BOOST_AUTO_TEST_SUITE_END()

		// ����� ���� ������
		BOOST_AUTO_TEST_SUITE(can_be_created)
			// ���� url �������� � �������� ���� � ��������
			BOOST_AUTO_TEST_CASE(if_url_is_correct_and_contains_port_and_document)
			{
				CheckUrlParsingFromString("Http://www.mysite.com:23/docs", "www.mysite.com", Protocol::HTTP, 23, "/docs");
				CheckUrlParsingFromString("Http://www.mysite.com:1/docs", "www.mysite.com", Protocol::HTTP, 1, "/docs");
				CheckUrlParsingFromString("Http://www.mysite.com:65535/docs", "www.mysite.com", Protocol::HTTP, 65535, "/docs");
			}

			// ���� url �������� � �� �������� ��������
			BOOST_AUTO_TEST_CASE(if_url_is_correct_and_doesnt_contain_document)
			{
				CheckUrlParsingFromString("Http://www.mysite.com:23/", "www.mysite.com", Protocol::HTTP, 23, "/");
				CheckUrlParsingFromString("Https://www.mysite.com:23", "www.mysite.com", Protocol::HTTPS, 23, "/");
				CheckUrlParsingFromString("Http://www.mysite.com:1", "www.mysite.com", Protocol::HTTP, 1, "/");
				CheckUrlParsingFromString("Http://www.mysite.com:65535", "www.mysite.com", Protocol::HTTP, 65535, "/");
			}

			// ���� url �������� � �� �������� �����
			BOOST_AUTO_TEST_CASE(if_url_is_correct_and_doesnt_contain_port)
			{
				CheckUrlParsingFromString("Http://www.mysite.com", "www.mysite.com", Protocol::HTTP, 80, "/");
				CheckUrlParsingFromString("Https://www.mysite.com/docs", "www.mysite.com", Protocol::HTTPS, 443, "/docs");
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	// ���� �� ������� ��������� ��������� domain, document � protocol
	BOOST_AUTO_TEST_SUITE(if_input_parameter_contains_domain_document_and_protocol)
		// �� ����� ���� ������ � ����������� ����������
		BOOST_AUTO_TEST_SUITE(cant_be_created_and_throws_exception)
			// ���� ����� ���� ��� �������� ������������ �������
			BOOST_AUTO_TEST_CASE(if_domain_is_empty_or_contains_invalid_characters)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("", "/", Protocol::HTTP), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("sd$#@", "/docs", Protocol::HTTPS), CUrlParsingError);
			}
		BOOST_AUTO_TEST_SUITE_END()

		// ����� ���� ������
		BOOST_AUTO_TEST_SUITE(can_be_created)
			// ���� url �������� � �������� �� ������ ��������
			BOOST_AUTO_TEST_CASE(if_url_is_correct_and_contains_not_empty_document)
			{
				CheckUrlParsingWithoutPort("http://www.mysite.com/docs", "www.mysite.com", "/docs", Protocol::HTTP);
				CheckUrlParsingWithoutPort("https://www.mysite.com/docs", "www.mysite.com", "/docs", Protocol::HTTPS);
				CheckUrlParsingWithoutPort("https://www.mysite.com/", "www.mysite.com", "/", Protocol::HTTPS);
			}

			// ���� url �������� � �������� ������ ��������
			BOOST_AUTO_TEST_CASE(if_url_is_correct_and_contains_empty_document)
			{
				CheckUrlParsingWithoutPort("http://www.mysite.com/", "www.mysite.com", "", Protocol::HTTP);
				CheckUrlParsingWithoutPort("https://www.mysite.com/", "www.mysite.com", "", Protocol::HTTPS);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	// ���� �� ������� ��������� ��������� domain, document, protocol � port
	BOOST_AUTO_TEST_SUITE(if_input_parameter_contains_domain_document_protocol_and_port)
		// �� ����� ���� ������ � ����������� ����������
		BOOST_AUTO_TEST_SUITE(cant_be_created_and_throws_exception)
			// ���� ����� ���� ��� �������� ������������ �������
			BOOST_AUTO_TEST_CASE(if_domain_is_empty_or_contains_invalid_characters)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("", "/", Protocol::HTTP), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl urlParser("sd$#@", "/docs", Protocol::HTTPS), CUrlParsingError);
			}

			// ���� ���� �� � ���������� �� 1 �� 65535
			BOOST_AUTO_TEST_CASE(if_port_isnt_in_range_from_1_to_65535)
			{
				BOOST_CHECK_THROW(CHttpUrl urlParser("www.mysite.com", "/docs", Protocol::HTTPS, 0), CUrlParsingError);
			}
		BOOST_AUTO_TEST_SUITE_END()

		// ����� ���� ������
		BOOST_AUTO_TEST_SUITE(can_be_created)
			// ���� url �������� � �������� �� ������ ��������
			BOOST_AUTO_TEST_CASE(if_url_is_correct_and_contains_not_empty_document)
			{
				CheckUrlParsingWithPort("http://www.mysite.com:32/docs", "www.mysite.com", "/docs", Protocol::HTTP, 32);
				CheckUrlParsingWithPort("https://www.mysite.com:32/docs", "www.mysite.com", "/docs", Protocol::HTTPS, 32);
				CheckUrlParsingWithPort("https://www.mysite.com:32/", "www.mysite.com", "/", Protocol::HTTPS, 32);
			}

			// ���� url �������� � �������� ������ ��������
			BOOST_AUTO_TEST_CASE(if_url_is_correct_and_contains_empty_document)
			{
				CheckUrlParsingWithPort("http://www.mysite.com:32/", "www.mysite.com", "", Protocol::HTTP, 32);
				CheckUrlParsingWithPort("https://www.mysite.com:32/", "www.mysite.com", "", Protocol::HTTPS, 32);
			}

			// ���� ���� � ���������� �� 1 �� 65535
			BOOST_AUTO_TEST_CASE(if_port_in_range_from_1_to_65535)
			{
				CheckUrlParsingWithPort("http://www.mysite.com:23/docs", "www.mysite.com", "/docs", Protocol::HTTP, 23);
				CheckUrlParsingWithPort("https://www.mysite.com:1/docs", "www.mysite.com", "/docs", Protocol::HTTPS, 1);
				CheckUrlParsingWithPort("https://www.mysite.com:65535/docs", "www.mysite.com", "/docs", Protocol::HTTPS, 65535);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <algorithm>
#include <regex>

CHttpUrl::CHttpUrl(const std::string& url)
	: m_url(url)
{
	if (url.empty())
	{
		throw CUrlParsingError("Url is empty");
	}

	std::regex regex(R"(^(https?)://([A-Za-z0-9-.]+)(?::([0-9]+))?(?:\/(.*))?$)", std::regex_constants::icase);
	std::smatch result;
	if (!std::regex_match(url, result, regex))
	{
		throw CUrlParsingError("Invalid url");
	}

	m_protocol = ValidateProtocol(result[1]);
	m_domain = ValidateDomain(result[2]);
	m_port = ValidatePort(result[3]);
	m_document = ValidateDocument(result[4]);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol = HTTP)
	: m_protocol(protocol)
	, m_domain(ValidateDomain(domain))
	, m_port(ValidatePort(""))
	, m_document(ValidateDocument(document))
{
	SetUrl();
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_protocol(protocol)
	, m_domain(ValidateDomain(domain))
	, m_document(ValidateDocument(document))
{
	if (port < 1)
	{
		throw CUrlParsingError("Invalid port");
	}

	m_port = port;
	SetUrl();
}

std::string CHttpUrl::ValidateDocument(const std::string& document) const
{
	return (document.empty() || (document[0] != '/')) ? '/' + document : document;
}

std::string CHttpUrl::ValidateDomain(const std::string& domain) const
{
	std::regex regex(R"(^([A-Za-z0-9-.]+)$)", std::regex_constants::icase);
	std::smatch result;
	if (!std::regex_match(domain, result, regex))
	{
		throw CUrlParsingError("Invalid domain");
	}

	return domain;
}

Protocol CHttpUrl::ValidateProtocol(const std::string& protocolString) const
{
	auto ConvertCharTolower = [](char ch) {
		return static_cast<char>(tolower(ch));
	};

	std::string protocolStringInLowerCase;
	std::transform(protocolString.begin(), protocolString.end(), std::back_inserter(protocolStringInLowerCase), ConvertCharTolower);
	if (protocolStringInLowerCase == "http")
	{
		return Protocol::HTTP;
	}

	return Protocol::HTTPS;
}

unsigned short CHttpUrl::GetPortNumber(const std::string& portString) const
{
	try
	{
		int portNumber = std::stoi(portString);
		if ((portNumber < 1) || (portNumber > 65535))
		{
			throw CUrlParsingError("Invalid port: " + portString);
		}

		return static_cast<unsigned short>(portNumber);
	}
	catch (...)
	{
		throw CUrlParsingError("Invalid port: " + portString);
	}
}

unsigned short CHttpUrl::ValidatePort(const std::string& portString) const
{
	if (portString.empty())
	{
		return static_cast<unsigned short>(m_protocol);
	}

	return GetPortNumber(portString);
}

void CHttpUrl::SetUrl()
{
	std::string portString = (static_cast<unsigned short>(m_protocol) == m_port) ? "" : ":" + std::to_string(m_port);
	m_url = GetStringFromProtocol() + "://" + m_domain + portString + m_document;
}

std::string CHttpUrl::GetStringFromProtocol() const
{
	if (m_protocol == Protocol::HTTP)
	{
		return "http";
	}
	else
	{
		return "https";
	}
}

std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

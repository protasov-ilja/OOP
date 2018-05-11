#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <regex>
#include <algorithm>

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

	m_protocol = SetProtocol(result[1]);
	m_domain = SetDomain(result[2]);
	m_port = SetPort(result[3]);
	m_document = SetDocument(result[4]);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol = HTTP)
try
	: m_protocol(protocol)
	, m_domain(SetDomain(domain))
	, m_port(SetPort(""))
	, m_document(SetDocument(document))
{
	SetUrl();
}
catch (const CUrlParsingError& err)
{
	throw err;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
try
	: m_protocol(protocol)
	, m_domain(SetDomain(domain))
	, m_document(SetDocument(document))
{
	if ((port < 1) || (port > 65535))
	{
		throw CUrlParsingError("Invalid port");
	}

	m_port = port;
	SetUrl();
}
catch (const CUrlParsingError& err)
{
	throw err;
}

std::string CHttpUrl::SetDocument(const std::string& document) const
{
	return (document.empty() || (document[0] != '/')) ? '/' + document : document;
}

std::string CHttpUrl::SetDomain(const std::string& domain) const
{
	std::regex regex(R"(^([A-Za-z0-9-.]+)$)", std::regex_constants::icase);
	std::smatch result;
	if (!std::regex_match(domain, result, regex))
	{
		throw CUrlParsingError("Invalid domain");
	}

	return domain;
}

Protocol CHttpUrl::SetProtocol(const std::string& protocolString) const
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
	else if (protocolStringInLowerCase == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("Invalid protocol");
}

unsigned short CHttpUrl::GetPortNumber(const std::string& portString) const
{
	try
	{
		unsigned short portNumber = std::stoi(portString);
		if ((portNumber < 1) || (portNumber > 65535))
		{
			throw CUrlParsingError("Invalid port");
		}

		return portNumber;
	}
	catch (...)
	{
		throw CUrlParsingError("Invalid port");
	}
}

unsigned short CHttpUrl::SetPort(const std::string& portString) const
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
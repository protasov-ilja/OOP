#pragma once
#include <string>

enum Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CHttpUrl
{
public:
	CHttpUrl(const std::string& url);
	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;
	std::string GetStringFromProtocol() const;

private:
	void SetUrl();
	std::string ValidateDocument(const std::string& document) const;
	std::string ValidateDomain(const std::string& domain) const;
	Protocol ValidateProtocol(const std::string& protocolString) const;
	unsigned short GetPortNumber(const std::string& portString) const;
	unsigned short ValidatePort(const std::string& portString) const;

	std::string m_url;
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
};

#include "stdafx.h"
#include "URLParser.h"

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	if (url.empty())
	{
		return false;
	}

	std::regex regex(R"(^(https?|ftp)://([A-Za-z0-9-.]+)(?::([0-9]+))?(?:\/(.*))?$)", std::regex_constants::icase);
	std::smatch result;
	if (!std::regex_match(url, result, regex))
	{
		return false;
	}

	protocol = CheckProtocol(result[1]);
	host = result[2];
	if (host.empty() && (protocol == Protocol::NotValid))
	{
		return false;
	}

	if (!CheckPort(port, result[3], protocol))
	{
		return false;
	}

	document = result[4];

	return true;
}

Protocol CheckProtocol(const std::string& protocolString)
{
	std::string protocolStringInLowerCase;
	std::transform(protocolString.begin(), protocolString.end(), std::back_inserter(protocolStringInLowerCase), tolower);
	if (protocolStringInLowerCase == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocolStringInLowerCase == "https")
	{
		return Protocol::HTTPS;
	}
	else if (protocolStringInLowerCase == "ftp")
	{
		return Protocol::FTP;
	}

	return Protocol::NotValid;
}

bool CheckPortNumber(const std::string& portString, int& portNumber)
{
	try
	{
		portNumber = std::stoi(portString);
		if ((portNumber < 1) || (portNumber > 65535))
		{
			std::cout << "Argument " << portString << " is less then 1 or more than 65535\n";
			return false;
		}
	}
	catch (const std::invalid_argument& isError)
	{
		std::cout << isError.what() << "\n";
		return false;
	}
	catch (const std::out_of_range& isError)
	{
		std::cout << isError.what() << "\n";
		return false;
	}

	return true;
}

bool CheckPort(int& port, const std::string& portString, const Protocol& protocol)
{
	if (portString.empty())
	{
		port = static_cast<int>(protocol);
		return true;
	}

	return CheckPortNumber(portString, port) ? true : false;
}

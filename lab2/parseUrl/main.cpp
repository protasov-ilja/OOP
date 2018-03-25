// parseUrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "URLParser.h"

void ProcessStringFromInputStream();
void WriteResultOfParsing(std::string const& host, int port, std::string const& document);

int main()
{
	ProcessStringFromInputStream();

	return 0;
}

void WriteResultOfParsing(std::string const& host, int port, std::string const& document)
{
	std::cout << "\nHOST: " << host << "\nPORT: " << port << "\nDOC: " << document << std::endl;
}

void ProcessStringFromInputStream()
{
	std::string inputURL;
	while (getline(std::cin, inputURL))
	{
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		if (ParseURL(inputURL, protocol, port, host, document))
		{
			WriteResultOfParsing(host, port, document);
		}
		else
		{
			std::cout << "The url is not valid" << std::endl;
		}
	}
}

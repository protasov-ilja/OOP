// parseUrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};


bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);

int main()
{

	return 0;
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	return true;
}

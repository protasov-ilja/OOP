#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
	FTP = 21,
	NotValid
};

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);
Protocol CheckProtocol(const std::string& protocolString);
bool CheckPortNumber(const std::string& portString, int& portNumber);
bool CheckPort(int& port, const std::string& portString, const Protocol& protocol);

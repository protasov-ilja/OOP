#pragma once
#include <string>
#include <regex>

class CIdentifier
{
public:
	CIdentifier();
	~CIdentifier();
	bool IsValid(const std::string name);
};


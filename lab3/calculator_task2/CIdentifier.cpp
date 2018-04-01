#include "stdafx.h"
#include "CIdentifier.h"


CIdentifier::CIdentifier()
{
}


CIdentifier::~CIdentifier()
{
}

bool CIdentifier::IsValid(const std::string name)
{
	/*std::regex regex(R"(^([A-Za-z_])([A-Za-z0-9_])?$)");
	std::smatch result;
	if (!std::regex_match(name, result, regex))
	{
		return false;
	}
	
	if (result[1].str().empty()) {
		return false;
	}

	return true;*/
}
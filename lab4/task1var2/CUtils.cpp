#include "stdafx.h"
#include "CUtils.h"

uint32_t CUtils::StringToUint32(std::string str)
{
	uint32_t x;
	std::stringstream ss;
	ss << std::hex << str;
	ss >> x;
	return x;
}

#pragma once
#include "stdafx.h"

namespace Utils
{
inline uint32_t StringToUint32(std::string str)
{
	uint32_t x;
	std::stringstream ss;
	ss << std::hex << str;
	ss >> x;
	return x;
}
} // namespace Utils

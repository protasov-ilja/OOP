#include "stdafx.h"
#include "CCalculator.h"

CCalculator::CCalculator()
{
}

CCalculator::~CCalculator()
{
}

bool CCalculator::SetUndeclaratedVariable(const std::string varName)
{
	if (CCalculator::FindIdentifierName(varName))
	{
		return false;
	}

	m_variableMap.insert(std::pair<std::string, double>(varName, NAN));

	return true;
}

bool CCalculator::SetDeclaratedVariable(const std::string& name, double value)
{
	return true;
}

bool CCalculator::FindIdentifierName(const std::string identifierName)
{
	if (m_variableMap.find(identifierName) != m_variableMap.end())
	{
		return true;
	}

	return false;
}

double GetValue(const std::string& name)
{
	return NAN;
}

	//bool CCalculator::IsValid(const std::string name) // имя хрень
	//{
	//	/*std::regex regex(R"(^([A-Za-z_])([A-Za-z0-9_]+)?)");
	//	std::smatch result;
	//	if (!std::regex_match(name, result, regex))
	//	{
	//		return false;
	//	}
	//
	//	if (result[1].str().empty()) {
	//		return false;
	//	}
	//	*/
	//	return true;
	//}

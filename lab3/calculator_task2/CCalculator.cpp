#include "stdafx.h"
#include "CCalculator.h"
#include <stack>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>

typedef std::pair<std::string, std::vector<std::string>> stackComp;

enum class position
{
	ZERO = 0,
	FIRST = 1,
	SECOND = 2
};

CCalculator::CCalculator()
{
}

CCalculator::~CCalculator()
{
}

bool CCalculator::SetUndeclaratedVariable(const std::string name)
{
	if (FindVariableName(name) || FindFunctionName(name))
	{
		return false;
	}

	m_variableMap.insert(std::pair<std::string, double>(name, std::numeric_limits<double>::quiet_NaN()));

	return true;
}

bool CCalculator::SetDeclaratedVariable(const std::string& name, double value)
{
	if (FindFunctionName(name))
	{
		return false;
	}

	bool variableWasFound = FindVariableName(name);
	if (variableWasFound && (std::isnan(m_variableMap[name])))
	{
			m_variableMap[name] = value;
	}
	else if (variableWasFound)
	{
		return false;
	}

	m_variableMap.insert(std::pair<std::string, double>(name, value));

	return true;
}

bool CCalculator::SetDeclaratedVariable(const std::string& name, const std::string& identifier2)
{
	if (FindFunctionName(name))
	{
		return false;
	}

	bool variableWasFound = FindVariableName(name);
	if (variableWasFound && (std::isnan(m_variableMap[name])))
	{
		// нужна проверка имени второго идентицикатора на существование в map!
		m_variableMap[name] = CalculateIdentifireValue(identifier2);
	}
	else if (variableWasFound)
	{
		return false;
	}

	m_variableMap.insert(std::pair<std::string, double>(name, CalculateIdentifireValue(identifier2)));

	return true;
}

double CCalculator::CalculateIdentifireValue(const std::string name)
{
	std::stack<stackComp> stackOfIdentifiers;
	//stackComp argument(name, 3);
	auto it = m_variableMap.find(name);
	std::vector<std::string> operators;
	boost::split(operators, it->second, boost::is_any_of(" "));
	if (operators.size() == 1)
	{
		operators.push_back("");
		operators.push_back("");
		operators.push_back("fisrt");
	}
	else
	{
		operators.push_back("fisrt");
	}

	stackOfIdentifiers.push({ name, operators });
	std::string id;
	while (!stackOfIdentifiers.empty())
	{
		if (stackOfIdentifiers.top().second[3] == "first")
		{
			id = stackOfIdentifiers.top().second[0];
		}
		else if (stackOfIdentifiers.top().second[3] == "second")
		{
			id = stackOfIdentifiers.top().second[2];
		}
		else
		{
			// pop
			// count result of curid
			id = strtod(stackOfIdentifiers.top().second[2]) ;
		}
	}
	return 1;
}

bool CCalculator::FindVariableName(const std::string identifierName)
{
	if (m_variableMap.find(identifierName) != m_variableMap.end())
	{
		return true;
	}

	return false;
}

bool CCalculator::FindFunctionName(const std::string identifierName)
{
	if (m_functionMap.find(identifierName) != m_functionMap.end())
	{
		return true;
	}

	return false;
}

double CCalculator::GetValue(const std::string& name) const
{
	return m_variableMap[name];
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

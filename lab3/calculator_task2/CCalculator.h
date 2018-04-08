#pragma once
#include <string>
#include <unordered_map>

class CCalculator
{
public:
	CCalculator();
	~CCalculator();
	bool SetUndeclaratedVariable(const std::string varName);
	bool SetDeclaratedVariable(const std::string& name, double value);
	double GetValue(const std::string & name) const;

private:
	//bool IsValid(const std::string name);
	bool FindIdentifierName(const std::string identifierName);
	std::unordered_map<std::string, double> m_variableMap;
};

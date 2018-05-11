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
	bool SetDeclaratedVariable(const std::string& name, const std::string& identifier2);
	double GetValue(const std::string & name) const;

private:
	//bool IsValid(const std::string name);
	double CalculateIdentifireValue(const std::string name);
	bool FindVariableName(const std::string identifierName);
	bool FindFunctionName(const std::string identifierName);
	std::unordered_map<std::string, double> m_variableMap;
	std::unordered_map<std::string, std::string> m_functionMap;
};

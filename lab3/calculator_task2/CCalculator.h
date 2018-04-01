#pragma once
#include <string>

class CCalculator
{
public:
	CCalculator();
	~CCalculator();
	void SetUndeclaratedVariable(const std::string name, const std::string secondArgument);
	void SetDeclaratedVariable(const std::string& name);
private:

};

#pragma once
#include <iostream>
#include <map>
#include <functional>
#include <boost/noncopyable.hpp>
#include <sstream>

class CTVSet;

// ������������ �� boost::noncopyable - ����� ������ ��������� ����������� � ������������ ����������� ������
class CRemoteControl : boost::noncopyable
{
public:
	CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output);
	bool HandleCommand();
	

	// ����������� �� �������������� ����������� � ���, ��� �� �� ������ ������������� �������� ������������
	// CRemoteControl& operator=(const CRemoteControl &) = delete;
private:
	bool SelectChannel(int channel);
	bool SelectPreviousChannel();
	bool GetChannelNumber(const std::string& inputString, int& number);
	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool Info(std::istream& args);

private:
	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;

	CTVSet& m_tv;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};

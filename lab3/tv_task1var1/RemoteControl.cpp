#include "stdafx.h"
#include "RemoteControl.h"
#include "CTVSet.h"
using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "TurnOn", [this](istream& strm) {
			   return TurnOn(strm);
		   } },
		  { "TurnOff", bind(&CRemoteControl::TurnOff, this, _1) }, 
		  { "Info", bind(&CRemoteControl::Info, this, _1) }
		  //, { "SelectPreviousChannel", bind(&CRemoteControl::SelectPreviousChannel, this, _1) }
	  })
{
}

bool CRemoteControl::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	getline(strm, action);

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	else
	{
		if (action.size() > 13)
		{
			std::string newAction;
			newAction.append(action, 0, 13);
			if (newAction == "SelectChannel")
			{
				std::string actionNumberString;
				actionNumberString.append(action, 14, action.size());
				int actionNumber;
				if (GetChannelNumber(actionNumberString, actionNumber))
				{
					return CRemoteControl::SelectChannel(actionNumber);
				}
			}
		}
	}

	return false;
}

bool CRemoteControl::GetChannelNumber(const std::string& stringNumber, int& number)
{
	try
	{
		number = stoi(stringNumber);
	}
	catch (const std::invalid_argument& isError)
	{
		std::cout << isError.what() << "\n";
		return false;
	}
	catch (const std::out_of_range& isError)
	{
		std::cout << isError.what() << "\n";
		return false;
	}
	return true;
}

bool CRemoteControl::TurnOn(std::istream&)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << std::endl;
	return true;
}

bool CRemoteControl::SelectChannel(int channel)
{
	if ((m_tv.IsTurnedOn()) && ((channel < 1) || (channel > 99)))
	{
		m_output << "Invalid channel" << std::endl;
	}
	else if (!m_tv.IsTurnedOn())
	{
		m_output << "Can't select channel because TV is turned off" << std::endl;
	}
	else
	{
		m_tv.SelectChannel(channel);
		m_output << "Channel selected" << std::endl;
	}

	return true;
}

bool CRemoteControl::SelectPreviousChannel()
{
	if (m_tv.IsTurnedOn())
	{
		m_tv.SelectPreviousChannel();
		m_output << "Channel selected" << std::endl;
	}
	else
	{
		m_output << "Can't select channel because TV is turned off" << std::endl;
	}

	return true;
}

bool CRemoteControl::TurnOff(std::istream&)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << std::endl;
	return true;
}

bool CRemoteControl::Info(std::istream&)
{
	std::string info = (m_tv.IsTurnedOn())
		? ("TV is turned on\nChannel is: " + std::to_string(m_tv.GetChannel()) + "\n")
		: "TV is turned off\n";

	m_output << info;

	return true;
}

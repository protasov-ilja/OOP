#include "stdafx.h"
#include "RemoteControl.h"
#include "CTVSet.h"

const std::string COMMAND_TURN_ON = "TurnOn";
const std::string COMMAND_TURN_OFF = "TurnOff";
const std::string COMMAND_INFO = "Info";
const std::string COMMAND_SELECT_CHANNEL = "SelectChannel";
const std::string COMMAND_SELECT_PREVIOUS_CHANNEL = "SelectPreviousChannel";

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { COMMAND_TURN_ON, bind(&CRemoteControl::TurnOn, this, std::placeholders::_1) },
					{ COMMAND_TURN_OFF, bind(&CRemoteControl::TurnOff, this, std::placeholders::_1) },
					{ COMMAND_INFO, bind(&CRemoteControl::Info, this, std::placeholders::_1) },
					{ COMMAND_SELECT_PREVIOUS_CHANNEL, bind(&CRemoteControl::SelectPreviousChannel, this, std::placeholders::_1) } 
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
		return CRemoteControl::CheckCommandSelectChannel(action);
	}
}

bool CRemoteControl::CheckChannelNumber(const std::string& stringNumber, int& number)
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

bool CRemoteControl::CheckCommandSelectChannel(std::string& action)
{
	if (action.size() > COMMAND_SELECT_CHANNEL.size())
	{
		std::string selectChannelCommand;
		if (selectChannelCommand.append(action, 0, COMMAND_SELECT_CHANNEL.size()) == COMMAND_SELECT_CHANNEL)
		{
			std::string channelNumberString;
			int channelNumber;
			if (CheckChannelNumber(channelNumberString.append(action, COMMAND_SELECT_CHANNEL.size() + 1, action.size()), channelNumber))
			{
				return CRemoteControl::SelectChannel(channelNumber);
			}
		}
	}

	return false;
}

bool CRemoteControl::TurnOn(std::istream&)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << std::endl;

	return true;
}

bool CRemoteControl::TurnOff(std::istream&)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << std::endl;

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

bool CRemoteControl::SelectPreviousChannel(std::istream&)
{
	if (m_tv.IsTurnedOn())
	{
		m_tv.SelectPreviousChannel();
		m_output << "Previous channel selected" << std::endl;
	}
	else
	{
		m_output << "Can't select previous channel because TV is turned off" << std::endl;
	}

	return true;
}

bool CRemoteControl::Info(std::istream&)
{
	std::string info = (m_tv.IsTurnedOn())
		? ("TV is turned on\nChannel is: " + std::to_string(m_tv.GetChannel()) + "\n")
		: "TV is turned off\nChannel is: 0\n";
	m_output << info;

	return true;
}

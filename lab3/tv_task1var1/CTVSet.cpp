#include "stdafx.h"
#include "CTVSet.h"

CTVSet::CTVSet()
{
}

CTVSet::~CTVSet()
{
}

bool CTVSet::IsTurnedOn() const
{
	return m_isOn;
}

bool CTVSet::SelectChannel(int channel)
{
	if ((m_isOn) && (channel <= 99) && (channel >= 1))
	{
		m_previousChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}

	return false;
}

int CTVSet::GetChannel() const
{
	return m_isOn ? m_selectedChannel : 0;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

bool CTVSet::SelectPreviousChannel()
{
	if (m_isOn)
	{
		int currentChannel = m_selectedChannel;
		m_selectedChannel = m_previousChannel;
		m_previousChannel = currentChannel;
		return true;
	}

	return false;
}

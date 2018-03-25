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

std::string CTVSet::Info() const
{
	return m_isOn ? "TV is on, current channel: " + std::to_string(m_selectedChannel) : "TV is off, current channel: 0";
}

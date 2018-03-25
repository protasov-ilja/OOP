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

bool CTVSet::SelectChannel(int channel) const
{
	return false;
}

int CTVSet::GetChannel() const
{
	return 0;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

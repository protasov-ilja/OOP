#pragma once
#include <string>

class CTVSet
{
public:
	CTVSet();
	~CTVSet();
	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();
	bool SelectChannel(int channel);
	int GetChannel() const;
	std::string Info() const;

private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
};

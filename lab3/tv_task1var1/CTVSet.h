#pragma once

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
	bool SelectPreviousChannel();

private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_previousChannel = 1;
};

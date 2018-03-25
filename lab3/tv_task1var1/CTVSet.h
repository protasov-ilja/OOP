#pragma once
class CTVSet
{
public:
	CTVSet();
	~CTVSet();
	bool IsTurnedOn() const;
	void TurnOn();
	//void TurnOff();
	bool SelectChannel(int channel) const;
	int GetChannel() const;
	//void Info();
private:
	bool m_isOn = false;
};

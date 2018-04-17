#pragma once
#include "ISolidShape.h"
class CSolidShape : public ISolidShape
{
public:
	CSolidShape() = default;
	virtual ~CSolidShape() = default;
	void SetFillColor(const std::string& fillColor);
	std::string GetFillColor() const override;

private:
	std::string m_fillColor;
};

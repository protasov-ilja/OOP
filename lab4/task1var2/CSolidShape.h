#pragma once
#include "ISolidShape.h"
#include "CShape.h"

class CSolidShape : public ISolidShape, public CShape
{
public:
	CSolidShape() = default;
	virtual ~CSolidShape() = default;
	std::string GetOutlineColor() const override;
	void SetFillColor(const std::string& fillColor);
	std::string GetFillColor() const override;

private:
	std::string m_fillColor;
};

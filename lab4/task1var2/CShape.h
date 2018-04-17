#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape() = default;
	virtual ~CShape() = default;
	std::string GetOutlineColor() const override;
	void SetOutlineColor(const std::string& outlineColor);

private:
	std::string m_outlineColor;
};

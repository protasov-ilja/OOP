#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle final : public ISolidShape
{
public:
	CCircle();
	CCircle(const CPoint& circleCenter, double circleRadius, const std::string& fillColor, const std::string& outlineColor);
	~CCircle();
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetFillColor() const override;
	std::string GetOutlineColor() const override;
	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_circleCenter;
	double m_circleRadius;
	std::string m_fillColor;
	std::string m_outlineColor;
};

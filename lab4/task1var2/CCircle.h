#pragma once
#include "CPoint2D.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(const CPoint2D& circleCenter, double circleRadius, const std::string& circleFillColor, const std::string& circleOutlineColor);
	~CCircle();
	double GetArea() const override;
	double GetPrimeter() const override;
	std::string ToString() override;
	std::string GetFillColor() override;
	std::string GetOutlineColor() const override;
	CPoint2D GetCenter() const;
	double GetRadius() const;

private:
	CPoint2D m_circleCenter;
	double m_circleRadius;
	std::string m_circleFillColor;
	std::string m_circleOutlineColor;
};

#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(const CPoint& circleCenter, double circleRadius, const std::string& circleFillColor, const std::string& circleOutlineColor);
	~CCircle();
	/*double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() override;
	std::string GetFillColor() override;
	std::string GetOutlineColor() const override;*/
	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_circleCenter;
	double m_circleRadius;
	std::string m_circleFillColor;
	std::string m_circleOutlineColor;
};

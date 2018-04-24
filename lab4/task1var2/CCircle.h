#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CCircle final : public CSolidShape
{
public:
	CCircle() = default;
	CCircle(const CPoint& circleCenter, const double circleRadius, const std::string& fillColor, const std::string& outlineColor);
	~CCircle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_circleCenter;
	double m_circleRadius;
};

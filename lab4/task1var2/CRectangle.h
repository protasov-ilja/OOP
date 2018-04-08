#pragma once
#include "CPoint2D.h"
#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint2D& leftTopAngle, const CPoint2D& rightBottomAngle, const std::string& rectangleFillColor, const std::string& rectangleOutlineColor);
	~CRectangle();
	double GetArea() const override;
	double GetPrimeter() const override;
	std::string ToString() override;
	std::string GetFillColor() override;
	std::string GetOutlineColor() const override;
	CPoint2D GetLeftTop() const;
	CPoint2D GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint2D m_leftTopAngle;
	CPoint2D m_rightBottomAngle;
	std::string m_rectangleFillColor;
	std::string m_rectangleOutlineColor;
};

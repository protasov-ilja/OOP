#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint& leftTopAngle, const CPoint& rightBottomAngle, const std::string& rectangleFillColor, const std::string& rectangleOutlineColor);
	~CRectangle();
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetFillColor() const override;
	std::string GetOutlineColor() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTopVertex;
	CPoint m_rightBottomVertex;
	std::string m_rectangleFillColor;
	std::string m_rectangleOutlineColor;
};
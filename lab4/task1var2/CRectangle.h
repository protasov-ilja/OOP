#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CRectangle final : public CSolidShape
{
public:
	CRectangle() = default;
	CRectangle(const CPoint& leftTopVertex, const double width, const double height, const std::string& outlineColor, const std::string& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	void Draw(ICanvas& canvas) const override;

private:
	CPoint GetRightTop() const;
	CPoint GetLeftBottom() const;
	CPoint m_leftTopVertex;
	double m_width;
	double m_height;
};

#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CRectangle final : public CSolidShape
{
public:
	CRectangle() = default;
	CRectangle(const CPoint& leftTopVertex, const CPoint& rightBottomVertex);
	CRectangle(const CPoint& leftTopVertex, const CPoint& rightBottomVertex, const std::string& outlineColor);
	CRectangle(const CPoint& leftTopVertex, const CPoint& rightBottomVertex, const std::string& outlineColor, const std::string& fillColor);
	~CRectangle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTopVertex;
	CPoint m_rightBottomVertex;
};

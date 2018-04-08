#pragma once
#include "CPoint2D.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint2D& vertex1, const CPoint2D& vertex2, const CPoint2D& vertex3, const std::string& triangleFillColor, const std::string& triangleOutlineColor);
	~CTriangle();
	double GetArea() const override;
	double GetPrimeter() const override;
	std::string ToString() override;
	std::string GetFillColor() override;
	std::string GetOutlineColor() const override;
	CPoint2D GetVertex1() const;
	CPoint2D GetVertex2() const;
	CPoint2D GetVertex3() const;

private:
	CPoint2D m_vertex1;
	CPoint2D m_vertex2;
	CPoint2D m_vertex3;
	std::string m_rectangleFillColor;
	std::string m_rectangleOutlineColor;
};

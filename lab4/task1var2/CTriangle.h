#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, const std::string& triangleFillColor, const std::string& triangleOutlineColor);
	~CTriangle();
	/*double GetArea() const override;
	double GetPrimeter() const override;
	std::string ToString() override;
	std::string GetFillColor() override;
	std::string GetOutlineColor() const override;*/
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	std::string m_rectangleFillColor;
	std::string m_rectangleOutlineColor;
};

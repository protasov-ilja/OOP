#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CTriangle final : public CSolidShape
{
public:
	CTriangle() = default;
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3);
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, const std::string& outlineColor);
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, const std::string& fillColor, const std::string& outlineColor);
	~CTriangle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};

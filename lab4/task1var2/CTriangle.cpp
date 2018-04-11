#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, const std::string& fillColor, const std::string& outlineColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

CTriangle::CTriangle()
{
}

CTriangle::~CTriangle()
{
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

double CTriangle::GetPerimeter() const
{
	return sqrt(pow((m_vertex2.x - m_vertex1.x), 2) + pow((m_vertex2.y - m_vertex1.y), 2)) + 
		   sqrt(pow((m_vertex3.x - m_vertex1.x), 2) + pow((m_vertex3.y - m_vertex1.y), 2)) + 
		   sqrt(pow((m_vertex3.x - m_vertex2.x), 2) + pow((m_vertex3.y - m_vertex2.y), 2));
}

std::string CTriangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

double CTriangle::GetArea() const
{
	CPoint vector1 = { m_vertex2.x - m_vertex1.x, m_vertex2.y - m_vertex1.y };
	CPoint vector2 = { m_vertex3.x - m_vertex1.x, m_vertex3.y - m_vertex1.y };
	double result = (vector1.x * vector2.y - vector2.x * vector1.y) / 2;

	return result < 0 ? result * -1 : result;
}

std::string CTriangle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(2);
	strm << "perimeter: " << GetPerimeter() << " area: " << GetArea()
		 << " fillcolor: " << GetFillColor() << " outlinecolor: " << GetOutlineColor()
		 << " vertex1.x: " << m_vertex1.x << " vertex1.y: " << m_vertex1.y
		 << " vertex1.x: " << m_vertex2.x << " vertex1.y: " << m_vertex2.y
		 << " vertex1.x: " << m_vertex3.x << " vertex1.y: " << m_vertex3.y << std::endl;

	return strm.str();
}

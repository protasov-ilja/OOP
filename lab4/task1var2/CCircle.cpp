#include "stdafx.h"
#include "CCircle.h"

CCircle::CCircle(const CPoint& circleCenter, double circleRadius, const std::string& circleFillColor, const std::string& circleOutlineColor)
	: m_circleCenter(circleCenter)
	, m_circleRadius(circleRadius)
	, m_fillColor(circleFillColor)
	, m_outlineColor(circleOutlineColor)
{
}

CCircle::CCircle()
{
}

CCircle::~CCircle()
{
}

CPoint CCircle::GetCenter() const
{
	return m_circleCenter;
}

double CCircle::GetRadius() const
{
	return m_circleRadius;
}

double CCircle::GetPerimeter() const
{
	return m_circleRadius * 2 * M_PI;
}

std::string CCircle::GetFillColor() const
{
	return m_fillColor;
}

std::string CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

double CCircle::GetArea() const
{
	return pow(m_circleRadius, 2) * M_PI;
}

std::string CCircle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(2);
	strm << "perimeter: " << GetPerimeter() << " area: " << GetArea()
		 << " fillcolor: " << GetFillColor() << " outlinecolor: " << GetOutlineColor()
		 << " center.x: " << m_circleCenter.x << " center.y: " << m_circleCenter.y
		 << " readius: " << m_circleRadius << std::endl;

	return strm.str();
}

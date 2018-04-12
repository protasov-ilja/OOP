#include "stdafx.h"
#include "CCircle.h"

CCircle::CCircle(const CPoint& circleCenter, double circleRadius)
	: m_circleCenter(circleCenter)
	, m_circleRadius(circleRadius)
{
}

CCircle::CCircle(const CPoint& circleCenter, double circleRadius, const std::string& outlineColor)
	: m_circleCenter(circleCenter)
	, m_circleRadius(circleRadius)
{
	SetOutlineColor(outlineColor);
}

CCircle::CCircle(const CPoint& circleCenter, double circleRadius, const std::string& outlineColor, const std::string& fillColor)
	: m_circleCenter(circleCenter)
	, m_circleRadius(circleRadius)
{
	SetFillColor(fillColor);
	SetOutlineColor(outlineColor);
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

double CCircle::GetArea() const
{
	return pow(m_circleRadius, 2) * M_PI;
}

std::string CCircle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(2);
	strm << "perimeter:" << GetPerimeter() << " area:" << GetArea()
		 << " fillcolor:" << GetFillColor() << " outlinecolor:" << GetOutlineColor()
		 << " center.x:" << m_circleCenter.x << " center.y:" << m_circleCenter.y
		 << " readius:" << m_circleRadius << std::endl;

	return strm.str();
}

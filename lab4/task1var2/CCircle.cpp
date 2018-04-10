#include "stdafx.h"
#include "CCircle.h"

CCircle::CCircle(const CPoint& circleCenter, double circleRadius, const std::string& circleFillColor, const std::string& circleOutlineColor)
	: m_circleCenter(circleCenter)
	, m_circleRadius(circleRadius)
	, m_circleFillColor(circleFillColor)
	, m_circleOutlineColor(circleOutlineColor)
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
	return m_circleFillColor;
}

std::string CCircle::GetOutlineColor() const
{
	return m_circleOutlineColor;
}

double CCircle::GetArea() const
{
	return pow(m_circleRadius, 2) * M_PI;
}

std::string CCircle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(2);
	strm << GetPerimeter() << " " << GetArea()
		 << " " << GetFillColor() << " " << GetOutlineColor()
		 << " " << m_circleCenter.x << " " << m_circleCenter.y
		 << " " << m_circleRadius << std::endl;

	return strm.str();
}
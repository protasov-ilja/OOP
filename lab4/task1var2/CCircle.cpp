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

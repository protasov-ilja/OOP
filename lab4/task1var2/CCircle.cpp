#include "stdafx.h"
#include "CCircle.h"
#include "CUtils.h"
#include "Config.h"

CCircle::CCircle(const CPoint& circleCenter, const double circleRadius, const std::string& outlineColor, const std::string& fillColor)
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

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.FillCircle(GetCenter(), GetRadius(), CUtils::StringToUint32(GetFillColor()));
	canvas.DrawCircle(GetCenter(), GetRadius(), CUtils::StringToUint32(GetOutlineColor()));
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
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "perimeter:" << GetPerimeter() << " area:" << GetArea()
		 << " fillcolor:" << GetFillColor() << " outlinecolor:" << GetOutlineColor()
		 << " center.x:" << m_circleCenter.x << " center.y:" << m_circleCenter.y
		 << " readius:" << m_circleRadius << std::endl;

	return strm.str();
}

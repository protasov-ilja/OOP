#include "stdafx.h"
#include "CRectangle.h"


CRectangle::CRectangle(const CPoint2D& leftTopAngle, const CPoint2D& rightBottomAngle, const std::string& rectangleFillColor, const std::string& rectangleOutlineColor)
	: m_leftTopAngle(leftTopAngle)
	, m_rightBottomAngle(rightBottomAngle)
	, m_rectangleFillColor(rectangleFillColor)
	, m_rectangleOutlineColor(rectangleOutlineColor)
{
}


CRectangle::~CRectangle()
{
}

#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(const CPoint& leftTopVertex, const CPoint& rightBottomVertex, const std::string& rectangleFillColor, const std::string& rectangleOutlineColor)
	: m_leftTopVertex(leftTopVertex)
	, m_rightBottomVertex(rightBottomVertex)
	, m_rectangleFillColor(rectangleFillColor)
	, m_rectangleOutlineColor(rectangleOutlineColor)
{
}

CRectangle::~CRectangle()
{
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopVertex;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottomVertex;
}

double CRectangle::GetWidth() const
{
	return GetRightBottom().m_x - GetLeftTop().m_x;
}

double CRectangle::GetHeight() const
{
	return GetLeftTop().m_y - GetRightBottom().m_y;
}

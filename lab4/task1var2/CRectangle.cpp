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
	return GetRightBottom().x - GetLeftTop().x;
}

double CRectangle::GetHeight() const
{
	return GetLeftTop().y - GetRightBottom().y;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (CRectangle::GetWidth() + CRectangle::GetHeight());
}

double CRectangle::GetArea() const
{
	return CRectangle::GetWidth() * CRectangle::GetHeight();
}

std::string CRectangle::GetFillColor() const
{
	return m_rectangleFillColor;
}

std::string CRectangle::GetOutlineColor() const
{
	return m_rectangleOutlineColor;
}

std::string CRectangle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(2);
	strm << GetPerimeter() << " " << GetArea()
		 << " " << GetFillColor() << " " << GetOutlineColor()
		 << " " << m_leftTopVertex.x << " " << m_leftTopVertex.y
		 << " " << m_rightBottomVertex.x << " " << m_rightBottomVertex.y
		 << " " << GetWidth() << " " << GetHeight() << std::endl;

	return strm.str();
}

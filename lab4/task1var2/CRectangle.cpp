#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(const CPoint& leftTopVertex, const CPoint& rightBottomVertex, const std::string& fillColor, const std::string& outlineColor)
	: m_leftTopVertex(leftTopVertex)
	, m_rightBottomVertex(rightBottomVertex)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

CRectangle::CRectangle()
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
	return m_fillColor;
}

std::string CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CRectangle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(2);
	strm << "perimeter: " << GetPerimeter() << "area: " << GetArea()
		 << "fillcolor: " << GetFillColor() << "outlinecolor: " << GetOutlineColor()
		 << "lefttop.x: " << m_leftTopVertex.x << "lefttop.y: " << m_leftTopVertex.y
		 << "rightBottom.x: " << m_rightBottomVertex.x << "rightBottom.y: " << m_rightBottomVertex.y
		 << "width: " << GetWidth() << "height: " << GetHeight() << std::endl;

	return strm.str();
}

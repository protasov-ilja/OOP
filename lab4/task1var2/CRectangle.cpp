#include "stdafx.h"
#include "CRectangle.h"
#include "CUtils.h"
#include "Config.h"

CRectangle::CRectangle(const CPoint& leftTopVertex, const CPoint& rightBottomVertex, const std::string& outlineColor, const std::string& fillColor)
	: m_leftTopVertex(leftTopVertex)
	, m_rightBottomVertex(rightBottomVertex)
{
	SetFillColor(fillColor);
	SetOutlineColor(outlineColor);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopVertex;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottomVertex;
}

CPoint CRectangle::GetRightTop() const
{
	return { GetLeftTop().x + GetWidth(), GetLeftTop().y };
}

CPoint CRectangle::GetLeftBottom() const
{
	return { GetLeftTop().x, GetLeftTop().y + GetHeight() };
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

void CRectangle::Draw(ICanvas& canvas)
{
	Points vertices = {
		GetLeftTop(),
		GetRightTop(),
		GetRightBottom(),
		GetLeftBottom(),
	};
	canvas.FillPolygon(vertices, CUtils::StringToUint32(GetFillColor()));
	uint32_t outlineColor = CUtils::StringToUint32(GetOutlineColor());
	canvas.DrawLine(vertices[0], vertices[1], outlineColor);
	canvas.DrawLine(vertices[1], vertices[2], outlineColor);
	canvas.DrawLine(vertices[2], vertices[3], outlineColor);
	canvas.DrawLine(vertices[3], vertices[0], outlineColor);
}

std::string CRectangle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "perimeter:" << GetPerimeter() << " area:" << GetArea()
		 << " fillcolor:" << GetFillColor() << " outlinecolor:" << GetOutlineColor()
		 << " lefttop.x:" << m_leftTopVertex.x << " lefttop.y:" << m_leftTopVertex.y
		 << " rightBottom.x:" << m_rightBottomVertex.x << " rightBottom.y:" << m_rightBottomVertex.y
		 << " width:" << GetWidth() << " height:" << GetHeight() << std::endl;

	return strm.str();
}

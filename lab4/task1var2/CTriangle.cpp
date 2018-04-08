#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle(const CPoint2D& vertex1, const CPoint2D& vertex2, const CPoint2D& vertex3, const std::string& triangleFillColor, const std::string& triangleOutlineColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_rectangleFillColor(triangleFillColor)
	, m_rectangleOutlineColor(triangleOutlineColor)
{
}

CTriangle::~CTriangle()
{
}

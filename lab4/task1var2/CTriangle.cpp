#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, const std::string& triangleFillColor, const std::string& triangleOutlineColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_triangleFillColor(triangleFillColor)
	, m_triangleOutlineColor(triangleOutlineColor)
{
}

CTriangle::~CTriangle()
{
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

double CTriangle::GetPerimeter() const
{
	return 0;
}

//std::string CTriangle::GetFillColor() const
//{
//	return m_triangleFillColor;
//}

std::string CTriangle::GetOutlineColor() const
{
	return m_triangleOutlineColor;
}

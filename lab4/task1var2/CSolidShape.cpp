#include "stdafx.h"
#include "CSolidShape.h"


void CSolidShape::SetFillColor(const std::string& fillColor)
{
	m_fillColor = fillColor;
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}
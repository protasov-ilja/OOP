#include "stdafx.h"
#include "CShape.h"

std::string CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void CShape::SetOutlineColor(const std::string& outlineColor)
{
	m_outlineColor = outlineColor;
}

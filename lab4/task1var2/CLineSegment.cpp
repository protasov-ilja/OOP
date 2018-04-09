#include "stdafx.h"
#include "CLineSegment.h"


CLineSegment::CLineSegment(const CPoint& startPointLine, const CPoint& endPointLine, const std::string& lineColor)
	: m_startPointLine(startPointLine)
	, m_endPointLine(endPointLine)
	, m_lineColor(lineColor)
{
}


CLineSegment::~CLineSegment()
{
}


CPoint CLineSegment::GetStartPoint() const
{
	return m_startPointLine;
}


CPoint CLineSegment::GetEndPoint() const
{
	return m_endPointLine;
}


double CLineSegment::GetPerimeter() const
{
	return 0;
}

std::string CLineSegment::GetOutlineColor() const
{
	return m_lineColor;
}
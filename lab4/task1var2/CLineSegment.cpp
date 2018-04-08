#include "stdafx.h"
#include "CLineSegment.h"


CLineSegment::CLineSegment(const CPoint2D& startPointLine, const CPoint2D& endPointLine, const std::string& lineColor)
	: m_startPointLine(startPointLine)
	, m_endPointLine(endPointLine)
	, m_lineColor(lineColor)
{
}


CLineSegment::~CLineSegment()
{
}

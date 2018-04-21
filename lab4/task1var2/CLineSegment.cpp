#include "stdafx.h"
#include "CLineSegment.h"
#include "CUtils.h"
#include "Config.h"

CLineSegment::CLineSegment(const CPoint& startPointLine, const CPoint& endPointLine, const std::string& lineColor)
	: m_startPointLine(startPointLine)
	, m_endPointLine(endPointLine)
{
	CShape::SetOutlineColor(lineColor);
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
	return sqrt(pow((m_endPointLine.x - m_startPointLine.x), 2) + pow((m_endPointLine.y - m_startPointLine.y), 2));
}

double CLineSegment::GetArea() const
{
	return 0;
}

void CLineSegment::Draw(ICanvas& canvas)
{
	canvas.DrawLine(GetStartPoint(), GetEndPoint(), CUtils::StringToUint32(GetOutlineColor()));
}

std::string CLineSegment::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "perimeter:" << GetPerimeter() << " area:" << GetArea()
		 << " outlinecolor:" << GetOutlineColor() << " startpoint.x:" << m_startPointLine.x
		 << " startpoint.y:" << m_startPointLine.y << " endpoint.x:" << m_endPointLine.x
		 << " endpoint.y:" << m_endPointLine.y << std::endl;

	return strm.str();
}

#pragma once
#include "CPoint.h"
#include "CShape.h"

class CLineSegment final : public CShape
{
public:
	CLineSegment() = default;
	CLineSegment(const CPoint& startPointLine, const CPoint& endPointLine);
	CLineSegment(const CPoint& startPointLine, const CPoint& endPointLine, const std::string& lineColor);
	~CLineSegment() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	CPoint m_startPointLine;
	CPoint m_endPointLine;
};

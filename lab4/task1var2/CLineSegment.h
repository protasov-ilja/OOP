#pragma once
#include "CPoint.h"
#include "CShape.h"

class CLineSegment final : public CShape
{
public:
	CLineSegment() = default;
	CLineSegment(const CPoint& startPointLine, const CPoint& endPointLine, const std::string& lineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_startPointLine;
	CPoint m_endPointLine;
};

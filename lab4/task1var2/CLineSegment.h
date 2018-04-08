#pragma once
#include "CPoint2D.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint2D& startPointLine, const CPoint2D& endPointLine, const std::string& lineColor);
	~CLineSegment();
	double GetArea() const override;
	double GetPrimeter() const override;
	std::string ToString() override;
	std::string GetOutlineColor() const override;
	CPoint2D GetStartPoint() const;
	CPoint2D GetEndPoint() const;

private:
	CPoint2D m_startPointLine;
	CPoint2D m_endPointLine;
	std::string m_lineColor;
};

#pragma once
#include "CPoint.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint& startPointLine, const CPoint& endPointLine, const std::string& lineColor);
	~CLineSegment();
	/*double GetArea() const override;
	double GetPrimeter() const override;
	std::string ToString() override;
	std::string GetOutlineColor() const override;*/
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	CPoint m_startPointLine;
	CPoint m_endPointLine;
	std::string m_lineColor;
};

#pragma once
#include "CPoint.h"

typedef std::vector<CPoint> Points;

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void DrawLine(CPoint from, CPoint to, uint32_t lineColor) = 0;
	virtual void FillPolygon(Points points, uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(CPoint center, double radius, uint32_t fillColor) = 0;
};

#pragma once
class CPoint
{
public:
	CPoint(double x, double y);
	CPoint() = default;
	~CPoint() = default;

	double x = 0;
	double y = 0;
};

#pragma once
#include <string>

class IShape
{
public:
	IShape();
	virtual ~IShape();
	virtual double GetArea() const;
	virtual double GetPrimeter() const;
	virtual std::string ToString();
	virtual std::string GetOutlineColor() const;
};


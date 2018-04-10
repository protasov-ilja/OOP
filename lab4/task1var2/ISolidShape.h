#pragma once
#include "IShape.h"
class ISolidShape : public IShape
{
public:
	ISolidShape();
	virtual ~ISolidShape();
	virtual std::string GetFillColor() const = 0;
};

#pragma once
#include "CShape.h"
class ISolidShape : public CShape
{
public:
	virtual ~ISolidShape() = default;
	virtual std::string GetFillColor() const = 0;
};

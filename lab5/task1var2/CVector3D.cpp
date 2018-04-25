#include "stdafx.h"
#include "CVector3D.h"
#include "float.h"
#include <cmath>
#include <iostream>

CVector3D::CVector3D(double x0, double y0, double z0)
	: x(x0)
	, y(y0)
	, z(z0)
{
}

double CVector3D::GetLength() const
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void CVector3D::Normalize()
{
	double lengthInversion = 1 / GetLength();
	x *= lengthInversion;
	y *= lengthInversion;
	z *= lengthInversion;
}

CVector3D const CVector3D::operator-() const
{
	return CVector3D(-x, -y, -z);
}

CVector3D const CVector3D::operator+() const
{
	return *this;
}

CVector3D const CVector3D::operator+(const CVector3D& vector2) const
{
	return CVector3D(x + vector2.x, y + vector2.y, z + vector2.z);
}

CVector3D const CVector3D::operator-(const CVector3D& vector2) const
{
	return CVector3D(x - vector2.x, y - vector2.y, z - vector2.z);
}

CVector3D CVector3D::operator+=(const CVector3D& vector2)
{
	x += vector2.x;
	y += vector2.y;
	z += vector2.z;

	return *this;
}

CVector3D CVector3D::operator-=(const CVector3D& vector2)
{
	x -= vector2.x;
	y -= vector2.y;
	z -= vector2.z;

	return *this;
}

CVector3D const CVector3D::operator*(double scalar) const
{
	return CVector3D(x * scalar, y * scalar, z * scalar);
}

CVector3D const CVector3D::operator/(double scalar) const
{
	return CVector3D(x / scalar, y / scalar, z / scalar);
}

CVector3D CVector3D::operator*=(double scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

CVector3D CVector3D::operator/=(double scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

bool CVector3D::CompareDoubleNumbers(double number1, double number2) const
{
	double diff = number1 - number2;
	return (diff < DBL_EPSILON) && (-diff < DBL_EPSILON);
}

bool CVector3D::operator==(const CVector3D& otherVector) const
{
	return (CompareDoubleNumbers(x, otherVector.x)) && (CompareDoubleNumbers(y, otherVector.y)) && (CompareDoubleNumbers(z, otherVector.z));
}

bool CVector3D::operator!=(const CVector3D& otherVector) const
{
	return !(*this == otherVector);
}

std::ostream& operator<<(std::ostream& stream, const CVector3D& vector)
{
	stream << vector.x << ", " << vector.y << ", " << vector.z;

	return stream;
}

std::istream& operator>>(std::istream& stream, CVector3D& vector)
{
	double inputX;
	double inputY;
	double inputZ;
	if ((stream >> inputX) && (stream.get() == ',') && (stream.get() == ' ') && (stream >> inputY) && (stream.get() == ',') && (stream.get() == ' ') && (stream >> inputZ))
	{
		vector = CVector3D(inputX, inputY, inputZ);
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}

CVector3D const operator*(double scalar, const CVector3D& vector)
{
	return CVector3D((scalar * vector.x), (scalar * vector.y), (scalar * vector.z));
}

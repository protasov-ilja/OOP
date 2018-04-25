#pragma once
#include <iostream>
class CVector3D
{
public:
	CVector3D() = default;
	CVector3D(double x0, double y0, double z0);
	double GetLength() const;
	void Normalize();
	CVector3D const operator-() const;
	CVector3D const operator+() const;
	CVector3D const operator+(const CVector3D& vector) const;
	CVector3D const operator-(const CVector3D& vector) const;
	CVector3D operator+=(const CVector3D& vector);
	CVector3D operator-=(const CVector3D& vector);
	CVector3D const operator*(double scalar) const;
	CVector3D const operator/(double scalar) const;
	CVector3D operator*=(double scalar);
	CVector3D operator/=(double scalar);
	bool operator==(const CVector3D& otherVector) const;
	bool operator!=(const CVector3D& otherVector) const;

	double x = 0;
	double y = 0;
	double z = 0;

private:
	bool CompareDoubleNumbers(double number1, double number2) const;
};

CVector3D const operator*(double scalar, const CVector3D& vector);
std::istream& operator>>(std::istream& stream, CVector3D& vector);
std::ostream& operator<<(std::ostream& stream, const CVector3D& vector);

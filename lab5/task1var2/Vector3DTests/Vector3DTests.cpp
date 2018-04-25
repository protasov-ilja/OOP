#include "stdafx.h"
#include "..\CVector3D.h"
#include <sstream>

const double EPSILON = 0.001;

bool CompareDoubles(double a, double b)
{
	double diff = a - b;
	return (diff < EPSILON) && (-diff < EPSILON);
}

bool compareVectors3D(const CVector3D& vector1, const CVector3D& vector2)
{
	return ((CompareDoubles(vector1.x, vector2.x)) && (CompareDoubles(vector1.y, vector2.y)) && (CompareDoubles(vector1.z, vector2.z)));
}

// ������
TEST_CASE("test vector3D")
{
	// ����� ������� ���� ��������� � �������� �����������
	SECTION("can create its own instance with zero parameters")
	{
		CVector3D vector;
		REQUIRE(compareVectors3D(vector, { 0, 0, 0 }));
	}

	// ����� ������� ���� ��������� � ��������� �����������
	SECTION("can create its own instance with the specified parameters")
	{
		CVector3D vector(2, 4, 5);
		REQUIRE(compareVectors3D(vector, { 2, 4, 5 }));
	}

	// ����� ������� ���� �����
	SECTION("can return its length")
	{
		CVector3D vector(2, 2, 1);
		REQUIRE(CompareDoubles(vector.GetLength(), sqrt(2 * 2 + 2 * 2 + 1 * 1)));
	}

	// ����� ������������� ����
	SECTION("can normalize itself")
	{
		CVector3D vector(2, 2, 1);
		double lengthInversion = 1 / vector.GetLength();
		vector.Normalize();
		REQUIRE(compareVectors3D(vector, { (2 * lengthInversion), (2 * lengthInversion), (1 * lengthInversion) }));
	}

	// �� ������ ����� ������ ��� ������������� �������� �����
	SECTION("doesnt change its data when using the unary plus")
	{
		CVector3D vector(2, 4, 5);
		CVector3D vector1 = +vector;
		REQUIRE(compareVectors3D(vector1, { 2, 4, 5 }));
	}

	// ����� �������� ���� ��������� �� ��������������� ��� ������������� �������� ������
	SECTION("can change its parameters to the opposite when using the unary minus")
	{
		CVector3D vector(2, 4, 5);
		CVector3D vector1 = -vector;
		REQUIRE(compareVectors3D(vector1, { -2, -4, -5 }));
	}

	// ����� ������� ����� ������� ������� � ������ �������
	SECTION("can add the length of the second vector with the length of the first")
	{
		CVector3D vector1(2, 4.4, 5);
		CVector3D vector2(0, 0, 0);
		CVector3D addVector = vector1 + vector2;
		REQUIRE(compareVectors3D(addVector, { 2, 4.4, 5 }));
	}

	// ����� ������� ����� ������� ������� �� ����� �������
	SECTION("can subtract the length of the second vector from the length of the first")
	{
		CVector3D vector1(2, 4.4, 5);
		CVector3D vector2(0, 0, 0);
		CVector3D subVector = vector1 - vector2;
		REQUIRE(compareVectors3D(subVector, { 2, 4.4, 5 }));
	}

	// ����� ������� ��������� ���������� ����� ����� �� ����� ������� �������
	SECTION("can return the result of increasing its length by the length of the second vector")
	{
		CVector3D vector1(2, 4.4, 5);
		CVector3D vector2(0, 0, 0);
		vector1 += vector2;
		REQUIRE(compareVectors3D(vector1, { 2, 4.4, 5 }));
	}

	// ����� ������� ��������� ���������� ����� ����� �� ������ ������� �������
	SECTION("can return the result of decreasing its length by the length of the second vector")
	{
		CVector3D vector1(2, 4.4, 5);
		CVector3D vector2(0, 0, 0);
		vector1 -= vector2;
		REQUIRE(compareVectors3D(vector1, { 2, 4.4, 5 }));
	}

	// ����� ������� ��������� ��������� ����� ����� �� ������
	SECTION("can return the result of multiplying its length by scalar")
	{
		double scalar = 2;
		CVector3D vector1(1, 2, 3);
		CVector3D vector2 = vector1 * scalar;
		REQUIRE(compareVectors3D(vector2, { 2, 4, 6 }));
	}

	// ����� ������� ��������� ��������� ������� �� ���� �����
	SECTION("can return the result of multiplying the scalar by its length")
	{
		double scalar = 2;
		CVector3D vector1(1, 2, 3);
		CVector3D vector2 = scalar * vector1;
		REQUIRE(compareVectors3D(vector2, { 2, 4, 6 }));
	}

	// ����� ������� ��������� ������� ����� ����� �� ������
	SECTION("can return the result of dividing its length by a scalar")
	{
		double scalar = 2;
		CVector3D vector1(2, 2, 2);
		CVector3D vector2 = vector1 / scalar;
		REQUIRE(compareVectors3D(vector2, { 1, 1, 1 }));
	}

	// ����� �������� ���� ������ �� ������
	SECTION("can multiply its length by scalar")
	{
		double scalar = 2;
		CVector3D vector(1, 2, 3);
		vector *= scalar;
		REQUIRE(compareVectors3D(vector, { 2, 4, 6 }));
	}

	// ����� ��������� ���� ������ �� ������
	SECTION("can divide its length by scalar")
	{
		double scalar = 2;
		CVector3D vector(2, 2, 2);
		vector /= scalar;
		REQUIRE(compareVectors3D(vector, { 1, 1, 1 }));
	}

	// ��� ��������� ���� �������� ���������� ������ ��� �� ���������
	SECTION("when comparing two vectors returns true when they are equal")
	{
		CVector3D vector1(2, 2, 2);
		CVector3D vector2(2, 2, 2);
		REQUIRE(vector1 == vector2);
	}

	// ��� ��������� ���� �������� ���������� ���� ��� �� �� ���������
	SECTION("when comparing two vectors returns false if they do not equal")
	{
		CVector3D vector1(2, 2, 2);
		CVector3D vector2(2, 3, 2);
		REQUIRE(!(vector1 == vector2));
	}

	// ��� ��������� ���� �������� ���������� ������ ��� �� �� ���������
	SECTION("when comparing two vectors returns true if they do not equal")
	{
		CVector3D vector1(2, 2, 2);
		CVector3D vector2(2, 3, 2);
		REQUIRE(vector1 != vector2);
	}

	// ��� ��������� ���� �������� ���������� ���� ��� �� ���������
	SECTION("when comparing two vectors returns false if they are equal")
	{
		CVector3D vector1(2, 2, 2);
		CVector3D vector2(2, 2, 2);
		REQUIRE(!(vector1 != vector2));
	}

	// ����� ��������� ������ �� ������
	SECTION("can read a vector from the stream")
	{
		std::stringstream strm("2, 2, 2");
		CVector3D vector;
		strm >> vector;
		REQUIRE(compareVectors3D(vector, { 2, 2, 2 }));
	}

	// ����� �������� ������ � �����
	SECTION("can write a vector into a stream")
	{
		std::stringstream strm;
		CVector3D vector(1, 2, 3);
		strm << vector;
		REQUIRE(strm.str() == "1, 2, 3");
	}
}

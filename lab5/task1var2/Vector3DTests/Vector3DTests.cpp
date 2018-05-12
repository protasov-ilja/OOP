#include "stdafx.h"
#include "..\CVector3D.h"
#include "..\Utils.h"
#include <sstream>

using namespace Utils;

bool compareVectors3D(const CVector3D& vector1, const CVector3D& vector2)
{
	return ((CompareDoubleNumbers(vector1.x, vector2.x)) && (CompareDoubleNumbers(vector1.y, vector2.y)) && (CompareDoubleNumbers(vector1.z, vector2.z)));
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
	SECTION("can create its own instance with specified parameters")
	{
		CVector3D vector(2, 4, 5);
		REQUIRE(compareVectors3D(vector, { 2, 4, 5 }));
	}

	// ����� ������� ���� �����
	SECTION("can return its length")
	{
		CVector3D vector(2, 2, 1);
		REQUIRE(CompareDoubleNumbers(vector.GetLength(), sqrt(2 * 2 + 2 * 2 + 1 * 1)));
	}

	// ����� ������������� ����
	SECTION("can normalize itself")
	{
		CVector3D vector(2, 2, 1);
		double lengthInversion = 1 / vector.GetLength();
		vector.Normalize();
		REQUIRE(compareVectors3D(vector, { (2 * lengthInversion), (2 * lengthInversion), (1 * lengthInversion) }));
	}
}

// ������������ ��������
TEST_CASE("override")
{
	// ������� ����
	SECTION("unary plus")
	{
		// �� ������ ������ �������
		SECTION("doesnt change vectors data")
		{
			CVector3D vector(2, 4, 5);
			CVector3D vector1 = +vector;
			REQUIRE(compareVectors3D(vector1, { 2, 4, 5 }));
		}
	}

	// ������� �����
	SECTION("unary minus")
	{
		// ����� �������� ��������� ������� �� ���������������
		SECTION("can change parameters of vector to opposite")
		{
			CVector3D vector(2, 4, 5);
			CVector3D vector1 = -vector;
			REQUIRE(compareVectors3D(vector1, { -2, -4, -5 }));
		}
	}

	// ����
	SECTION("plus")
	{
		// ����� ������� ����� ������� ������� � ������ �������
		SECTION("can add length of second vector with length of first")
		{
			CVector3D vector1(2, 4.4, 5);
			CVector3D vector2(0, 0, 0);
			CVector3D addVector = vector1 + vector2;
			REQUIRE(compareVectors3D(addVector, { 2, 4.4, 5 }));
		}
	}

	// �����
	SECTION("minus")
	{
		// ����� ������� ����� ������� ������� �� ����� �������
		SECTION("can subtract length of second vector from length of first")
		{
			CVector3D vector1(2, 4.4, 5);
			CVector3D vector2(0, 0, 0);
			CVector3D subVector = vector1 - vector2;
			REQUIRE(compareVectors3D(subVector, { 2, 4.4, 5 }));
		}
	}

	// +=
	SECTION("+=")
	{
		// ����� ��������� ����� ������� �� ����� ������� �������
		SECTION("can increase length of vector by length of second vector")
		{
			CVector3D vector1(2, 4.4, 5);
			CVector3D vector2(0, 0, 0);
			vector1 += vector2;
			REQUIRE(compareVectors3D(vector1, { 2, 4.4, 5 }));
		}
	}

	// -=
	SECTION("-=")
	{
		// ����� ������� ����� ������� ������� �� ����� ������� �������
		SECTION("can subtract length of second vector from length of first vector")
		{
			CVector3D vector1(2, 4.4, 5);
			CVector3D vector2(0, 0, 0);
			vector1 -= vector2;
			REQUIRE(compareVectors3D(vector1, { 2, 4.4, 5 }));
		}
	}

	// ���������
	SECTION("multiplication")
	{
		// ����� �������� ����� ������� �� ������
		SECTION("can multiply length of vector by scalar")
		{
			double scalar = 2;
			CVector3D vector1(1, 2, 3);
			CVector3D vector2 = vector1 * scalar;
			REQUIRE(compareVectors3D(vector2, { 2, 4, 6 }));
		}

		// ����� �������� ������ �� ����� �������
		SECTION("can multiply scalar by length of vector")
		{
			double scalar = 2;
			CVector3D vector1(1, 2, 3);
			CVector3D vector2 = scalar * vector1;
			REQUIRE(compareVectors3D(vector2, { 2, 4, 6 }));
		}
	}

	// �������
	SECTION("division")
	{
		// ����� ��������� ����� ������� �� ������
		SECTION("can divide length of vector into scalar")
		{
			double scalar = 2;
			CVector3D vector1(2, 2, 2);
			CVector3D vector2 = vector1 / scalar;
			REQUIRE(compareVectors3D(vector2, { 1, 1, 1 }));
		}
	}

	// *=
	SECTION("*=")
	{
		// ����� �������� ����� ������� �� ������
		SECTION("can multiply length of vector by scalar")
		{
			double scalar = 2;
			CVector3D vector(1, 2, 3);
			vector *= scalar;
			REQUIRE(compareVectors3D(vector, { 2, 4, 6 }));
		}
	}

	// /=
	SECTION("/=")
	{
		// ����� ��������� ����� ������� �� ������
		SECTION("can divide length of vector into scalar")
		{
			double scalar = 2;
			CVector3D vector(2, 2, 2);
			vector /= scalar;
			REQUIRE(compareVectors3D(vector, { 1, 1, 1 }));
		}
	}

	// ���������
	SECTION("==")
	{
		// ��� ��������� ���� �������� ���������� ������ ����� ��� �����
		SECTION("when comparing two vectors returns true when they are equal")
		{
			CVector3D vector1(2, 2, 2);
			CVector3D vector2(2, 2, 2);
			REQUIRE(vector1 == vector2);
		}

		// ��� ��������� ���� �������� ���������� ���� ���� ��� �� �����
		SECTION("when comparing two vectors returns false if they do not equal")
		{
			CVector3D vector1(2, 2, 2);
			CVector3D vector2(2, 3, 2);
			REQUIRE(!(vector1 == vector2));
		}
	}

	// �����������
	SECTION("!=")
	{
		// ��� ��������� ���� �������� ���������� ������ ���� ��� �� �����
		SECTION("when comparing two vectors returns true if they do not equal")
		{
			CVector3D vector1(2, 2, 2);
			CVector3D vector2(2, 3, 2);
			REQUIRE(vector1 != vector2);
		}

		// ��� ��������� ���� �������� ���������� ���� ���� ��� �����
		SECTION("when comparing two vectors returns false if they are equal")
		{
			CVector3D vector1(2, 2, 2);
			CVector3D vector2(2, 2, 2);
			REQUIRE(!(vector1 != vector2));
		}
	}

	// ���������� �� ������
	SECTION(">>")
	{
		// ����� ��������� ������ �� ������ � ������� x, y, z
		SECTION("can read a vector from a stream in the format x, y, z")
		{
			std::stringstream strm("2, 2, 2");
			CVector3D vector;
			strm >> vector;
			REQUIRE(compareVectors3D(vector, { 2, 2, 2 }));
		}
	}

	// ������ � �����
	SECTION("<<")
	{
		// ����� �������� ������ � ����� � ������� x, y, z
		SECTION("can write a vector into a stream in the format x, y, z")
		{
			std::stringstream strm;
			CVector3D vector(1, 2, 3);
			strm << vector;
			REQUIRE(strm.str() == "1, 2, 3");
		}
	}
}

// ������� ���������� ������������
TEST_CASE("DotProduct function")
{
	// ����� ������� ��������� ���������� ������������ ���� ���������� ��������
	SECTION("can return result of scalar product of two three-dimensional vectors")
	{
		CVector3D vector1(1, 2, 3);
		CVector3D vector2(-1, -2, -3);
		double PoluchenResult = DotProduct(vector1, vector2);
		double requireResult = (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
		REQUIRE(CompareDoubleNumbers(PoluchenResult, requireResult));
	}
}

// ������� ���������� ������������
TEST_CASE("CrossProduct function")
{
	// ����� ������� ��������� ���������� ������������ ���� ���������� ��������
	SECTION("can return result of cross product of two three-dimensional vectors")
	{
		CVector3D v1(1, 2, 3);
		CVector3D v2(1, 2, 3);
		CVector3D PoluchenResult = CrossProduct(v1, v2);
		CVector3D requireResult((v1.y * v2.z) - (v1.z * v2.y), -1 * ((v1.x * v2.z) - (v1.z * v2.x)), (v1.x * v2.y) - (v1.y * v2.x));
		REQUIRE(compareVectors3D(PoluchenResult, requireResult));
	}
}

// ������� ������������
TEST_CASE("Normalize function")
{
	// ����� ������� ��������� ������, ������� �� �� �����������, ��� � ������, ����������� � �������� ��������� �������
	SECTION("can return unit vector which having same direction as vector that acting as argument of function")
	{
		CVector3D v1(1, 2, 3);
		CVector3D PoluchenResult = Normalize(v1);
		CVector3D normalizeVector(v1.x, v1.y, v1.z);
		normalizeVector.Normalize();
		REQUIRE(compareVectors3D(PoluchenResult, normalizeVector));
	}
}

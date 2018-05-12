#include "stdafx.h"
#include "..\CVector3D.h"
#include "..\Utils.h"
#include <sstream>

using namespace Utils;

bool compareVectors3D(const CVector3D& vector1, const CVector3D& vector2)
{
	return ((CompareDoubleNumbers(vector1.x, vector2.x)) && (CompareDoubleNumbers(vector1.y, vector2.y)) && (CompareDoubleNumbers(vector1.z, vector2.z)));
}

// вектор
TEST_CASE("test vector3D")
{
	// может создать свой экземпляр с нулевыми параметрами
	SECTION("can create its own instance with zero parameters")
	{
		CVector3D vector;
		REQUIRE(compareVectors3D(vector, { 0, 0, 0 }));
	}

	// может создать свой экземпляр с заданными параметрами
	SECTION("can create its own instance with specified parameters")
	{
		CVector3D vector(2, 4, 5);
		REQUIRE(compareVectors3D(vector, { 2, 4, 5 }));
	}

	// может вернуть свою длину
	SECTION("can return its length")
	{
		CVector3D vector(2, 2, 1);
		REQUIRE(CompareDoubleNumbers(vector.GetLength(), sqrt(2 * 2 + 2 * 2 + 1 * 1)));
	}

	// может нормализовать себя
	SECTION("can normalize itself")
	{
		CVector3D vector(2, 2, 1);
		double lengthInversion = 1 / vector.GetLength();
		vector.Normalize();
		REQUIRE(compareVectors3D(vector, { (2 * lengthInversion), (2 * lengthInversion), (1 * lengthInversion) }));
	}
}

// перегруженый оператор
TEST_CASE("override")
{
	// унарный плюс
	SECTION("unary plus")
	{
		// не меняет данных вектора
		SECTION("doesnt change vectors data")
		{
			CVector3D vector(2, 4, 5);
			CVector3D vector1 = +vector;
			REQUIRE(compareVectors3D(vector1, { 2, 4, 5 }));
		}
	}

	// унарный минус
	SECTION("unary minus")
	{
		// может поменять параметры вектора на противоположные
		SECTION("can change parameters of vector to opposite")
		{
			CVector3D vector(2, 4, 5);
			CVector3D vector1 = -vector;
			REQUIRE(compareVectors3D(vector1, { -2, -4, -5 }));
		}
	}

	// плюс
	SECTION("plus")
	{
		// может сложить длину второго вектора с длиной первого
		SECTION("can add length of second vector with length of first")
		{
			CVector3D vector1(2, 4.4, 5);
			CVector3D vector2(0, 0, 0);
			CVector3D addVector = vector1 + vector2;
			REQUIRE(compareVectors3D(addVector, { 2, 4.4, 5 }));
		}
	}

	// минус
	SECTION("minus")
	{
		// может вычесть длину второго вектора из длины первого
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
		// может увеличить длину вектора на длину второго вектора
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
		// может вычесть длину второго вектора из длины первого вектора
		SECTION("can subtract length of second vector from length of first vector")
		{
			CVector3D vector1(2, 4.4, 5);
			CVector3D vector2(0, 0, 0);
			vector1 -= vector2;
			REQUIRE(compareVectors3D(vector1, { 2, 4.4, 5 }));
		}
	}

	// умножения
	SECTION("multiplication")
	{
		// может умножить длину вектора на скаляр
		SECTION("can multiply length of vector by scalar")
		{
			double scalar = 2;
			CVector3D vector1(1, 2, 3);
			CVector3D vector2 = vector1 * scalar;
			REQUIRE(compareVectors3D(vector2, { 2, 4, 6 }));
		}

		// может умножить скаляр на длину вектора
		SECTION("can multiply scalar by length of vector")
		{
			double scalar = 2;
			CVector3D vector1(1, 2, 3);
			CVector3D vector2 = scalar * vector1;
			REQUIRE(compareVectors3D(vector2, { 2, 4, 6 }));
		}
	}

	// деления
	SECTION("division")
	{
		// может разделить длину вектора на скаляр
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
		// может умножить длину вектора на скаляр
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
		// может разделить длину вектора на скаляр
		SECTION("can divide length of vector into scalar")
		{
			double scalar = 2;
			CVector3D vector(2, 2, 2);
			vector /= scalar;
			REQUIRE(compareVectors3D(vector, { 1, 1, 1 }));
		}
	}

	// равенства
	SECTION("==")
	{
		// при сравнении двух векторов возвращает истину когда они равны
		SECTION("when comparing two vectors returns true when they are equal")
		{
			CVector3D vector1(2, 2, 2);
			CVector3D vector2(2, 2, 2);
			REQUIRE(vector1 == vector2);
		}

		// при сравнении двух векторов возвращает ложь если они не равны
		SECTION("when comparing two vectors returns false if they do not equal")
		{
			CVector3D vector1(2, 2, 2);
			CVector3D vector2(2, 3, 2);
			REQUIRE(!(vector1 == vector2));
		}
	}

	// неравенства
	SECTION("!=")
	{
		// при сравнении двух векторов возвращает истину если они не равны
		SECTION("when comparing two vectors returns true if they do not equal")
		{
			CVector3D vector1(2, 2, 2);
			CVector3D vector2(2, 3, 2);
			REQUIRE(vector1 != vector2);
		}

		// при сравнении двух векторов возвращает ложь если они равны
		SECTION("when comparing two vectors returns false if they are equal")
		{
			CVector3D vector1(2, 2, 2);
			CVector3D vector2(2, 2, 2);
			REQUIRE(!(vector1 != vector2));
		}
	}

	// считывания из потока
	SECTION(">>")
	{
		// может считывать вектор из потока в формате x, y, z
		SECTION("can read a vector from a stream in the format x, y, z")
		{
			std::stringstream strm("2, 2, 2");
			CVector3D vector;
			strm >> vector;
			REQUIRE(compareVectors3D(vector, { 2, 2, 2 }));
		}
	}

	// записи в поток
	SECTION("<<")
	{
		// может записать вектор в поток в формате x, y, z
		SECTION("can write a vector into a stream in the format x, y, z")
		{
			std::stringstream strm;
			CVector3D vector(1, 2, 3);
			strm << vector;
			REQUIRE(strm.str() == "1, 2, 3");
		}
	}
}

// функция скалярного произведения
TEST_CASE("DotProduct function")
{
	// может вернуть результат скалярного произведения двух трехмерных векторов
	SECTION("can return result of scalar product of two three-dimensional vectors")
	{
		CVector3D vector1(1, 2, 3);
		CVector3D vector2(-1, -2, -3);
		double PoluchenResult = DotProduct(vector1, vector2);
		double requireResult = (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
		REQUIRE(CompareDoubleNumbers(PoluchenResult, requireResult));
	}
}

// функция векторного произведения
TEST_CASE("CrossProduct function")
{
	// может вернуть результат векторного произведения двух трехмерных векторов
	SECTION("can return result of cross product of two three-dimensional vectors")
	{
		CVector3D v1(1, 2, 3);
		CVector3D v2(1, 2, 3);
		CVector3D PoluchenResult = CrossProduct(v1, v2);
		CVector3D requireResult((v1.y * v2.z) - (v1.z * v2.y), -1 * ((v1.x * v2.z) - (v1.z * v2.x)), (v1.x * v2.y) - (v1.y * v2.x));
		REQUIRE(compareVectors3D(PoluchenResult, requireResult));
	}
}

// функция нормализации
TEST_CASE("Normalize function")
{
	// может вернуть единичный вектор, имеющий то же направление, что и вектор, выступающий в качестве аргумента функции
	SECTION("can return unit vector which having same direction as vector that acting as argument of function")
	{
		CVector3D v1(1, 2, 3);
		CVector3D PoluchenResult = Normalize(v1);
		CVector3D normalizeVector(v1.x, v1.y, v1.z);
		normalizeVector.Normalize();
		REQUIRE(compareVectors3D(PoluchenResult, normalizeVector));
	}
}

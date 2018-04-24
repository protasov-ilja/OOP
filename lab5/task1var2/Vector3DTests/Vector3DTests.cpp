#include "stdafx.h"
#include "..\CVector3D.h"

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

// вектор
TEST_CASE("test vector3D")
{
	// может создать свой экземпляр с нулевыми параметрами
	SECTION("vector1")
	{
		CVector3D vector;
		REQUIRE(compareVectors3D(vector, { 0, 0, 0 }));
	}

	// может создать свой экземпляр с задаными параметрами
	SECTION("vector2")
	{
		CVector3D vector(2, 4, 5);
		REQUIRE(compareVectors3D(vector, {2, 4, 5}));
	}

	// может вернуть свою длину
	{
		CVector3D vector(2, 2, 1);
		REQUIRE(CompareDoubles(vector.GetLength(), sqrt(2 * 2 + 2 * 2 + 1 * 1)));
	}

	// может не менять своих данных при использовании унарного плюса
	SECTION("vector2.2")
	{
		CVector3D vector(2, 4, 5);
		CVector3D vector1 = +vector;
		REQUIRE(compareVectors3D(vector1, { 2, 4, 5 }));
	}

	// может поменять свои параметры на противоположные при использовании унарного минуса
	SECTION("vector2.3")
	{
		CVector3D vector(2, 4, 5);
		CVector3D vector1 = -vector;
		REQUIRE(compareVectors3D(vector1, { -2, -4, -5 }));
	}

	//  может сложить длину второго вектора с длиной первого
	SECTION("vector3")
	{
		CVector3D vector1(2, 4.4, 5);
		CVector3D vector2(0, 0, 0);
		CVector3D addVector = vector1 + vector2;
		REQUIRE(compareVectors3D(addVector, {2, 4.4, 5}));
	}

	// может вычесть длину второго вектора из длины первого
	SECTION("vector4")
	{
		CVector3D vector1(2, 4.4, 5);
		CVector3D vector2(0, 0, 0);
		CVector3D subVector = vector1 - vector2;
		REQUIRE(compareVectors3D(subVector, { 2, 4.4, 5 }));
	}

	// может вернуть результат увеличения своей длины на длинну второго вектора
	SECTION("vector5")
	{
		CVector3D vector1(2, 4.4, 5);
		CVector3D vector2(0, 0, 0);
		vector1 += vector2;
		REQUIRE(compareVectors3D(vector1, { 2, 4.4, 5 }));
	}

	// может вернуть результат уменьшения своей длины на длинну второго вектора
	SECTION("vector6")
	{
		CVector3D vector1(2, 4.4, 5);
		CVector3D vector2(0, 0, 0);
		vector1 -= vector2;
		REQUIRE(compareVectors3D(vector1, { 2, 4.4, 5 }));
	}

	// может вернуть результат умножения своей длины на скаляр
	SECTION("vector7")
	{
		double scalar = 2;
		CVector3D vector1(1, 2, 3);
		CVector3D vector2 = vector1 * scalar;
		REQUIRE(compareVectors3D(vector2, { 2, 4, 6 }));
	}

	// может вернуть результат умножения скаляра на свою длину 
	SECTION("vector8")
	{
		double scalar = 2;
		CVector3D vector1(1, 2, 3);
		CVector3D vector2 = scalar * vector1;
		REQUIRE(compareVectors3D(vector2, { 2, 4, 6 }));
	}

	// может вернуть результат деления своей длины на скаляр
	SECTION("vector9")
	{
		double scalar = 2;
		CVector3D vector1(2, 2, 2);
		CVector3D vector2 = vector1 / scalar;
		REQUIRE(compareVectors3D(vector2, { 1, 1, 1 }));
	}

	// может умножить свою длинну на скаляр
	SECTION("vector10")
	{
		double scalar = 2;
		CVector3D vector(1, 2, 3);
		vector *= scalar;
		REQUIRE(compareVectors3D(vector, { 2, 4, 6 }));
	}

	// может разделить свою длинну на скаляр
	SECTION("vector11")
	{
		double scalar = 2;
		CVector3D vector(2, 2, 2);
		vector /= scalar;
		REQUIRE(compareVectors3D(vector, { 1, 1, 1 }));
	}

	// при сравнении двух векторов возвращает истину при их равенстве
	SECTION("vector12")
	{
		CVector3D vector1(2, 2, 2);
		CVector3D vector2(2, 2, 2);
		REQUIRE(vector1 == vector2);
	}

	// при сравнении двух векторов возвращает ложь при их не равенстве
	SECTION("vector12")
	{
		CVector3D vector1(2, 2, 2);
		CVector3D vector2(2, 3, 2);
		REQUIRE(!(vector1 == vector2));
	}

	// при сравнении двух векторов возвращает истину при их не равенстве
	SECTION("vector12")
	{
		CVector3D vector1(2, 2, 2);
		CVector3D vector2(2, 3, 2);
		REQUIRE(vector1 != vector2);
	}

	// при сравнении двух векторов возвращает ложь при их равенстве
	SECTION("vector12")
	{
		CVector3D vector1(2, 2, 2);
		CVector3D vector2(2, 2, 2);
		REQUIRE(!(vector1 != vector2));
	}
}

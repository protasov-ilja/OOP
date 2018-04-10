#include "stdafx.h"
#include "..\CCircle.h"
#include "..\CLineSegment.h"
#include "..\CRectangle.h"
#include "..\CTriangle.h"
#include <vector>

const double EPSILON = 0.001;

bool PointsAreEqual(const CPoint& firstPoint, const CPoint& secondPoint)
{
	return ((firstPoint.x == secondPoint.x) && (firstPoint.y == secondPoint.y));
}

bool StringsAreEqual(const std::string& a, const std::string& b)
{
	return a == b;
}

bool CompareDoubles(double a, double b)
{
	double diff = a - b;
	return (diff < EPSILON) && (-diff < EPSILON);
}

// �������
TEST_CASE("test lineSegment", "[lineSegment]")
{
	CLineSegment lineSegment({ 0, 0 }, { 2, 0 }, "ffffff");

	// ����� ���������� ���� ��������� �����
	SECTION("lineSegment1")
	{
		REQUIRE(PointsAreEqual(lineSegment.GetStartPoint(), { 0, 0 }));
	}

	// ����� ���������� ���� �������� �����
	SECTION("lineSegment2")
	{
		REQUIRE(PointsAreEqual(lineSegment.GetEndPoint(), { 2, 0 }));
	}

	// ����� ���������� ���� �����
	SECTION("lineSegment3")
	{
		REQUIRE(lineSegment.GetPerimeter() == 2);
	}

	// ����� ���������� ���� ������ �������
	SECTION("lineSegment4")
	{
		REQUIRE(lineSegment.GetOutlineColor() == "ffffff");
	}

	// ����� ���������� ���� �������
	SECTION("lineSegment5")
	{
		REQUIRE(lineSegment.GetArea() == 0);
	}

	// ����� ���������� ���������� � ����
	SECTION("lineSegment6")
	{
		REQUIRE(lineSegment.ToString() == "2.00 0.00 ffffff 0.00 0.00 2.00 0.00\n");
	}
}

// �����������
TEST_CASE("test triangle", "[triangle]")
{
	CTriangle triangle({ 0, 0 }, { 2, 2 }, { 4, 0 }, "ffffff", "000000");

	// ����� ���������� ���������� ����� 1-�� �������
	SECTION("triangle1")
	{
		REQUIRE(PointsAreEqual(triangle.GetVertex1(), { 0, 0 }));
	}

	// ����� ���������� ���������� ����� 2-�� �������
	SECTION("triangle2")
	{
		REQUIRE(PointsAreEqual(triangle.GetVertex2(), { 2, 2 }));
	}

	// ����� ���������� ���������� ����� 3-�� �������
	SECTION("triangle3")
	{
		REQUIRE(PointsAreEqual(triangle.GetVertex3(), { 4, 0 }));
	}

	// ����� ���������� ���� ��������
	SECTION("triangle4")
	{
		REQUIRE(CompareDoubles(triangle.GetPerimeter(), 9.6568542495));
	}

	// ����� ���������� ���� ����� �������
	SECTION("triangle5")
	{
		REQUIRE(triangle.GetFillColor() == "ffffff");
	}

	// ����� ���������� ���� ������ �������
	SECTION("triangle6")
	{
		REQUIRE(triangle.GetOutlineColor() == "000000");
	}

	// ����� ���������� ���� �������
	SECTION("triangle7")
	{
		REQUIRE(triangle.GetArea() == 4);
	}

	// ����� ���������� ���������� � ����
	SECTION("triangle8")
	{
		REQUIRE(triangle.ToString() == "9.66 4.00 ffffff 000000 0.00 0.00 2.00 2.00 4.00 0.00\n");
	}
}

// �������������
TEST_CASE("test rectangle", "[rectangle]")
{
	CRectangle rectangle({ 0, 0 }, { 2, -3 }, "ffffff", "000000");

	// ����� ���������� ���������� ����� ������� �������
	SECTION("rectangle1")
	{
		REQUIRE(PointsAreEqual(rectangle.GetLeftTop(), { 0, 0 }));
	}

	// ����� ���������� ���������� ������ ������ �������
	SECTION("rectangle2")
	{
		REQUIRE(PointsAreEqual(rectangle.GetRightBottom(), { 2, -3 }));
	}

	// ����� ���������� ���� ������
	SECTION("rectangle3")
	{
		REQUIRE(rectangle.GetWidth() == 2);
	}

	// ����� ���������� ���� ������
	SECTION("rectangle4")
	{
		REQUIRE(rectangle.GetHeight() == 3);
	}

	// ����� ���������� ���� ��������
	SECTION("rectangle5")
	{
		REQUIRE(rectangle.GetPerimeter() == 10);
	}

	// ����� ���������� ���� ����� �������
	SECTION("rectangle6")
	{
		REQUIRE(rectangle.GetFillColor() == "ffffff");
	}

	// ����� ���������� ���� ������ �������
	SECTION("rectangle7")
	{
		REQUIRE(rectangle.GetOutlineColor() == "000000");
	}

	// ����� ���������� ���� �������
	SECTION("rectangle8")
	{
		REQUIRE(rectangle.GetArea() == 6);
	}

	// ����� ���������� ���������� � ����
	SECTION("rectangle9")
	{
		REQUIRE(rectangle.ToString() == "10.00 6.00 ffffff 000000 0.00 0.00 2.00 -3.00 2.00 3.00\n");
	}
}

// ����
TEST_CASE("test circle", "[circle]")
{
	CCircle circle({ 0, 0 }, 2, "ffffff", "000000");

	// ����� ���������� ���������� ������ ������
	SECTION("circle1")
	{
		REQUIRE(PointsAreEqual(circle.GetCenter(), { 0, 0 }));
	}

	// ����� ���������� ���� ������
	SECTION("circle2")
	{
		REQUIRE(circle.GetRadius() == 2);
	}

	// ����� ���������� ���� ��������
	SECTION("circle3")
	{
		REQUIRE(circle.GetPerimeter() == 2 * 2 * M_PI);
	}

	// ����� ���������� ���� ����� �������
	SECTION("circle4")
	{
		REQUIRE(circle.GetFillColor() == "ffffff");
	}

	// ����� ���������� ���� ������ �������
	SECTION("circle5")
	{
		REQUIRE(circle.GetOutlineColor() == "000000");
	}

	// ����� ���������� ���� �������
	SECTION("circle6")
	{
		REQUIRE(circle.GetArea() == 2 * 2 * M_PI);
	}

	// ����� ���������� ���������� � ����
	SECTION("circle7")
	{
		REQUIRE(circle.ToString() == "12.57 12.57 ffffff 000000 0.00 0.00 2.00\n");
	}
}

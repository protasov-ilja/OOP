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
TEST_CASE("test lineSegment")
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
	SECTION("lineSegment4.2")
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
		REQUIRE(lineSegment.ToString() == "perimeter:2.00 area:0.00 outlinecolor:ffffff startpoint.x:0.00 startpoint.y:0.00 endpoint.x:2.00 endpoint.y:0.00\n");
	}
}

// �����������
TEST_CASE("test triangle")
{
	CTriangle triangle({ 0, 0 }, { 2, 2 }, { 4, 0 }, "000000", "ffffff");

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
	SECTION("triangle5.3")
	{
		REQUIRE(triangle.GetFillColor() == "ffffff");
	}

	// ����� ���������� ���� ������ �������
	SECTION("triangle6.3")
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
		REQUIRE(triangle.ToString() == "perimeter:9.66 area:4.00 fillcolor:ffffff outlinecolor:000000 vertex1.x:0.00 vertex1.y:0.00 vertex2.x:2.00 vertex2.y:2.00 vertex3.x:4.00 vertex3.y:0.00\n");
	}
}

// �������������
TEST_CASE("test rectangle")
{
	CRectangle rectangle({ 0, 0 }, { 2, -3 }, "000000", "ffffff");

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
		REQUIRE(rectangle.ToString() == "perimeter:10.00 area:6.00 fillcolor:ffffff outlinecolor:000000 lefttop.x:0.00 lefttop.y:0.00 rightBottom.x:2.00 rightBottom.y:-3.00 width:2.00 height:3.00\n");
	}
}

// ����
TEST_CASE("test circle")
{
	CCircle circle({ 0, 0 }, 2, "000000", "ffffff");

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
		REQUIRE(circle.ToString() == "perimeter:12.57 area:12.57 fillcolor:ffffff outlinecolor:000000 center.x:0.00 center.y:0.00 readius:2.00\n");
	}
}

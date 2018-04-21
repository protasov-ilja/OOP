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

bool CompareDoubles(double a, double b)
{
	double diff = a - b;
	return (diff < EPSILON) && (-diff < EPSILON);
}

// �������
TEST_CASE("test lineSegment ")
{
	CLineSegment lineSegment({ 0, 0 }, { 2, 0 }, "ffffff");

	// ����� ���������� ���� ��������� �����
	SECTION("can return its start point")
	{
		REQUIRE(PointsAreEqual(lineSegment.GetStartPoint(), { 0, 0 }));
	}

	// ����� ���������� ���� �������� �����
	SECTION("can return its end point")
	{
		REQUIRE(PointsAreEqual(lineSegment.GetEndPoint(), { 2, 0 }));
	}

	// ����� ���������� ���� �����
	SECTION("can return its length")
	{
		REQUIRE(lineSegment.GetPerimeter() == 2);
	}

	// ����� ���������� ���� ������ �������
	SECTION("can return its outline color")
	{
		REQUIRE(lineSegment.GetOutlineColor() == "ffffff");
	}

	// ����� ���������� ���� �������
	SECTION("can return its area")
	{
		REQUIRE(lineSegment.GetArea() == 0);
	}

	// ����� ���������� ���������� � ����
	SECTION("can return information about itself")
	{
		REQUIRE(lineSegment.ToString() == "perimeter:2.00 area:0.00 outlinecolor:ffffff startpoint.x:0.00 startpoint.y:0.00 endpoint.x:2.00 endpoint.y:0.00\n");
	}
}

// �����������
TEST_CASE("test triangle ")
{
	CTriangle triangle({ 0, 0 }, { 2, 2 }, { 4, 0 }, "000000", "ffffff");

	// ����� ���������� ���������� ����� 1-�� �������
	SECTION("can return coordinates of its first vertex")
	{
		REQUIRE(PointsAreEqual(triangle.GetVertex1(), { 0, 0 }));
	}

	// ����� ���������� ���������� ����� 2-�� �������
	SECTION("can return coordinates of its 2nd vertex")
	{
		REQUIRE(PointsAreEqual(triangle.GetVertex2(), { 2, 2 }));
	}

	// ����� ���������� ���������� ����� 3-�� �������
	SECTION("can return coordinates of its 3rd vertex")
	{
		REQUIRE(PointsAreEqual(triangle.GetVertex3(), { 4, 0 }));
	}

	// ����� ���������� ���� ��������
	SECTION("can return its perimeter")
	{
		REQUIRE(CompareDoubles(triangle.GetPerimeter(), 9.6568542495));
	}

	// ����� ���������� ���� ����� �������
	SECTION("can return its fill color")
	{
		REQUIRE(triangle.GetFillColor() == "ffffff");
	}

	// ����� ���������� ���� ������ �������
	SECTION("can return its outline color")
	{
		REQUIRE(triangle.GetOutlineColor() == "000000");
	}

	// ����� ���������� ���� �������
	SECTION("can return its area")
	{
		REQUIRE(triangle.GetArea() == 4);
	}

	// ����� ���������� ���������� � ����
	SECTION("can return information about itself")
	{
		REQUIRE(triangle.ToString() == "perimeter:9.66 area:4.00 fillcolor:ffffff outlinecolor:000000 vertex1.x:0.00 vertex1.y:0.00 vertex2.x:2.00 vertex2.y:2.00 vertex3.x:4.00 vertex3.y:0.00\n");
	}
}

// �������������
TEST_CASE("test rectangle ")
{
	CRectangle rectangle({ 0, 0 },  2, 3, "000000", "ffffff");

	// ����� ���������� ���������� ����� ������� �������
	SECTION("can return coordinates of left top vertex")
	{
		REQUIRE(PointsAreEqual(rectangle.GetLeftTop(), { 0, 0 }));
	}

	// ����� ���������� ���������� ������ ������ �������
	SECTION("can return coordinates of right bottom vertex")
	{
		REQUIRE(PointsAreEqual(rectangle.GetRightBottom(), { 2, 3 }));
	}

	// ����� ���������� ���� ������
	SECTION("can return its width")
	{
		REQUIRE(rectangle.GetWidth() == 2);
	}

	// ����� ���������� ���� ������
	SECTION("can return its height")
	{
		REQUIRE(rectangle.GetHeight() == 3);
	}

	// ����� ���������� ���� ��������
	SECTION("can return its perimeter")
	{
		REQUIRE(rectangle.GetPerimeter() == 10);
	}

	// ����� ���������� ���� ����� �������
	SECTION("can return its fill color")
	{
		REQUIRE(rectangle.GetFillColor() == "ffffff");
	}

	// ����� ���������� ���� ������ �������
	SECTION("can return its outline color")
	{
		REQUIRE(rectangle.GetOutlineColor() == "000000");
	}

	// ����� ���������� ���� �������
	SECTION("can return its area")
	{
		REQUIRE(rectangle.GetArea() == 6);
	}

	// ����� ���������� ���������� � ����
	SECTION("can return information about itself")
	{
		REQUIRE(rectangle.ToString() == "perimeter:10.00 area:6.00 fillcolor:ffffff outlinecolor:000000 lefttop.x:0.00 lefttop.y:0.00 rightBottom.x:2.00 rightBottom.y:3.00 width:2.00 height:3.00\n");
	}
}

// ����
TEST_CASE("test circle ")
{
	CCircle circle({ 0, 0 }, 2, "000000", "ffffff");

	// ����� ���������� ���������� ������ ������
	SECTION("can return coordinates of its center")
	{
		REQUIRE(PointsAreEqual(circle.GetCenter(), { 0, 0 }));
	}

	// ����� ���������� ���� ������
	SECTION("can return its radius")
	{
		REQUIRE(circle.GetRadius() == 2);
	}

	// ����� ���������� ���� ��������
	SECTION("can return its perimeter")
	{
		REQUIRE(circle.GetPerimeter() == 2 * 2 * M_PI);
	}

	// ����� ���������� ���� ����� �������
	SECTION("can return its fill color")
	{
		REQUIRE(circle.GetFillColor() == "ffffff");
	}

	// ����� ���������� ���� ������ �������
	SECTION("can return its outline color")
	{
		REQUIRE(circle.GetOutlineColor() == "000000");
	}

	// ����� ���������� ���� �������
	SECTION("can return its area")
	{
		REQUIRE(circle.GetArea() == 2 * 2 * M_PI);
	}

	// ����� ���������� ���������� � ����
	SECTION("can return information about itself")
	{
		REQUIRE(circle.ToString() == "perimeter:12.57 area:12.57 fillcolor:ffffff outlinecolor:000000 center.x:0.00 center.y:0.00 readius:2.00\n");
	}
}

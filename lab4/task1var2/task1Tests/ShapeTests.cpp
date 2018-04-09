#include "stdafx.h"
#include "..\CCircle.h"
#include "..\CLineSegment.h"
#include "..\CRectangle.h"
#include "..\CTriangle.h"
#include <vector>

bool PointsAreEqual(const CPoint& firstPoint, const CPoint& secondPoint)
{
	return ((firstPoint.m_x == secondPoint.m_x) && (firstPoint.m_y == secondPoint.m_y));
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
		CHECK(lineSegment.GetOutlineColor() == "ffffff");
	}
}

// �����������
TEST_CASE("test triangle", "[triangle]")
{
	CTriangle triangle({ 0, 0 }, { 2, 2 }, { 4, 0 }, "ffffff", "000000");

	// ����� ���������� ���������� ����� 1-�� �������
	SECTION("triangle1")
	{
		CHECK(PointsAreEqual(triangle.GetVertex1(), { 0, 0 }));
	}

	// ����� ���������� ���������� ����� 2-�� �������
	SECTION("triangle2")
	{
		CHECK(PointsAreEqual(triangle.GetVertex2(), { 2, 2 }));
	}

	// ����� ���������� ���������� ����� 3-�� �������
	SECTION("triangle3")
	{
		CHECK(PointsAreEqual(triangle.GetVertex3(), { 4, 0 }));
	}

	// ����� ���������� ���� ��������
	SECTION("triangle4")
	{
		REQUIRE(triangle.GetPerimeter() == 2);
	}

	//// ����� ���������� ���� ����� �������
	//SECTION("triangle5")
	//{
	//	CHECK(triangle.GetFillColor() == "ffffff");
	//}

	// ����� ���������� ���� ������ �������
	SECTION("triangle6")
	{
		CHECK(triangle.GetOutlineColor() == "000000");
	}
}

// �������������
TEST_CASE("test rectangle", "[rectangle]")
{
	CRectangle rectangle({ 0, 0 }, { 2, -3 }, "ffffff", "000000");

	// ����� ���������� ���������� ����� ������� �������
	SECTION("rectangle1")
	{
		CHECK(PointsAreEqual(rectangle.GetLeftTop(), { 0, 0 }));
	}

	// ����� ���������� ���������� ������ ������ �������
	SECTION("rectangle2")
	{
		CHECK(PointsAreEqual(rectangle.GetRightBottom(), { 2, -3 }));
	}

	// ����� ���������� ���� ������
	SECTION("rectangle3")
	{
		CHECK(rectangle.GetWidth() == 2);
	}

	// ����� ���������� ���� ������
	SECTION("rectangle4")
	{
		CHECK(rectangle.GetHeight() == 3);
	}

	// ����� ���������� ���� ��������
	SECTION("rectangle5")
	{
		REQUIRE(rectangle.GetPerimeter() == 2);
	}

	//// ����� ���������� ���� ����� �������
	//SECTION("rectangle6")
	//{
	//	CHECK(rectangle.GetFillColor() == "ffffff");
	//}

	// ����� ���������� ���� ������ �������
	SECTION("rectangle7")
	{
		CHECK(rectangle.GetOutlineColor() == "000000");
	}
}

// ����
TEST_CASE("test circle", "[circle]")
{
	CCircle circle({ 0, 0 }, 2, "ffffff", "000000");

	// ����� ���������� ���������� ������ ������
	SECTION("circle1")
	{
		CHECK(PointsAreEqual(circle.GetCenter(), { 0, 0 }));
	}

	// ����� ���������� ���� ������
	SECTION("circle2")
	{
		CHECK(circle.GetRadius() == 2);
	}

	// ����� ���������� ���� ��������
	SECTION("circle3")
	{
		REQUIRE(circle.GetPerimeter() == 2 * 2 * M_PI);
	}

	//// ����� ���������� ���� ����� �������
	//SECTION("circle4")
	//{
	//	CHECK(circle.GetFillColor() == "ffffff");
	//}

	// ����� ���������� ���� ������ �������
	SECTION("circle5")
	{
		CHECK(circle.GetOutlineColor() == "000000");
	}
}

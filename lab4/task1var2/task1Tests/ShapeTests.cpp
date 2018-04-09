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

CLineSegment lineSegment({ 1, 2 }, { 2, 4 }, "ffffff");

// �������
TEST_CASE("test lineSegment", "[lineSegment]")
{
	// ����� ���������� ���� ��������� �����
	SECTION("lineSegment1")
	{
		REQUIRE(PointsAreEqual(lineSegment.GetStartPoint(), { 1, 2 }));
	}

	// ����� ���������� ���� �������� �����
	SECTION("lineSegment2")
	{
		REQUIRE(PointsAreEqual(lineSegment.GetEndPoint(), { 2, 4 }));
	}
}

CTriangle triangle({ 0, 0 }, { 2, 2 }, { 4, 0 }, "ffffff", "ffffff");

// �����������
TEST_CASE("test triangle", "[triangle]")
{
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
}

CRectangle rectangle({ 0, 0 }, { 2, -3 }, "ffffff", "ffffff");

// �������������
TEST_CASE("test rectangle", "[rectangle]")
{
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
}

CCircle circle({ 0, 0 }, 2, "ffffff", "ffffff");

// ����������
TEST_CASE("test circle", "[circle]")
{
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
}

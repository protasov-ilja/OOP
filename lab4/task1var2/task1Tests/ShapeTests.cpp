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

// Отрезок
TEST_CASE("test lineSegment", "[lineSegment]")
{
	// может возвращать свою начальную точку
	SECTION("lineSegment1")
	{
		REQUIRE(PointsAreEqual(lineSegment.GetStartPoint(), { 1, 2 }));
	}

	// может возвращать свою конечную точку
	SECTION("lineSegment2")
	{
		REQUIRE(PointsAreEqual(lineSegment.GetEndPoint(), { 2, 4 }));
	}
}

CTriangle triangle({ 0, 0 }, { 2, 2 }, { 4, 0 }, "ffffff", "ffffff");

// Треугольник
TEST_CASE("test triangle", "[triangle]")
{
	// может возвращать координаты своей 1-ой вершины
	SECTION("triangle1")
	{
		CHECK(PointsAreEqual(triangle.GetVertex1(), { 0, 0 }));
	}

	// может возвращать координаты своей 2-ой вершины
	SECTION("triangle2")
	{
		CHECK(PointsAreEqual(triangle.GetVertex2(), { 2, 2 }));
	}

	// может возвращать координаты своей 3-ой вершины
	SECTION("triangle3")
	{
		CHECK(PointsAreEqual(triangle.GetVertex3(), { 4, 0 }));
	}
}

CRectangle rectangle({ 0, 0 }, { 2, -3 }, "ffffff", "ffffff");

// Прямоугольник
TEST_CASE("test rectangle", "[rectangle]")
{
	// может возвращать координаты левой верхней вершины
	SECTION("rectangle1")
	{
		CHECK(PointsAreEqual(rectangle.GetLeftTop(), { 0, 0 }));
	}

	// может возвращать координаты правой нижней вершины
	SECTION("rectangle2")
	{
		CHECK(PointsAreEqual(rectangle.GetRightBottom(), { 2, -3 }));
	}

	// может возвращать свою ширину
	SECTION("rectangle3")
	{
		CHECK(rectangle.GetWidth() == 2);
	}

	// может возвращать свою высоту
	SECTION("rectangle4")
	{
		CHECK(rectangle.GetHeight() == 3);
	}
}

CCircle circle({ 0, 0 }, 2, "ffffff", "ffffff");

// Окружность
TEST_CASE("test circle", "[circle]")
{
	// может возвращать координаты своего центра
	SECTION("circle1")
	{
		CHECK(PointsAreEqual(circle.GetCenter(), { 0, 0 }));
	}

	// может возвращать свой радиус
	SECTION("circle2")
	{
		CHECK(circle.GetRadius() == 2);
	}
}

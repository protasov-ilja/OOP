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

// Отрезок
TEST_CASE("test lineSegment", "[lineSegment]")
{
	CLineSegment lineSegment({ 0, 0 }, { 2, 0 }, "ffffff");

	// может возвращать свою начальную точку
	SECTION("lineSegment1")
	{
		REQUIRE(PointsAreEqual(lineSegment.GetStartPoint(), { 0, 0 }));
	}

	// может возвращать свою конечную точку
	SECTION("lineSegment2")
	{
		REQUIRE(PointsAreEqual(lineSegment.GetEndPoint(), { 2, 0 }));
	}

	// может возвращать свою длину
	SECTION("lineSegment3")
	{
		REQUIRE(lineSegment.GetPerimeter() == 2);
	}

	// может возвращать цвет своего контура
	SECTION("lineSegment4")
	{
		CHECK(lineSegment.GetOutlineColor() == "ffffff");
	}
}

// Треугольник
TEST_CASE("test triangle", "[triangle]")
{
	CTriangle triangle({ 0, 0 }, { 2, 2 }, { 4, 0 }, "ffffff", "000000");

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

	// может возвращать свой периметр
	SECTION("triangle4")
	{
		REQUIRE(triangle.GetPerimeter() == 2);
	}

	//// может возвращать цвет своей заливки
	//SECTION("triangle5")
	//{
	//	CHECK(triangle.GetFillColor() == "ffffff");
	//}

	// может возвращать цвет своего контура
	SECTION("triangle6")
	{
		CHECK(triangle.GetOutlineColor() == "000000");
	}
}

// Прямоугольник
TEST_CASE("test rectangle", "[rectangle]")
{
	CRectangle rectangle({ 0, 0 }, { 2, -3 }, "ffffff", "000000");

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

	// может возвращать свой периметр
	SECTION("rectangle5")
	{
		REQUIRE(rectangle.GetPerimeter() == 2);
	}

	//// может возвращать цвет своей заливки
	//SECTION("rectangle6")
	//{
	//	CHECK(rectangle.GetFillColor() == "ffffff");
	//}

	// может возвращать цвет своего контура
	SECTION("rectangle7")
	{
		CHECK(rectangle.GetOutlineColor() == "000000");
	}
}

// Круг
TEST_CASE("test circle", "[circle]")
{
	CCircle circle({ 0, 0 }, 2, "ffffff", "000000");

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

	// может возвращать свой периметр
	SECTION("circle3")
	{
		REQUIRE(circle.GetPerimeter() == 2 * 2 * M_PI);
	}

	//// может возвращать цвет своей заливки
	//SECTION("circle4")
	//{
	//	CHECK(circle.GetFillColor() == "ffffff");
	//}

	// может возвращать цвет своего контура
	SECTION("circle5")
	{
		CHECK(circle.GetOutlineColor() == "000000");
	}
}

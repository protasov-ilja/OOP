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

// Отрезок
TEST_CASE("test lineSegment")
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
	SECTION("lineSegment4.2")
	{
		REQUIRE(lineSegment.GetOutlineColor() == "ffffff");
	}

	// может возвращать свою площадь
	SECTION("lineSegment5")
	{
		REQUIRE(lineSegment.GetArea() == 0);
	}

	// может возвращать информацию о себе
	SECTION("lineSegment6")
	{
		REQUIRE(lineSegment.ToString() == "perimeter:2.00 area:0.00 outlinecolor:ffffff startpoint.x:0.00 startpoint.y:0.00 endpoint.x:2.00 endpoint.y:0.00\n");
	}
}

// Треугольник
TEST_CASE("test triangle")
{
	CTriangle triangle({ 0, 0 }, { 2, 2 }, { 4, 0 }, "000000", "ffffff");

	// может возвращать координаты своей 1-ой вершины
	SECTION("triangle1")
	{
		REQUIRE(PointsAreEqual(triangle.GetVertex1(), { 0, 0 }));
	}

	// может возвращать координаты своей 2-ой вершины
	SECTION("triangle2")
	{
		REQUIRE(PointsAreEqual(triangle.GetVertex2(), { 2, 2 }));
	}

	// может возвращать координаты своей 3-ой вершины
	SECTION("triangle3")
	{
		REQUIRE(PointsAreEqual(triangle.GetVertex3(), { 4, 0 }));
	}

	// может возвращать свой периметр
	SECTION("triangle4")
	{
		REQUIRE(CompareDoubles(triangle.GetPerimeter(), 9.6568542495));
	}

	// может возвращать цвет своей заливки
	SECTION("triangle5.3")
	{
		REQUIRE(triangle.GetFillColor() == "ffffff");
	}

	// может возвращать цвет своего контура
	SECTION("triangle6.3")
	{
		REQUIRE(triangle.GetOutlineColor() == "000000");
	}

	// может возвращать свою площадь
	SECTION("triangle7")
	{
		REQUIRE(triangle.GetArea() == 4);
	}

	// может возвращать информацию о себе
	SECTION("triangle8")
	{
		REQUIRE(triangle.ToString() == "perimeter:9.66 area:4.00 fillcolor:ffffff outlinecolor:000000 vertex1.x:0.00 vertex1.y:0.00 vertex2.x:2.00 vertex2.y:2.00 vertex3.x:4.00 vertex3.y:0.00\n");
	}
}

// Прямоугольник
TEST_CASE("test rectangle")
{
	CRectangle rectangle({ 0, 0 }, { 2, -3 }, "000000", "ffffff");

	// может возвращать координаты левой верхней вершины
	SECTION("rectangle1")
	{
		REQUIRE(PointsAreEqual(rectangle.GetLeftTop(), { 0, 0 }));
	}

	// может возвращать координаты правой нижней вершины
	SECTION("rectangle2")
	{
		REQUIRE(PointsAreEqual(rectangle.GetRightBottom(), { 2, -3 }));
	}

	// может возвращать свою ширину
	SECTION("rectangle3")
	{
		REQUIRE(rectangle.GetWidth() == 2);
	}

	// может возвращать свою высоту
	SECTION("rectangle4")
	{
		REQUIRE(rectangle.GetHeight() == 3);
	}

	// может возвращать свой периметр
	SECTION("rectangle5")
	{
		REQUIRE(rectangle.GetPerimeter() == 10);
	}

	// может возвращать цвет своей заливки
	SECTION("rectangle6")
	{
		REQUIRE(rectangle.GetFillColor() == "ffffff");
	}

	// может возвращать цвет своего контура
	SECTION("rectangle7")
	{
		REQUIRE(rectangle.GetOutlineColor() == "000000");
	}

	// может возвращать свою площадь
	SECTION("rectangle8")
	{
		REQUIRE(rectangle.GetArea() == 6);
	}

	// может возвращать информацию о себе
	SECTION("rectangle9")
	{
		REQUIRE(rectangle.ToString() == "perimeter:10.00 area:6.00 fillcolor:ffffff outlinecolor:000000 lefttop.x:0.00 lefttop.y:0.00 rightBottom.x:2.00 rightBottom.y:-3.00 width:2.00 height:3.00\n");
	}
}

// Круг
TEST_CASE("test circle")
{
	CCircle circle({ 0, 0 }, 2, "000000", "ffffff");

	// может возвращать координаты своего центра
	SECTION("circle1")
	{
		REQUIRE(PointsAreEqual(circle.GetCenter(), { 0, 0 }));
	}

	// может возвращать свой радиус
	SECTION("circle2")
	{
		REQUIRE(circle.GetRadius() == 2);
	}

	// может возвращать свой периметр
	SECTION("circle3")
	{
		REQUIRE(circle.GetPerimeter() == 2 * 2 * M_PI);
	}

	// может возвращать цвет своей заливки
	SECTION("circle4")
	{
		REQUIRE(circle.GetFillColor() == "ffffff");
	}

	// может возвращать цвет своего контура
	SECTION("circle5")
	{
		REQUIRE(circle.GetOutlineColor() == "000000");
	}

	// может возвращать свою площадь
	SECTION("circle6")
	{
		REQUIRE(circle.GetArea() == 2 * 2 * M_PI);
	}

	// может возвращать информацию о себе
	SECTION("circle7")
	{
		REQUIRE(circle.ToString() == "perimeter:12.57 area:12.57 fillcolor:ffffff outlinecolor:000000 center.x:0.00 center.y:0.00 readius:2.00\n");
	}
}

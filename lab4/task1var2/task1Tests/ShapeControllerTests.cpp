#include "stdafx.h"
#include "..\CCircle.h"
#include "..\CLineSegment.h"
#include "..\CRectangle.h"
#include "..\CTriangle.h"
#include "..\CShapeController.h"
#include <vector>

struct ShapeControllerDependencies
{
	std::stringstream input;
	std::stringstream output;
};

struct ShapeControllerFixture : ShapeControllerDependencies
{
	CShapeController shapeController;

	ShapeControllerFixture()
		: shapeController(input, output)
	{
	}

	void VerifyCommandHandling(const std::string& command, const std::string& expectedOutput)
	{
		output = std::stringstream();
		input = std::stringstream();
		REQUIRE(input << command);
		REQUIRE(shapeController.HandleCommand());
		REQUIRE(input.eof());
		REQUIRE(output.str() == expectedOutput);
	}
};

// контроллер фигур
TEST_CASE_METHOD(ShapeControllerFixture, "test shapeController ",)
{
	// может добавить отрезок
	SECTION("can add line segment")
	{
		VerifyCommandHandling("lineSegment 1 2 3 4 ffffff", "LineSegmentWasAdded\n");
		VerifyCommandHandling("lineSegment 1 2 3 4 ffffffff", "LineSegmentWasAdded\n");
		VerifyCommandHandling("lineSegment 11 22 22 34 000000", "LineSegmentWasAdded\n");
		VerifyCommandHandling("lineSegment 12 22 33 4 aaaaaa", "LineSegmentWasAdded\n");
		VerifyCommandHandling("lineSegment 13.4 4.2 3.5 4.4 999999", "LineSegmentWasAdded\n");
	}

	// не может добавить отрезок если параметры не указаны или неправильного типа и возвращает информацию об ошибке
	SECTION("cant add line if parameters are not specified or wrong type and returns error information")
	{
		VerifyCommandHandling("lineSegment 1 d 3 4 ffffff", "you wrote incorrect arguments\nplease write: lineSegment start.x start.y end.x end.y outlinecolor\n");
		VerifyCommandHandling("lineSegment 1 1 1f 4 ffffff", "you wrote incorrect arguments\nplease write: lineSegment start.x start.y end.x end.y outlinecolor\n");
		VerifyCommandHandling("lineSegment 1 1 3 d4 ffffff", "you wrote incorrect arguments\nplease write: lineSegment start.x start.y end.x end.y outlinecolor\n");
		VerifyCommandHandling("lineSegment 1a2 1 3 d ffffff", "you wrote incorrect arguments\nplease write: lineSegment start.x start.y end.x end.y outlinecolor\n");
		VerifyCommandHandling("lineSegment a 1 3 d ffffff", "you wrote incorrect arguments\nplease write: lineSegment start.x start.y end.x end.y outlinecolor\n");
		VerifyCommandHandling("lineSegment a 1 3 d", "you wrote incorrect arguments\nplease write: lineSegment start.x start.y end.x end.y outlinecolor\n");
		VerifyCommandHandling("lineSegment 1 1 3 ffffff", "you wrote incorrect arguments\nplease write: lineSegment start.x start.y end.x end.y outlinecolor\n");
		VerifyCommandHandling("lineSegment ffffff", "you wrote incorrect arguments\nplease write: lineSegment start.x start.y end.x end.y outlinecolor\n");
		VerifyCommandHandling("lineSegment", "you wrote incorrect arguments\nplease write: lineSegment start.x start.y end.x end.y outlinecolor\n");
	}

	// не может добавить отрезок если цвет не в 16-ти ричной системе счисления и его длина меньше или больше 6
	SECTION("cant add line segment if the outline color is not in the 16-bit number system and its length is less than or greater than 6")
	{
		VerifyCommandHandling("lineSegment 1 2 3 4 afd32", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("lineSegment 1 2 3 4 fgFfff", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("lineSegment 1 2 3 4 gfFfff", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("lineSegment 1 2 3 4 fFfffg", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("lineSegment 1 2 3 4 fff99fd", "you wrote incorrect color\ncolor must be hex color\n");
	}

	// может добавить круг
	SECTION("can add circle")
	{
		VerifyCommandHandling("circle 1 2 2 ffffff ffffff", "CircleWasAdded\n");
		VerifyCommandHandling("circle 1 2 2 ffffffff ffffff", "CircleWasAdded\n");
		VerifyCommandHandling("circle 1 2 2 ffffff ffffffff", "CircleWasAdded\n");
		VerifyCommandHandling("circle 1 2 2 000000 000000", "CircleWasAdded\n");
		VerifyCommandHandling("circle 1 2 3 aaaaaa aaaaaa", "CircleWasAdded\n");
		VerifyCommandHandling("circle 1 2 5 999999 999999", "CircleWasAdded\n");
	}

	// не может добавить круг если параметры не указаны или неправильного типа и возвращает информацию об ошибке
	SECTION("cant add circle if the parameters are not specified or wrong type and returns error information")
	{
		VerifyCommandHandling("circle 1 d 4 ffffff 000000", "you wrote incorrect arguments\nplease write: circle center.x center.y radius outlinecolor fillcolor\n");
		VerifyCommandHandling("circle 1 1a 4 ffffff 000000", "you wrote incorrect arguments\nplease write: circle center.x center.y radius outlinecolor fillcolor\n");
		VerifyCommandHandling("circle 1 1 d2 ffffff 000000", "you wrote incorrect arguments\nplease write: circle center.x center.y radius outlinecolor fillcolor\n");
		VerifyCommandHandling("circle 2a1 1 3 ffffff 000000", "you wrote incorrect arguments\nplease write: circle center.x center.y radius outlinecolor fillcolor\n");
		VerifyCommandHandling("circle 2a1 1 3 ffffff", "you wrote incorrect arguments\nplease write: circle center.x center.y radius outlinecolor fillcolor\n");
		VerifyCommandHandling("circle 1 3", "you wrote incorrect arguments\nplease write: circle center.x center.y radius outlinecolor fillcolor\n");
		VerifyCommandHandling("circle ffffff", "you wrote incorrect arguments\nplease write: circle center.x center.y radius outlinecolor fillcolor\n");
		VerifyCommandHandling("circle", "you wrote incorrect arguments\nplease write: circle center.x center.y radius outlinecolor fillcolor\n");
	}

	// не может добавить круг если цвет контура не в 16-ти ричной системе счисления и его длина меньше или больше 6
	SECTION("cant add circle if outline color is not in the 16-bit number system and its length is less than or greater than 6")
	{
		VerifyCommandHandling("circle 1 2 3 afd32 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 fgFfff 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 gfFfff 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 fFfffg 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 fff99fd 000000", "you wrote incorrect color\ncolor must be hex color\n");
	}

	// не может добавить круг если цвет заливки не в 16-ти ричной системе счисления и его длина меньше или больше 6
	SECTION("cant add circle if fill color is not in the 16-bit number system and its length is less than or greater than 6")
	{
		VerifyCommandHandling("circle 1 2 3 000000 afd32", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 000000 fgFfff", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 000000 gfFfff", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 000000 fFfffg", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 000000 fff99fd", "you wrote incorrect color\ncolor must be hex color\n");
	}

	// не может добавить круг если радиус меньше 0
	SECTION("cant add circle if radius is less than 0")
	{
		VerifyCommandHandling("circle 1 2 -3 ffffff ffffff", "you wrote incorrect radius\nradius less than 0\n");
		VerifyCommandHandling("circle 1 2 -1 ffffff ffffff", "you wrote incorrect radius\nradius less than 0\n");
		VerifyCommandHandling("circle 1 2 -0.1 ffffff ffffff", "you wrote incorrect radius\nradius less than 0\n");
	}

	// может добавить прямоугольник
	SECTION("can add rectangle")
	{
		VerifyCommandHandling("rectangle 1 1 2 2 ffffffff ffffff", "RectangleWasAdded\n");
		VerifyCommandHandling("rectangle 1 1 2 2 ffffff aaffffff", "RectangleWasAdded\n");
		VerifyCommandHandling("rectangle 1 1 2 2 ffffff ffffff", "RectangleWasAdded\n");
		VerifyCommandHandling("rectangle 1 1 2 2 ffffff ffffff", "RectangleWasAdded\n");
		VerifyCommandHandling("rectangle 1 1 2 2 000000 000000", "RectangleWasAdded\n");
		VerifyCommandHandling("rectangle 1 1 2 2 aaaaaa aaaaaa", "RectangleWasAdded\n");
		VerifyCommandHandling("rectangle 1 1 2 2 999999 999999", "RectangleWasAdded\n");
	}

	// не может добавить прямоугольник если параметры не указаны или неправильного типа и возвращает информацию об ошибке
	SECTION("cant add rectangle if the parameters are not specified or wrong type and returns error information")
	{
		VerifyCommandHandling("rectangle 1 d 4 0 ffffff 000000", "you wrote incorrect arguments\nplease write: rectangle lefttop.x lefttop.y rightbottom.x rightbottom.y outlinecolor fillcolor\n");
		VerifyCommandHandling("rectangle 1 1a 4 0 ffffff 000000", "you wrote incorrect arguments\nplease write: rectangle lefttop.x lefttop.y rightbottom.x rightbottom.y outlinecolor fillcolor\n");
		VerifyCommandHandling("rectangle 1 1 d2 0 ffffff 000000", "you wrote incorrect arguments\nplease write: rectangle lefttop.x lefttop.y rightbottom.x rightbottom.y outlinecolor fillcolor\n");
		VerifyCommandHandling("rectangle 2a1 1 3 0 ffffff 000000", "you wrote incorrect arguments\nplease write: rectangle lefttop.x lefttop.y rightbottom.x rightbottom.y outlinecolor fillcolor\n");
		VerifyCommandHandling("rectangle 1 3 9 0", "you wrote incorrect arguments\nplease write: rectangle lefttop.x lefttop.y rightbottom.x rightbottom.y outlinecolor fillcolor\n");
		VerifyCommandHandling("rectangle ffffff", "you wrote incorrect arguments\nplease write: rectangle lefttop.x lefttop.y rightbottom.x rightbottom.y outlinecolor fillcolor\n");
		VerifyCommandHandling("rectangle", "you wrote incorrect arguments\nplease write: rectangle lefttop.x lefttop.y rightbottom.x rightbottom.y outlinecolor fillcolor\n");
	}

	// не может добавить прямоугольник если цвет контура указан неправильно
	SECTION("cant add rectangle if outline color is not in the 16-bit number system and its length is less than or greater than 6")
	{
		VerifyCommandHandling("rectangle 1 2 3 0 afd32 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("rectangle 1 2 3 0 fgFfff 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("rectangle 1 2 3 0 gfFfff 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("rectangle 1 2 3 0 fFfffg 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("rectangle 1 2 3 0 fff99fd 000000", "you wrote incorrect color\ncolor must be hex color\n");
	}

	// не может добавить прямоугольник если цвет заливки указан неправильно
	SECTION("cant add rectangle if fill color is not in the 16-bit number system and its length is less than or greater than 6")
	{
		VerifyCommandHandling("circle 1 2 3 0 000000 afd32", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 0 000000 fgFfff", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 0 000000 gfFfff", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 0 000000 fFfffg", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("circle 1 2 3 0 000000 fff99fd", "you wrote incorrect color\ncolor must be hex color\n");
	}

	// не может добавить прямоугольник если ширина меньше 0
	SECTION("cant add rectangle if width is less than 0")
	{
		VerifyCommandHandling("rectangle 4 2 -1 0 ffffff ffffff", "you wrote incorrect width\nwidth less than 0\n");
		VerifyCommandHandling("rectangle 1 2 -0.1 4 ffffff ffffff", "you wrote incorrect width\nwidth less than 0\n");
		VerifyCommandHandling("rectangle 4 2 -10 4 ffffff ffffff", "you wrote incorrect width\nwidth less than 0\n");
	}

	// не может добавить прямоугольник если высота меньше 0
	SECTION("cant add rectangle if height is less than 0")
	{
		VerifyCommandHandling("rectangle 4 2 2 -1 ffffff ffffff", "you wrote incorrect height\nheight less than 0\n");
		VerifyCommandHandling("rectangle 1 2 2 -0.1 ffffff ffffff", "you wrote incorrect height\nheight less than 0\n");
		VerifyCommandHandling("rectangle 4 2 2 -10 ffffff ffffff", "you wrote incorrect height\nheight less than 0\n");
	}

	// может добавить треугольник
	SECTION("can add triangle")
	{
		VerifyCommandHandling("triangle 0 0 2 2 4 0 ffffffff ffffff", "TriangleWasAdded\n");
		VerifyCommandHandling("triangle 0 0 2 2 4 0 ffffff aaffffff", "TriangleWasAdded\n");
		VerifyCommandHandling("triangle 0 0 2 2 4 0 ffffff ffffff", "TriangleWasAdded\n");
		VerifyCommandHandling("triangle 0 0 2 2 4 0 000000 000000", "TriangleWasAdded\n");
		VerifyCommandHandling("triangle 0 0 2 2 4 0 aaaaaa aaaaaa", "TriangleWasAdded\n");
		VerifyCommandHandling("triangle 0 0 2 2 4 0 999999 999999", "TriangleWasAdded\n");
	}

	// не может добавить треугольник если параметры не указаны или неправильного типа и возвращает информацию об ошибке
	SECTION("cant add triangle if the parameters are not specified or wrong type and returns error information")
	{
		VerifyCommandHandling("triangle 1 d 2 2 4 0 ffffff 000000", "you wrote incorrect arguments\nplease write: vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y outlinecolor fillcolor\n");
		VerifyCommandHandling("triangle 1 1a 2 2 4 0 ffffff 000000", "you wrote incorrect arguments\nplease write: vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y outlinecolor fillcolor\n");
		VerifyCommandHandling("triangle 1 1 d2 0 4 0 ffffff 000000", "you wrote incorrect arguments\nplease write: vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y outlinecolor fillcolor\n");
		VerifyCommandHandling("triangle 2a1 1 3 0 4 0 ffffff 000000", "you wrote incorrect arguments\nplease write: vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y outlinecolor fillcolor\n");
		VerifyCommandHandling("triangle 0 0 2 2 4 0 ", "you wrote incorrect arguments\nplease write: vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y outlinecolor fillcolor\n");
		VerifyCommandHandling("triangle ffffff", "you wrote incorrect arguments\nplease write: vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y outlinecolor fillcolor\n");
		VerifyCommandHandling("triangle", "you wrote incorrect arguments\nplease write: vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y outlinecolor fillcolor\n");
	}

	// не может добавить треугольник если цвет контура указан неправильно
	SECTION("cant add triangle if outline color is not in the 16-bit number system and its length is less than or greater than 6")
	{
		VerifyCommandHandling("rectangle 0 0 2 2 4 0 afd32 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("rectangle 0 0 2 2 4 0 fgFfff 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("rectangle 0 0 2 2 4 0 gfFfff 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("rectangle 0 0 2 2 4 0 fFfffg 000000", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("rectangle 0 0 2 2 4 0 fff99fd 000000", "you wrote incorrect color\ncolor must be hex color\n");
	}

	// не может добавить треугольник если цвет заливки указан неправильно
	SECTION("cant add triangle if fill color is not in the 16-bit number system and its length is less than or greater than 6")
	{
		VerifyCommandHandling("triangle 0 0 2 2 4 0 000000 afd32", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("triangle 0 0 2 2 4 0 000000 fgFfff", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("triangle 0 0 2 2 4 0 000000 gfFfff", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("triangle 0 0 2 2 4 0 000000 fFfffg", "you wrote incorrect color\ncolor must be hex color\n");
		VerifyCommandHandling("triangle 0 0 2 2 4 0 000000 fff99fd", "you wrote incorrect color\ncolor must be hex color\n");
	}
	
	// если массив фигур не пуст
	SECTION("if array of figures is not empty ")
	{
		// может найти фигуру с мин периметром и вывести информацию о ней
		SECTION("can find figure with min perimeter and display information about it")
		{
			VerifyCommandHandling("lineSegment 0 0 2 0 aad32d", "LineSegmentWasAdded\n");
			VerifyCommandHandling("minPerimeter", "minPerimeterShape: perimeter:2.00 area:0.00 outlinecolor:aad32dff startpoint.x:0.00 startpoint.y:0.00 endpoint.x:2.00 endpoint.y:0.00\n");
		}

		// может найти фигуру с мах площадью и вывести информацию о ней
		SECTION("can find figure with max area and display information about it")
		{
			VerifyCommandHandling("lineSegment 0 0 2 0 aad32d", "LineSegmentWasAdded\n");
			VerifyCommandHandling("triangle 0 0 2 2 4 0 000000 ffffff", "TriangleWasAdded\n");
			VerifyCommandHandling("maxArea", "maxAreaShape: perimeter:2.00 area:0.00 outlinecolor:aad32dff startpoint.x:0.00 startpoint.y:0.00 endpoint.x:2.00 endpoint.y:0.00\n");
		}
	}

	// если массив фигур пуст
	SECTION("if array of figures is empty ")
	{
		// при попытке поиска фигуры с мин периметром выводит что массив пуст
		SECTION("when trying to find figure with min perimeter, displays that the array is empty")
		{
			VerifyCommandHandling("minPerimeter", "array of shapes is empty!\n");
		}

		// при попытке поиска фигуры с мах площадью выводит что массив пуст
		SECTION("when trying to find figure with max area, displays that the array is empty")
		{
			VerifyCommandHandling("maxArea", "array of shapes is empty!\n");
		}
	}
};

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

// ���������� �����
TEST_CASE("test shapeController", ShapeControllerFixture)
{
	// �� ����� ������ �������� ���  ����� ����������� �������
	SECTION("shapeController1")
	{
		REQUIRE(!VerifyCommandHandling("line 1, 2, 3, 4 ffffff", ""));
		REQUIRE(!VerifyCommandHandling("circlee 1, 2, 2, 4 000000", ""));
		REQUIRE(!VerifyCommandHandling("triangel 1, 2, 3, 4 aaaaaa", ""));
	}
	
	// ����� �������� �������
	SECTION("shapeController2")
	{
		REQUIRE(VerifyCommandHandling("lineSegment 1, 2, 3, 4 ffffff", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("lineSegment 1, 2, 2, 4 000000", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("lineSegment 1, 2, 3, 4 aaaaaa", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("lineSegment 1, 2, 5, 4 999999", "LineSegmentWasAdded\n"));
	}

	// �� ����� �������� ������� ���� ��������� �� ������� ��� ������������� ����
	SECTION("shapeController3")
	{
		REQUIRE(VerifyCommandHandling("lineSegment 1 d 3 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("lineSegment 1 1 f 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("lineSegment 1 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("lineSegment a 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("lineSegment a 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("lineSegment a 1 3 d", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("lineSegment 1 1 3 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("lineSegment 1 3 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("lineSegment ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("lineSegment", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
	}

	// �� ����� �������� ������� ���� ���� ������ �����������
	SECTION("shapeController4")
	{
		REQUIRE(VerifyCommandHandling("lineSegment 1 2 3 4 asd32", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("lineSegment 1 2 3 4 fgFfff", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("lineSegment 1 2 3 4 fff99fx", "you wrote uncorect color\ncolor must be hex color\n"));
	}

	// ����� �������� ����
	SECTION("shapeController5")
	{
		REQUIRE(VerifyCommandHandling("circle 1, 2, 3, 4 ffffff", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("circle 1, 2, 2, 4 000000", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("circle 1, 2, 3, 4 aaaaaa", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("circle 1, 2, 5, 4 999999", "LineSegmentWasAdded\n"));
	}

	// �� ����� �������� ���� ���� ��������� �� ������� ��� ������������� ����
	SECTION("shapeController6")
	{
		REQUIRE(VerifyCommandHandling("circle 1 d 3 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("circle 1 1 f 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("circle 1 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("circle a 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("circle a 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("circle a 1 3 d", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("circle 1 1 3 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("circle 1 3 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("circle ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("circle", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
	}

	// �� ����� �������� ���� ���� ���� ������� ������ �����������
	SECTION("shapeController7")
	{
		REQUIRE(VerifyCommandHandling("circle 1 2 3 4 asd32", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("circle 1 2 3 4 fgFfff", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("circle 1 2 3 4 fff99fx", "you wrote uncorect color\ncolor must be hex color\n"));
	}

	// �� ����� �������� ���� ���� ���� ������� ������ �����������
	SECTION("shapeController8")
	{
		REQUIRE(VerifyCommandHandling("circle 1 2 3 4 asd32", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("circle 1 2 3 4 fgFfff", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("circle 1 2 3 4 fff99fx", "you wrote uncorect color\ncolor must be hex color\n"));
	}

	// �� ����� �������� ���� ���� ������ ������ 0
	SECTION("shapeController8")
	{
		REQUIRE(VerifyCommandHandling("circle 1 2 3 4 asd32", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("circle 1 2 3 4 fgFfff", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("circle 1 2 3 4 fff99fx", "you wrote uncorect color\ncolor must be hex color\n"));
	}

	// ����� �������� �������������
	SECTION("shapeController5")
	{
		REQUIRE(VerifyCommandHandling("rectangle 1, 2, 3, 4 ffffff", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1, 2, 2, 4 000000", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1, 2, 3, 4 aaaaaa", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1, 2, 5, 4 999999", "LineSegmentWasAdded\n"));
	}

	// �� ����� �������� ������������� ���� ��������� �� ������� ��� ������������� ����
	SECTION("shapeController6")
	{
		REQUIRE(VerifyCommandHandling("rectangle 1 d 3 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1 1 f 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("rectangle a 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("rectangle a 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("rectangle a 1 3 d", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1 1 3 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1 3 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("rectangle ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("rectangle", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
	}

	// �� ����� �������� ������������� ���� ���� ������� ������ �����������
	SECTION("shapeController7")
	{
		REQUIRE(VerifyCommandHandling("rectangle 1 2 3 4 asd32", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1 2 3 4 fgFfff", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1 2 3 4 fff99fx", "you wrote uncorect color\ncolor must be hex color\n"));
	}

	// �� ����� �������� ������������� ���� ���� ������� ������ �����������
	SECTION("shapeController8")
	{
		REQUIRE(VerifyCommandHandling("rectangle 1 2 3 4 asd32", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1 2 3 4 fgFfff", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1 2 3 4 fff99fx", "you wrote uncorect color\ncolor must be hex color\n"));
	}

	// �� ����� �������� ������������� ���� ������� ����� ����� ��������� ������ ��� ���� ������ ������
	SECTION("shapeController8")
	{
		REQUIRE(VerifyCommandHandling("rectangle 1 2 3 4 asd32", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1 2 3 4 fgFfff", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("rectangle 1 2 3 4 fff99fx", "you wrote uncorect color\ncolor must be hex color\n"));
	}

	// ����� �������� �����������
	SECTION("shapeController5")
	{
		REQUIRE(VerifyCommandHandling("triangle 1, 2, 3, 4 ffffff", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("triangle 1, 2, 2, 4 000000", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("triangle 1, 2, 3, 4 aaaaaa", "LineSegmentWasAdded\n"));
		REQUIRE(VerifyCommandHandling("triangle 1, 2, 5, 4 999999", "LineSegmentWasAdded\n"));
	}

	// �� ����� �������� ����������� ���� ��������� �� ������� ��� ������������� ����
	SECTION("shapeController6")
	{
		REQUIRE(VerifyCommandHandling("triangle 1 d 3 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("triangle 1 1 f 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("triangle 1 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("triangle a 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("triangle a 1 3 d ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("triangle a 1 3 d", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("triangle 1 1 3 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("triangle 1 3 4 ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("triangle ffffff", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
		REQUIRE(VerifyCommandHandling("triangle", "you wrote uncorrect arguments\nplease, write lineSegment start.x start.y end.x end.y outlinecolor\n"));
	}

	// �� ����� �������� ����������� ���� ���� ������� ������ �����������
	SECTION("shapeController7")
	{
		REQUIRE(VerifyCommandHandling("triangle 1 2 3 4 asd32", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("triangle 1 2 3 4 fgFfff", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("triangle 1 2 3 4 fff99fx", "you wrote uncorect color\ncolor must be hex color\n"));
	}

	// �� ����� �������� ����������� ���� ���� ������� ������ �����������
	SECTION("shapeController8")
	{
		REQUIRE(VerifyCommandHandling("triangle 1 2 3 4 asd32", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("triangle 1 2 3 4 fgFfff", "you wrote uncorect color\ncolor must be hex color\n"));
		REQUIRE(VerifyCommandHandling("triangle 1 2 3 4 fff99fx", "you wrote uncorect color\ncolor must be hex color\n"));
	}
	
	// ���� ������ ����� �� ����
	SECTION("shapeController8")
	{
		// ����� ����� ������ � ��� ���������� � ������� ���������� � ���
		SECTION("shapeController8")
		{
			REQUIRE(VerifyCommandHandling("lineSegment 0 0 2 0 asd32d", "LineSegmentWasAdded\n"));
			REQUIRE(VerifyCommandHandling("minPerimeter", "minPerimeterShape: perimeter:2.00 area : 0.00 outlinecolor : asd32d startpoint.x : 0.00 startpoint.y : 0.00 endpoint.x : 2.00 endpoint.y : 0.00\n"));
		}

		// ����� ����� ������ � ��� �������� � ������� ���������� � ���
		SECTION("shapeController8")
		{
			REQUIRE(VerifyCommandHandling("lineSegment 0 0 2 0 asd32d", "LineSegmentWasAdded\n"));
			REQUIRE(VerifyCommandHandling("triangle 0 0 2 2 4 0 000000 ffffff\n"));
			REQUIRE(VerifyCommandHandling("maxArea", "maxAreaShape: perimeter:9.66 area:4.00 fillcolor:ffffff outlinecolor:000000 vertex1.x:0.00 vertex1.y:0.00 vertex2.x:2.00 vertex2.y:2.00 vertex3.x:4.00 vertex3.y:0.00\n"));
		}
	}

	// ���� ������ ����� ����
	SECTION("shapeController8")
	{
		// ��� ������� ������ ������ � ��� ���������� ������� ��� ������ ����
		SECTION("shapeController8")
		{
			REQUIRE(VerifyCommandHandling("minPerimeter", "array of shapes is empty!\n"));
		}

		// ������� ������ ������ � ��� �������� ������� ������� ��� ������ ����
		SECTION("shapeController8")
		{
			REQUIRE(VerifyCommandHandling("maxArea", "array of shapes is empty!\n"));
		}
	}
	
};
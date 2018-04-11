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

	void VerifyCommandHandling(const std::string& command, const boost::optional<int>& expectedChannel, const std::string& expectedOutput)
	{
		output = std::stringstream();
		input = std::stringstream();
		REQUIRE(input << command);
		REQUIRE(remoteControl.HandleCommand());
		REQUIRE(tv.IsTurnedOn(), expectedChannel.is_initialized());
		REQUIRE(tv.GetChannel(), expectedChannel.get_value_or(0));
		REQUIRE(input.eof());
		REQUIRE(output.str(), expectedOutput);
	}
}

// контроллер фигур
TEST_CASE("test shapeController", ShapeControllerFixture)
{
	// может возвращать свою начальную точку
	SECTION("shapeController1")
	{
		REQUIRE();
	}
};
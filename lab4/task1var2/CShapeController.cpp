#include "stdafx.h"
#include "CShapeController.h"

const std::string COMMAND_ADD_CIRCLE = "circle";
const std::string COMMAND_ADD_RECTANGLE = "rectangle";
const std::string COMMAND_ADD_TRIANGLE = "triangle";
const std::string COMMAND_ADD_LINE_SEGMENT = "lineSegment";
const std::string COMMAND_GET_MIN_PERIMETER = "minPerimeter";
const std::string COMMAND_GET_MAX_AREA = "maxArea";

CShapeController::CShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({ { COMMAND_ADD_CIRCLE, bind(&CShapeController::AddCircle, this, std::placeholders::_1) },
					{ COMMAND_ADD_RECTANGLE, bind(&CShapeController::AddRectangle, this, std::placeholders::_1) },
					{ COMMAND_ADD_TRIANGLE, bind(&CShapeController::AddTriangle, this, std::placeholders::_1) },
					{ COMMAND_ADD_LINE_SEGMENT, bind(&CShapeController::AddLineSegment, this, std::placeholders::_1) },
					{ COMMAND_GET_MIN_PERIMETER, bind(&CShapeController::GetShapeWithMinPerimeter, this, std::placeholders::_1) },
					{ COMMAND_GET_MAX_AREA, bind(&CShapeController::GetShapeWithMaxArea, this, std::placeholders::_1) } })
{
}

CShapeController::~CShapeController()
{
}

bool CShapeController::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

std::shared_ptr<IShape> CShapeController::GetShapeWithMinPerimeter(std::istream& args) const
{

}
std::shared_ptr<IShape> CShapeController::GetShapeWithMaxArea(std::istream& args) const
{
}

std::shared_ptr<IShape> CShapeController::AddCircle(std::istream& args)
{
}

std::shared_ptr<IShape> CShapeController::AddLineSegment(std::istream& args)
{
}

std::shared_ptr<IShape> CShapeController::AddRectangle(std::istream& args)
{
}

std::shared_ptr<IShape> CShapeController::AddTriangle(std::istream& args)
{
}

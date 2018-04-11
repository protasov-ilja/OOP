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

bool CShapeController::GetShapeWithMinPerimeter(std::istream& args) const
{
	if (m_arrayOfShapes.empty())
	{
		return false;
	}

	auto GetMinShapePtr = [](const std::shared_ptr<IShape>& a, const std::shared_ptr<IShape>& b) {
		return a->GetPerimeter() < b->GetPerimeter();
	};
	auto shapeWithMinPerimeter = *std::min_element(m_arrayOfShapes.begin(), m_arrayOfShapes.end(), GetMinShapePtr);
	m_output << "minPerimeterShape";
	m_output << shapeWithMinPerimeter->ToString() << std::endl;
	return true;
}

bool CShapeController::GetShapeWithMaxArea(std::istream& args) const
{
	if (m_arrayOfShapes.empty())
	{
		return false;
	}

	auto GetMaxShapePtr = [](const std::shared_ptr<IShape>& a, const std::shared_ptr<IShape>& b) {
		return a->GetPerimeter() > b->GetPerimeter();
	};
	auto shapeWithMaxArea = *std::min_element(m_arrayOfShapes.begin(), m_arrayOfShapes.end(), GetMaxShapePtr);
	m_output << "maxAreaShape";
	m_output << shapeWithMaxArea->ToString() << std::endl;
	return true;
}

bool CShapeController::AddCircle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint center(0, 0);
	double radius;
	if (args >> center.x >> center.y >> radius >> fillColor >> outlineColor)
	{

		m_output << "AddCircle\n";
		return true;
	}

	return false;
}

bool CShapeController::AddLineSegment(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint center;
	double radius;
	if (args >> center.x >> center.y >> radius >> fillColor >> outlineColor)
	{
		m_arrayOfShapes.push_back();
		m_output << "AddLineSegment\n";
		return true;
	}

	return false;
}

bool CShapeController::AddRectangle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint center(0, 0);
	double radius;
	if (args >> center.x >> center.y >> radius >> fillColor >> outlineColor)
	{

		m_output << "AddRectangle\n";
		return true;
	}

	return false;
}

bool CShapeController::AddTriangle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint center(0, 0);
	double radius;
	if (args >> center.x >> center.y >> radius >> fillColor >> outlineColor)
	{
		m_output << "AddTriangle\n";
		return true;
	}

	return false;
}

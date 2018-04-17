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

bool CShapeController::IsColor(const std::string& color) const
{
	std::regex regex(R"(^([A-Fa-f0-9]){6}$)");
	std::smatch result;
	if (!std::regex_match(color, result, regex))
	{
		return false;
	}

	if (result[1].str().empty()) {
		return false;
	}

	return true;
}

bool CShapeController::GetShapeWithMinPerimeter(std::istream& args) const
{
	if (m_arrayOfShapes.empty())
	{
		m_output << "array of shapes is empty!" << std::endl;
		return true;
	}

	auto GetMinShapePtr = [](const std::shared_ptr<IShape>& a, const std::shared_ptr<IShape>& b) {
		return a->GetPerimeter() < b->GetPerimeter();
	};
	auto shapeWithMinPerimeter = *std::min_element(m_arrayOfShapes.begin(), m_arrayOfShapes.end(), GetMinShapePtr);
	m_output << "minPerimeterShape: ";
	m_output << shapeWithMinPerimeter->ToString();
	return true;
}

bool CShapeController::GetShapeWithMaxArea(std::istream& args) const
{
	if (m_arrayOfShapes.empty())
	{
		m_output << "array of shapes is empty!" << std::endl;
		return true;
	}

	auto GetMaxShapePtr = [](const std::shared_ptr<IShape>& a, const std::shared_ptr<IShape>& b) {
		return a->GetPerimeter() > b->GetPerimeter();
	};
	auto shapeWithMaxArea = *std::max_element(m_arrayOfShapes.begin(), m_arrayOfShapes.end(), GetMaxShapePtr);
	m_output << "maxAreaShape: ";
	m_output << shapeWithMaxArea->ToString();
	return true;
}

bool CShapeController::AddCircle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint center;
	double radius;
	if (args >> center.x >> center.y >> radius >> outlineColor >> fillColor)
	{
		if (!(IsColor(outlineColor) && IsColor(fillColor)))
		{
			m_output << "you wrote incorrect color\ncolor must be hex color" << std::endl;
			return true;
		}

		if (radius < 0)
		{
			m_output << "you wrote incorrect radius\nradius less than 0" << std::endl;
			return true;
		}
		
		std::shared_ptr<IShape> circlePtr(new CCircle(center, radius, outlineColor, fillColor));
		m_arrayOfShapes.push_back(std::move(circlePtr));
		m_output << "CircleWasAdded\n";
	}
	else
	{
		m_output << "you wrote incorrect arguments\n" 
				 << "please write: circle center.x center.y radius outlinecolor fillcolor" 
				 << std::endl;
	}

	return true;
}

bool CShapeController::AddLineSegment(std::istream& args)
{
	std::string outlineColor;
	CPoint start;
	CPoint end;
	if (args >> start.x >> start.y >> end.x >> end.y >> outlineColor)
	{
		if (!IsColor(outlineColor))
		{
			m_output << "you wrote incorrect color\ncolor must be hex color" << std::endl;
			return true;
		}

		std::shared_ptr<IShape> lineSegmentPtr(new CLineSegment(start, end, outlineColor));
		m_arrayOfShapes.push_back(std::move(lineSegmentPtr));
		m_output << "LineSegmentWasAdded\n";
	}
	else
	{
		m_output << "you wrote incorrect arguments\n"
				 << "please write: lineSegment start.x start.y end.x end.y outlinecolor"
				 << std::endl;
	}

	return true;
}

bool CShapeController::AddRectangle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint leftTop;
	CPoint rightBottom;
	if (args >> leftTop.x >> leftTop.y >> rightBottom.x >> rightBottom.y >> outlineColor >> fillColor)
	{
		if (!(IsColor(outlineColor) && IsColor(fillColor)))
		{
			m_output << "you wrote incorrect color\ncolor must be hex color" << std::endl;
			return true;
		}

		if ((leftTop.x > rightBottom.x) || (leftTop.y < rightBottom.y))
		{
			m_output << "you wrote incorrect lefttop or rightbottom points\n leftTop.x < rightBottom.x and leftTop.y > rightBottom.y" << std::endl;
			return true;
		}

		std::shared_ptr<IShape> rectanglePtr(new CRectangle(leftTop, rightBottom, outlineColor, fillColor));
		m_arrayOfShapes.push_back(std::move(rectanglePtr));
		m_output << "RectangleWasAdded\n";
	}
	else
	{
		m_output << "you wrote incorrect arguments\n"
				 << "please write: rectangle lefttop.x lefttop.y rightbottom.x rightbottom.y outlinecolor fillcolor"
				 << std::endl;
	}

	return true;
}

bool CShapeController::AddTriangle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;
	if (args >> vertex1.x >> vertex1.y >> vertex2.x >> vertex2.y >> vertex3.x >> vertex3.y >> outlineColor >> fillColor)
	{
		if (!(IsColor(outlineColor) && IsColor(fillColor)))
		{
			m_output << "you wrote incorrect color\ncolor must be hex color" << std::endl;
			return true;
		}

		std::shared_ptr<IShape> trianglePtr(new CTriangle(vertex1, vertex2, vertex3, outlineColor, fillColor));
		m_arrayOfShapes.push_back(std::move(trianglePtr));
		m_output << "TriangleWasAdded\n";
	}
	else
	{
		m_output << "you wrote incorrect arguments\n"
				 << "please write: vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y outlinecolor fillcolor"
				 << std::endl;
	}

	return true;
}

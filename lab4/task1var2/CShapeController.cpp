#include "stdafx.h"
#include "CShapeController.h"
#include "CCanvas.h"
#include "Config.h"

CShapeController::CShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({ { COMMAND_ADD_CIRCLE, bind(&CShapeController::AddCircle, this, std::placeholders::_1) },
		  { COMMAND_ADD_RECTANGLE, bind(&CShapeController::AddRectangle, this, std::placeholders::_1) },
		  { COMMAND_ADD_TRIANGLE, bind(&CShapeController::AddTriangle, this, std::placeholders::_1) },
		  { COMMAND_ADD_LINE_SEGMENT, bind(&CShapeController::AddLineSegment, this, std::placeholders::_1) },
		  { COMMAND_GET_MIN_PERIMETER, bind(&CShapeController::GetShapeWithMinPerimeter, this, std::placeholders::_1) },
		  { COMMAND_GET_MAX_AREA, bind(&CShapeController::GetShapeWithMaxArea, this, std::placeholders::_1) },
		  { COMMAND_DRAW_ALL, bind(&CShapeController::DrawShapes, this, std::placeholders::_1) } })
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
		it->second(strm);
		return true;
	}

	return false;
}

bool CShapeController::IsColor(const std::string& color) const
{
	std::regex regex(R"(^([A-Fa-f0-9]){6}(([A-Fa-f0-9]){2})?$)");
	std::smatch result;
	if (!std::regex_match(color, result, regex))
	{
		return false;
	}

	if (result[1].str().empty())
	{
		return false;
	}

	return true;
}

void CShapeController::AddAlphaToColorIfNeeded(std::string& color)
{
	if (color.length() == 6)
	{
		color += "ff";
	}
}

void CShapeController::DrawShapes(std::istream&)
{
	if (m_arrayOfShapes.empty())
	{
		m_output << "array of shapes is empty!" << std::endl;
		return;
	}

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Canvas");
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		for (auto shape : m_arrayOfShapes)
		{
			shape->Draw(canvas);
		}

		window.display();
	}
}

void CShapeController::GetShapeWithMinPerimeter(std::istream&) const
{
	if (m_arrayOfShapes.empty())
	{
		m_output << "array of shapes is empty!" << std::endl;
		return;
	}

	auto shapePerimeterComporator = [](const std::shared_ptr<IShape>& a, const std::shared_ptr<IShape>& b) {
		return a->GetPerimeter() < b->GetPerimeter();
	};
	auto shapeWithMinPerimeter = *std::min_element(m_arrayOfShapes.begin(), m_arrayOfShapes.end(), shapePerimeterComporator);
	m_output << "minPerimeterShape: ";
	m_output << shapeWithMinPerimeter->ToString();
	return;
}

void CShapeController::GetShapeWithMaxArea(std::istream&) const
{
	if (m_arrayOfShapes.empty())
	{
		m_output << "array of shapes is empty!" << std::endl;
		return;
	}

	auto shapeAreaComporator = [](const std::shared_ptr<IShape>& a, const std::shared_ptr<IShape>& b) {
		return a->GetPerimeter() > b->GetPerimeter();
	};
	auto shapeWithMaxArea = *std::max_element(m_arrayOfShapes.begin(), m_arrayOfShapes.end(), shapeAreaComporator);
	m_output << "maxAreaShape: ";
	m_output << shapeWithMaxArea->ToString();
	return;
}

void CShapeController::AddCircle(std::istream& args)
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
			return;
		}

		if (radius < 0)
		{
			m_output << "you wrote incorrect radius\nradius less than 0" << std::endl;
			return;
		}

		AddAlphaToColorIfNeeded(outlineColor);
		AddAlphaToColorIfNeeded(fillColor);
		m_arrayOfShapes.push_back(std::make_shared<CCircle>(center, radius, outlineColor, fillColor));
		m_output << "CircleWasAdded\n";
	}
	else
	{
		m_output << "you wrote incorrect arguments\n"
				 << "please write: circle center.x center.y radius outlinecolor fillcolor"
				 << std::endl;
	}

	return;
}

void CShapeController::AddLineSegment(std::istream& args)
{
	std::string outlineColor;
	CPoint start;
	CPoint end;
	if (args >> start.x >> start.y >> end.x >> end.y >> outlineColor)
	{
		if (!IsColor(outlineColor))
		{
			m_output << "you wrote incorrect color\ncolor must be hex color" << std::endl;
			return;
		}

		AddAlphaToColorIfNeeded(outlineColor);
		m_arrayOfShapes.push_back(std::make_shared<CLineSegment>(start, end, outlineColor));
		m_output << "LineSegmentWasAdded\n";
	}
	else
	{
		m_output << "you wrote incorrect arguments\n"
				 << "please write: lineSegment start.x start.y end.x end.y outlinecolor"
				 << std::endl;
	}

	return;
}

void CShapeController::AddRectangle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint leftTop;
	double width;
	double height;
	if (args >> leftTop.x >> leftTop.y >> width >> height >> outlineColor >> fillColor)
	{
		if (!(IsColor(outlineColor) && IsColor(fillColor)))
		{
			m_output << "you wrote incorrect color\ncolor must be hex color" << std::endl;
			return;
		}

		AddAlphaToColorIfNeeded(outlineColor);
		AddAlphaToColorIfNeeded(fillColor);
		if (width < 0)
		{
			m_output << "you wrote incorrect width\nwidth less than 0" << std::endl;
			return;
		}

		if (height < 0)
		{
			m_output << "you wrote incorrect height\nheight less than 0" << std::endl;
			return;
		}

		m_arrayOfShapes.push_back(std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor));
		m_output << "RectangleWasAdded\n";
	}
	else
	{
		m_output << "you wrote incorrect arguments\n"
				 << "please write: rectangle lefttop.x lefttop.y rightbottom.x rightbottom.y outlinecolor fillcolor"
				 << std::endl;
	}

	return;
}

void CShapeController::AddTriangle(std::istream& args)
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
			return;
		}

		AddAlphaToColorIfNeeded(outlineColor);
		AddAlphaToColorIfNeeded(fillColor);
		m_arrayOfShapes.push_back(std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));
		m_output << "TriangleWasAdded\n";
	}
	else
	{
		m_output << "you wrote incorrect arguments\n"
				 << "please write: vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y outlinecolor fillcolor"
				 << std::endl;
	}

	return;
}

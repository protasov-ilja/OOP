#pragma once
#include "IShape.h"
#include "CPoint.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"

class CShapeController
{
public:
	CShapeController() = default;
	CShapeController(std::istream& input, std::ostream& output);
	~CShapeController() = default;
	bool HandleCommand();

private:
	typedef std::map<std::string, std::function<void(std::istream& args)>> ActionMap;

	void GetShapeWithMinPerimeter(std::istream& args) const;
	void GetShapeWithMaxArea(std::istream& args) const;
	void AddCircle(std::istream& args);
	void AddLineSegment(std::istream& args);
	void AddRectangle(std::istream& args);
	void AddTriangle(std::istream& args);
	bool IsColor(const std::string& color) const;

	std::vector<std::shared_ptr<IShape>> m_arrayOfShapes;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
};

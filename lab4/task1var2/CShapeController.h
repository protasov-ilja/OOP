#pragma once
#include "IShape.h"
#include <algorithm>
#include <boost/noncopyable.hpp>
#include <functional>
#include <map>
#include <memory>
#include <vector>

class CShapeController
{
public:
	CShapeController(std::istream& input, std::ostream& output);
	~CShapeController();
	bool HandleCommand();

private:
	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;

	bool GetShapeWithMinPerimeter(std::istream& args) const;
	bool GetShapeWithMaxArea(std::istream& args) const;
	bool AddCircle(std::istream& args);
	bool AddLineSegment(std::istream& args);
	bool AddRectangle(std::istream& args);
	bool AddTriangle(std::istream& args);

	std::vector<std::shared_ptr<IShape>> m_arrayOfShapes;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
};

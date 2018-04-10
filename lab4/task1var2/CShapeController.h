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

	std::shared_ptr<IShape> GetShapeWithMinPerimeter(std::istream& args) const;
	std::shared_ptr<IShape> GetShapeWithMaxArea(std::istream& args) const;
	std::shared_ptr<IShape> AddCircle(std::istream& args);
	std::shared_ptr<IShape> AddLineSegment(std::istream& args);
	std::shared_ptr<IShape> AddRectangle(std::istream& args);
	std::shared_ptr<IShape> AddTriangle(std::istream& args);

	std::vector<std::shared_ptr<IShape>> m_arrayOfShapes;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
};

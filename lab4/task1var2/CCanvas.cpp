#include "stdafx.h"
#include "CCanvas.h"
#include "Config.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	sf::Vertex points[] = {
		sf::Vertex(sf::Vector2f(
					   static_cast<float>(from.x),
					   static_cast<float>(from.y)),
			sf::Color(sf::Uint32(lineColor))),
		sf::Vertex(sf::Vector2f(
					   static_cast<float>(to.x),
					   static_cast<float>(to.y)),
			sf::Color(sf::Uint32(lineColor)))
	};

	m_window.draw(points, THICKNESS, sf::Lines);
}
void CCanvas::FillPolygon(Points points, uint32_t fillColor)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	polygon.setFillColor(sf::Color(sf::Uint32(fillColor)));
	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
	}

	m_window.draw(polygon);
}
void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(sf::Vector2f(
		static_cast<float>(center.x),
		static_cast<float>(center.y)));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(THICKNESS);
	circle.setOutlineColor(sf::Color(sf::Uint32(lineColor)));
	m_window.draw(circle);
}
void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(sf::Vector2f(
		static_cast<float>(center.x),
		static_cast<float>(center.y)));
	circle.setFillColor(sf::Color(sf::Uint32(fillColor)));
	m_window.draw(circle);
}

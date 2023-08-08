#include "ScoreBoost.h"

ScoreBoost::ScoreBoost(const sf::Vector2f& position)
{
	shape.setSize(sf::Vector2f(30.f, 30.f));
	shape.setPosition(position);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(5.f);
	shape.setOutlineColor(sf::Color::Black);
}

void ScoreBoost::draw(sf::RenderTarget& window)
{
	window.draw(shape);
}

sf::Shape& ScoreBoost::getShape()
{
	return shape;
}

#include "HealPack.h"

HealPack::HealPack(const sf::Vector2f& position)
{
	shape.setSize(sf::Vector2f(30.f, 30.f));
	shape.setPosition(position);
	shape.setFillColor(sf::Color::Green);
	shape.setOutlineThickness(5.f);
	shape.setOutlineColor(sf::Color::Black);
}

void HealPack::draw(sf::RenderTarget& window)
{
	window.draw(shape);
}

sf::Shape& HealPack::getShape()
{
	return shape;
}

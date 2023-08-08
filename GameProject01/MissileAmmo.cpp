#include "MissileAmmo.h"

MissileAmmo::MissileAmmo(const sf::Vector2f& position)
{
	shape.setSize(sf::Vector2f(30.f, 30.f));
	shape.setPosition(position);
	shape.setFillColor(sf::Color::Magenta);
	shape.setOutlineThickness(5.f);
	shape.setOutlineColor(sf::Color::Black);
}

void MissileAmmo::draw(sf::RenderTarget& window)
{
	window.draw(shape);
}

sf::Shape& MissileAmmo::getShape()
{
	return shape;
}

#include "Shotgun.h"


const sf::RectangleShape& Shotgun::getShape() const
{
	return shape;
}

void Shotgun::update()
{

}

void Shotgun::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

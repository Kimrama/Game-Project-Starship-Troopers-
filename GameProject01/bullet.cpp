#include "Bullet.h"


const sf::RectangleShape& Bullet::getShape() const
{
	return shape;
}

void Bullet::update()
{

}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

sf::Shape& Bullet::getShape()
{
	return shape;
}

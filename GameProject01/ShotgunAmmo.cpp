#include "ShotgunAmmo.h"

ShotgunAmmo::ShotgunAmmo(const sf::Vector2f& position)
{
	//shotgunTexture.loadFromFile("D:/ConsoleApplication1/sprite/slime.png");
	//spriteShotgun.setTexture(textureShotgun);
	//spriteShotgun.setScale(0.8, 0.8);
	//sprite.setOrigin(static_cast<float>(textureShotgun.getSize().x) / 2, static_cast<float>(textureShotgun.getSize().y / 2));
	//spriteShotgun.setPosition(position);
	shape.setSize(sf::Vector2f(30.f, 30.f));
	shape.setPosition(position);
	shape.setFillColor(sf::Color::Yellow);
	shape.setOutlineThickness(5.f);
	shape.setOutlineColor(sf::Color::Black);
	//shape.setTexture(&shotgunTexture);
}

void ShotgunAmmo::draw(sf::RenderTarget& window)
{

	window.draw(shape);
}

sf::Shape& ShotgunAmmo::getShape()
{
	return shape;
}


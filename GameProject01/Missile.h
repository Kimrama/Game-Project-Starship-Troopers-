#pragma once
#include <SFML\Graphics.hpp>
class Missile
{
public:
	sf::RectangleShape shape;
	sf::Vector2f currVelocity;
	float maxSpeed;

	Missile()
		:currVelocity(0.f, 0.f), maxSpeed(12.f)
	{
		this->shape.setFillColor(sf::Color::Magenta);
		this->shape.setSize(sf::Vector2f(28.f, 18.f));
	};

	void update();
	void render(sf::RenderTarget& target);
	sf::Shape& getShape();

};


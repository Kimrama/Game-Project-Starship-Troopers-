#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	sf::RectangleShape shape;
	sf::Vector2f currVelocity;
	float maxSpeed;
	const sf::RectangleShape& getShape() const;


	Bullet()
		:currVelocity(0.f, 0.f), maxSpeed(30.f)
	{
		this->shape.setFillColor(sf::Color::Red);
		this->shape.setSize(sf::Vector2f(20.f, 9.f));
	};

	void update();
	void render(sf::RenderTarget& target);
	sf::Shape& getShape();

};

#endif // BULLET_H


#include <SFML/Graphics.hpp>

class Shotgun
{
public:
	sf::RectangleShape shape;
	sf::Vector2f currVelocity;
	float maxSpeed;
	const sf::RectangleShape& getShape() const;

	Shotgun()
		:currVelocity(0.f, 0.f), maxSpeed(30.f)
	{
		this->shape.setFillColor(sf::Color::Yellow);
		this->shape.setSize(sf::Vector2f(20.f, 9.f));
	};

	void update();
	void render(sf::RenderTarget& target);
};



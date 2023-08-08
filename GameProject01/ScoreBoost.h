#pragma once
#include <SFML\Graphics.hpp>
class ScoreBoost
{
public:
	ScoreBoost(const sf::Vector2f& position);
	void draw(sf::RenderTarget& window);
	sf::Shape& getShape();


private:

	sf::RectangleShape shape;
};


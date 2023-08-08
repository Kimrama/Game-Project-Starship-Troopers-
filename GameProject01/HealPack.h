#pragma once
#include <SFML\Graphics.hpp>
class HealPack
{
public:

	HealPack(const sf::Vector2f& position);
	void draw(sf::RenderTarget& window);
	sf::Shape& getShape();


private:
	sf::Texture shotgunTexture;

	sf::RectangleShape shape;
};


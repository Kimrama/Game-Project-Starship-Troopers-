#pragma once
#include <SFML\Graphics.hpp>
class ShotgunAmmo
{
public:
	ShotgunAmmo(const sf::Vector2f& position);
	void draw(sf::RenderTarget& window);
	sf::Shape& getShape();


private:
	sf::Texture shotgunTexture;

	sf::RectangleShape shape;
};


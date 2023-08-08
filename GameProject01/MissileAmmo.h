#pragma once
#include <SFML\Graphics.hpp>
class MissileAmmo
{
public:
	MissileAmmo(const sf::Vector2f& position);
	void draw(sf::RenderTarget& window);
	sf::Shape& getShape();


private:
	sf::Texture shotgunTexture;

	sf::RectangleShape shape;
};


#pragma once
#include <SFML/Graphics.hpp>
class Playeranimation
{
public:

	Playeranimation(sf::Texture* texture, sf::Vector2u imageCount, float switcTime);
	sf::IntRect uvRect;

	void update(int row, float deltaTime, bool faceRight);

private:
	sf::Vector2u imageCount;
	sf::Vector2u currenImage;

	//control speed image
	float totalTime;
	float switchTime;



};


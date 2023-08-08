#include "Playeranimation.h"
#include <iostream>

Playeranimation::Playeranimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{

	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currenImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

}

void Playeranimation::update(int row, float deltaTime, bool faceRight)
{
	currenImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currenImage.x++;
		//std::cout << "time  " << deltaTime << std::endl;
		if (currenImage.x >= 2)
		{
			currenImage.x = 0;
		}
	}

	uvRect.top = currenImage.y * uvRect.height;
	if (faceRight)
	{
		uvRect.left = currenImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currenImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}



}

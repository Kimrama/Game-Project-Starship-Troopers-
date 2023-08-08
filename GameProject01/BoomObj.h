#pragma once
#include <SFML/Graphics.hpp>
class BoomObj
{
public:
    BoomObj(const sf::Vector2f& position);

    void draw(sf::RenderWindow& window);

    void boomAnimation(float deltatime);
    sf::IntRect frame;


    sf::Sprite& getSprite();
private:
    sf::Sprite sprite;
    sf::RectangleShape body;

    sf::Texture texture;
    float totaltime;

};


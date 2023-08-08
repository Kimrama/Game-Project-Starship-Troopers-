#include "BoomObj.h"

BoomObj::BoomObj(const sf::Vector2f& position)
{
    texture.loadFromFile("D:/GameProject01/GameProject01/sprite/Explosion 2 SpriteSheet.png");

    sprite.setScale(8, 8);
    sprite.setOrigin(24.f, 24.f);
    sprite.setPosition(position);
    frame = sf::IntRect(0, 0, 48, 48);
    sprite.setTextureRect(frame);
    totaltime = 0;
}

void BoomObj::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void BoomObj::boomAnimation(float deltatime)
{
    totaltime += deltatime;
    sprite.setTexture(texture);
    frame = sf::IntRect(0, 0, 48, 48);

    if (totaltime > 0.2f) {
        if (frame.left == 48 * 18) {
            frame.left = 0;
        }
        else {
            frame.left += 48;
        }
        totaltime = 0;
    }
    sprite.setTextureRect(frame);
}

sf::Sprite& BoomObj::getSprite()
{
    return sprite;
}

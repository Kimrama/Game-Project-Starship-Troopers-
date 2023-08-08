#include "Enemy2.h"
#include <SFML/Graphics.hpp>
#include <iostream>



Enemy2::Enemy2(const sf::Vector2f& position)
    : maxHP(5), currentHP(5), dead(false)
{

    if (!texture.loadFromFile("D:/GameProject01/GameProject01/sprite/Robots/Spider1.png")) {
        std::cerr << "Error loading texture monster" << std::endl;
        return;
    }
    sprite.setScale(0.6f, 0.6f);
    sprite.setOrigin(0.f, 0.f);
    sprite.setPosition(position);
    frame = sf::IntRect(0, 0, 80, 80);
    sprite.setTextureRect(frame);
    totaltime = 0;
}

void Enemy2::update(const sf::FloatRect& playerBounds) {

    if (sprite.getGlobalBounds().intersects(playerBounds)) {
        dead = true;
        //takeDamage(10);
    }
}

void Enemy2::takeDamage(int damage) {
    currentHP -= damage;


    if (currentHP <= 0) {
        dead = true;
    }
}

bool Enemy2::colWithPlayer(const sf::FloatRect& playerBounds) {
    return sprite.getGlobalBounds().intersects(playerBounds);
}

bool Enemy2::isDead() {
    return dead;
}

void Enemy2::draw(sf::RenderWindow& window) {
    //sprite.setTexture(texture);
    window.draw(sprite);
}

void Enemy2::moveToPlayer(const sf::Vector2f& playerPosition, float speed, float deltatime) {
    sf::Vector2f direction = playerPosition - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;

    sprite.move(direction * speed);
    sprite.setTexture(texture);

    frame = sf::IntRect(0, 0, 80, 80);
    totaltime += deltatime;

    if (totaltime > 0.2f) {
        if (frame.left == 320) {
            frame.left = 0;
        }
        else {
            frame.left += 80;
        }
        totaltime = 0;
    }

    if (sprite.getPosition().x > playerPosition.x) {

        sprite.setScale(-0.6f, 0.6f);
    }
    else {

        sprite.setScale(0.6f, 0.6f);
    }
    sprite.setTextureRect(frame);

}


sf::Sprite& Enemy2::getSprite()
{
    return sprite;
}


#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"


Enemy::Enemy(const sf::Vector2f& position)
    : maxHP(2), currentHP(2), dead(false)
{

    if (!texture.loadFromFile("./sprite/Robots/Centipede3.png")) {
        std::cerr << "Error loading texture monster" << std::endl;
        return;
    }
    sprite.setScale(0.5, 0.5);
    sprite.setOrigin(0.f, 0.f);
    sprite.setPosition(position);
    frame = sf::IntRect(0, 0, 80, 80);
    sprite.setTextureRect(frame);
    totaltime = 0;
}

void Enemy::update(const sf::FloatRect& playerBounds) {

    if (sprite.getGlobalBounds().intersects(playerBounds)) {
        dead = true;
        //takeDamage(10);
    }
}

void Enemy::takeDamage(int damage) {
    currentHP -= damage;


    if (currentHP <= 0) {
        dead = true;
    }
}

bool Enemy::colWithPlayer(const sf::FloatRect& playerBounds) {
    return sprite.getGlobalBounds().intersects(playerBounds);
}

bool Enemy::colWithBullet(const sf::FloatRect& bulletBounds)
{
    return sprite.getGlobalBounds().intersects(bulletBounds);
}

bool Enemy::isDead() {
    return dead;
}

void Enemy::draw(sf::RenderWindow& window) {
    //sprite.setTexture(texture);
    window.draw(sprite);
}

void Enemy::moveToPlayer(const sf::Vector2f& playerPosition, float speed, float deltatime) {
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

        sprite.setScale(-0.5f, 0.5f);
    }
    else {

        sprite.setScale(0.5f, 0.5f);
    }
    sprite.setTextureRect(frame);

}


sf::Sprite& Enemy::getSprite()
{
    return sprite;
}


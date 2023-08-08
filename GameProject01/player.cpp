#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"

player::player(sf::Texture* texture, const sf::Vector2f& position, sf::Vector2u imageCount, float switcTime, float speed)
    :playeranimation(texture, imageCount, switcTime)
{
    /*
    sprite.setTexture(texture);
    sprite.setScale(0.3f, 0.3f);
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    */
    this->speed = speed;
    row = 0;
    faceRight = true;

    body.setSize(sf::Vector2f(50.f, 50.f));
    body.setPosition(position);
    body.setTexture(texture);

    level = 1;
    max_HP = 100;
    HP = max_HP;

}


void player::draw(sf::RenderWindow& window) {
    window.draw(body);
}

const sf::RectangleShape& player::getBody() const
{
    return body;
}

int player::getMaxHP() {
    return max_HP;
}

int player::getHP() {
    return HP;
}



sf::Vector2f player::getPosition() const
{
    return body.getPosition();
}

void player::takeDamage(int damage) {
    HP -= damage;
}

void player::takeHeal(int heal)
{
    if (HP + heal >= 100) {
        HP = 100;
    }
    else {
        HP += heal;
    }
}


void player::update()
{
    body.setPosition(body.getPosition());
}

void player::movementUpdate(float deltatime, sf::Vector2f mouse)
{

    row = 0;
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed * deltatime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed * deltatime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= speed * deltatime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += speed * deltatime;
    if (mouse.x > 960.f) {
        faceRight = true;

    }
    else
    {
        faceRight = false;
    }

    playeranimation.update(row, deltatime, faceRight);
    body.setTextureRect(playeranimation.uvRect);
    body.move(movement);
}






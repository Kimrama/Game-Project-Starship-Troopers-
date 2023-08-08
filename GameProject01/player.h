#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Playeranimation.h"

class player
{
public:
    player(sf::Texture* texture, const sf::Vector2f& position, sf::Vector2u imageCount, float switcTime, float speed);
    //void move(const sf::Vector2f& val);
    void draw(sf::RenderWindow& window);
    void takeDamage(int damage);
    void takeHeal(int heal);
    void update();
    void movementUpdate(float deltatime, sf::Vector2f mouse);


    const sf::RectangleShape& getBody() const;

    int getMaxHP();
    int getHP();



    sf::Vector2f getPosition() const;


private:
    sf::Texture texture;
    sf::Sprite sprite;
    int level;
    int max_HP, HP;
    sf::Vector2f m_position;
    int max_Exp, Exp;

    sf::RectangleShape body;
    Playeranimation playeranimation;
    unsigned int row;
    float speed;
    bool faceRight;
};
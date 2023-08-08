#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2f& position);

    void update(const sf::FloatRect& playerBounds);
    void takeDamage(int damage);
    bool isDead();
    void draw(sf::RenderWindow& window);
    bool colWithPlayer(const sf::FloatRect& playerBounds);
    bool colWithBullet(const sf::FloatRect& bulletBounds);
    void moveToPlayer(const sf::Vector2f& pos_Player, float speed, float deltatime);





    sf::IntRect frame;


    sf::Sprite& getSprite();

private:
    sf::Sprite sprite;
    sf::RectangleShape body;

    sf::Texture texture;
    float totaltime;
    int maxHP;
    int currentHP;
    bool dead;
    bool faceRight;
    sf::Vector2u imageCount;
    sf::Vector2u currenImage;

};
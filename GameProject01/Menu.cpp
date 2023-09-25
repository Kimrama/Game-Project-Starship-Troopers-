#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

menu::menu() {

    if (!font.loadFromFile("./font1.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    play_button.setSize(sf::Vector2f(200.0f, 50.0f));
    play_button.setPosition(SCREEN_WIDTH / 2 + 200.f, SCREEN_HEIGHT / 2 - 300.f);
    play_button.setFillColor(sf::Color::Red);

    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(40);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(play_button.getPosition().x + 60.0f, play_button.getPosition().y - 3.0f);

    score_button.setSize(sf::Vector2f(400.0f, 50.0f));
    score_button.setPosition(SCREEN_WIDTH / 2 + 200.f, SCREEN_HEIGHT / 2 - 200.f);
    score_button.setFillColor(sf::Color::Red);

    scoreText.setFont(font);
    scoreText.setString("Scoreboard");
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(score_button.getPosition().x + 60.0f, score_button.getPosition().y - 3.0f);

    howToPlay_button.setSize(sf::Vector2f(400.0f, 50.0f));
    howToPlay_button.setPosition(SCREEN_WIDTH / 2 + 200.f, SCREEN_HEIGHT / 2 - 100.f);
    howToPlay_button.setFillColor(sf::Color::Red);

    howToPlayText.setFont(font);
    howToPlayText.setString("How To Play");
    howToPlayText.setCharacterSize(40);
    howToPlayText.setFillColor(sf::Color::White);
    howToPlayText.setPosition(howToPlay_button.getPosition().x + 60.0f, howToPlay_button.getPosition().y - 3.0f);

    exit_button.setSize(sf::Vector2f(400.0f, 50.0f));
    exit_button.setPosition(SCREEN_WIDTH / 2 + 200.f, SCREEN_HEIGHT / 2 - 0.0f);
    exit_button.setFillColor(sf::Color::Red);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(40);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(exit_button.getPosition().x + 60.0f, exit_button.getPosition().y - 3.0f);

    back_button.setSize(sf::Vector2f(400.0f, 50.0f));
    back_button.setPosition(SCREEN_WIDTH / 2 + 600.0f, SCREEN_HEIGHT / 2 + 400.0f);
    back_button.setFillColor(sf::Color::Red);

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(40);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(back_button.getPosition().x + 60.0f, back_button.getPosition().y - 3.0f);


    mainMenu_button.setSize(sf::Vector2f(400.0f, 50.0f));
    mainMenu_button.setPosition(SCREEN_WIDTH / 2 + 600.0f, SCREEN_HEIGHT / 2 + 400.0f);
    mainMenu_button.setFillColor(sf::Color::Red);

    mainMenuText.setFont(font);
    mainMenuText.setString("Main Menu");
    mainMenuText.setCharacterSize(40);
    mainMenuText.setFillColor(sf::Color::White);
    mainMenuText.setPosition(mainMenu_button.getPosition().x + 110.0f, mainMenu_button.getPosition().y - 3.0f);



}
void menu::draw(sf::RenderWindow& window) {
    window.draw(play_button);
    window.draw(playText);
    window.draw(score_button);
    window.draw(scoreText);
    window.draw(howToPlay_button);
    window.draw(howToPlayText);
    window.draw(exit_button);
    window.draw(exitText);
}

void menu::drawExit(sf::RenderWindow& window, const sf::Vector2f& playerPos)
{
    float xOffset = 200.f;
    float yOffset = 300.f;
    exit_button.setPosition(playerPos.x - xOffset, playerPos.y - yOffset);
    exitText.setPosition(exit_button.getPosition().x + 60.0f, exit_button.getPosition().y - 3.0f);
    window.draw(exit_button);
    window.draw(exitText);
}



void menu::drawBack(sf::RenderWindow& window)
{
    window.draw(back_button);
    window.draw(backText);
}

void menu::drawMainMenu(sf::RenderWindow& window, const sf::Vector2f& playerPos)
{
    float xOffset = 200.f;
    float yOffset = 300.f;
    mainMenu_button.setPosition(playerPos.x - xOffset, playerPos.y - yOffset);
    mainMenuText.setPosition(mainMenu_button.getPosition().x + 90.0f, mainMenu_button.getPosition().y - 3.0f);
    window.draw(mainMenu_button);
    window.draw(mainMenuText);

}




bool menu::isPressPlayButton(sf::Vector2f mousePosition) {
    return play_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

bool menu::isPressScoreButton(sf::Vector2f mousePosition)
{
    return score_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

bool menu::isPressHowToPlayButton(sf::Vector2f mousePosition)
{
    return howToPlay_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

bool menu::isPressExitButton(sf::Vector2f mousePosition)
{
    return exit_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

bool menu::isPressBackButton(sf::Vector2f mousePosition)
{
    return back_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

bool menu::isPressMainMenuButton(sf::Vector2f mousePosition)
{
    return mainMenu_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

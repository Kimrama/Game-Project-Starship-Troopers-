#pragma once
#include <SFML/Graphics.hpp>	

class menu
{
public:
	menu();
	void draw(sf::RenderWindow& window);
	void drawExit(sf::RenderWindow& window, const sf::Vector2f& playerPos);
	void drawBack(sf::RenderWindow& window);
	void drawMainMenu(sf::RenderWindow& window, const sf::Vector2f& playerPos);

	bool isPressPlayButton(sf::Vector2f mousePosition);
	bool isPressScoreButton(sf::Vector2f mousePosition);
	bool isPressHowToPlayButton(sf::Vector2f mousePosition);
	bool isPressExitButton(sf::Vector2f mousePosition);
	bool isPressBackButton(sf::Vector2f mousePosition);
	bool isPressMainMenuButton(sf::Vector2f mousePosition);



private:

	sf::Font font;
	sf::Text playText;
	sf::RectangleShape play_button;
	sf::Text scoreText;
	sf::RectangleShape score_button;
	sf::Text howToPlayText;
	sf::RectangleShape howToPlay_button;
	sf::Text exitText;
	sf::RectangleShape exit_button;
	sf::Text backText;
	sf::RectangleShape back_button;
	sf::Text mainMenuText;
	sf::RectangleShape mainMenu_button;


};

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Key Release Detection");

    bool keyIsPressed = false;
    sf::Clock doublePressClock;
    doublePressClock.restart();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            

            if (event.type == sf::Event::KeyPressed) {
                int time = doublePressClock.getElapsedTime().asMilliseconds();
                std::cout << event.key.code << std::endl;
            }
            if (event.type == sf::Event::KeyReleased) {
                std::cout << event.key.code << std::endl;
            }
        }
            
        window.clear();
        window.display();
    }

    return 0;
}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <random>
#include <cmath>
#include <math.h>
#include "player.h"
#include "Enemy.h"
#include "Menu.h"
#include "PauseMenu.h"
#include "BoomObj.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "HealPack.h"
#include "Missile.h"
#include "MissileAmmo.h"
#include "ScoreBoost.h"
#include "ShotgunAmmo.h"
#include <fstream>
#include <algorithm>


#include "Map.h"
#include "bullet.h"
#include "shotgun.h"


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define ENEMY_SPAWN_MARGIN 0.0f


struct Entry {

    std::string letter;
    int number;
    Entry() : letter(), number() {}
    void reset() {
        letter = {};
        number = 0;
    }

};

std::vector<Entry> entries;
std::stringstream lineScore;

void setScoreBoard() {

    lineScore.clear();
    entries.clear();

    std::ifstream inputFile("score.txt");

    std::vector<Entry> entries;
    std::string line;

    while (getline(inputFile, line)) {
        Entry entry;
        entry.reset();

        std::istringstream iss(line);

        for (int i = 0; i < 2; i++) {

            if (i == 0) {
                iss >> entry.letter;
            }
            else {
                iss >> entry.number;
            }

        }

        entries.push_back(entry);
    }
    inputFile.close();

    std::sort(entries.begin(), entries.end(), [](const Entry& a, const Entry& b) {
        return a.number > b.number;
        });
    
    /*
    for (int i = 0; i < 10 && i < entries.size(); ++i) {
        std::cout << entries[i].letter << " : " << entries[i].number << std::endl;
    }
    */

    for (size_t i = 0; i < entries.size() ; i++) {
        
        lineScore << entries[i].letter << "    " << entries[i].number << "\n";
    }

}
    
int main()
{

restart:

    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game", sf::Style::Fullscreen);
    //sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game");
    /*
    player character("D:/ConsoleApplication1/sprite/slime.png", sf::Vector2f(9600.0f, 5400.0f));
    //player character("C:/Study/CE_1/pro_fun/game/sprite/character_Down.png", sf::Vector2f(0.0f, 0.0f));
    */

    sf::Texture playerTexture;
    playerTexture.loadFromFile("D:/GameProject01/GameProject01/sprite/Soldiers/Assault-Class.png");

    player character(&playerTexture, sf::Vector2f(9600.0f, 5400.0f), sf::Vector2u(5, 9), 0.1f, 150.0f);

    sf::Font font;
    font.loadFromFile("D:/GameProject01/GameProject01/font1.ttf");

    sf::Text showWave;

    showWave.setFont(font);
    showWave.setCharacterSize(60);
    showWave.setOutlineThickness(5.f);
    showWave.setFillColor(sf::Color::White);

    sf::Text Score;

    Score.setFont(font);
    Score.setCharacterSize(40);
    Score.setOutlineThickness(5.f);
    Score.setFillColor(sf::Color::White);

    sf::Text onlyScore;
    onlyScore.setFont(font);
    onlyScore.setCharacterSize(60);
    onlyScore.setOutlineThickness(5.f);
    onlyScore.setFillColor(sf::Color::White);


    sf::Text HP;

    HP.setFont(font);
    HP.setCharacterSize(30);
    HP.setFillColor(sf::Color::Black);

    sf::Text Ammo;

    Ammo.setFont(font);
    Ammo.setCharacterSize(30);
    Ammo.setOutlineThickness(5.f);
    Ammo.setFillColor(sf::Color::White);

    sf::Text playerName;
    playerName.setFont(font);
    playerName.setCharacterSize(30);
    playerName.setOutlineThickness(5.f);
    playerName.setFillColor(sf::Color::White);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::Red);

    sf::Text enterPlayerName;
    enterPlayerName.setFont(font);
    enterPlayerName.setString("ENTER PLAYER NAME \n\n\n PRESS ENTER");
    enterPlayerName.setCharacterSize(60);
    enterPlayerName.setFillColor(sf::Color::White);

    sf::Text textBox;
    textBox.setFont(font);
    textBox.setCharacterSize(60);
    textBox.setFillColor(sf::Color::White);

    sf::Text scoreBoardText;

    scoreBoardText.setFont(font);
    scoreBoardText.setString("SCOREBOARD");
    scoreBoardText.setCharacterSize(60);
    scoreBoardText.setFillColor(sf::Color::White);

    sf::Text setScoreText;
    setScoreText.setFont(font);
    setScoreText.setCharacterSize(50);
    setScoreText.setFillColor(sf::Color::White);


    sf::RectangleShape black;
    black.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    black.setFillColor(sf::Color::Black);
    black.setPosition(0, 0);

    sf::RectangleShape HPBar;
    HPBar.setSize(sf::Vector2f(700.f, 40.f));
    HPBar.setFillColor(sf::Color::White);
    HPBar.setOutlineThickness(10.f);
    HPBar.setOutlineColor(sf::Color::Black);

    sf::RectangleShape HPBarRed;
    
    HPBarRed.setFillColor(sf::Color::Red);


    PauseMenu pauseMenu(window);

    Map myMap(SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10);
    menu menu;

    sf::Clock clock;
    sf::Clock movementClock;
    sf::View view(sf::FloatRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT));

    bool gameStarted = false;
    bool isPause = false;
    bool endGame = false;
    bool enterName = false;
    bool callfunction =  false;
    float deltaTime = 0.0f;
    int rateFire = 0;
    int ang1;
    int ang2;
    int ang3;
    int enemyPerWave = 20;
    int wave = 1;
    int nowEnemy = 0;
    int scoreBoost = 1;
    int score = 0;
    int shotgunAmmo = 40;
    int missileAmmo = 20;

    float fx = 0;
    float waveDelay = 0;

    float xOffset = 0.0f;
    float yOffset = 500.0f;

    bool showScore = false;

    std::vector<Enemy> enemies;
    std::vector<Enemy1> enemies1;
    std::vector<Enemy2> enemies2;
    std::vector<ShotgunAmmo> shotgunammos;
    std::vector<MissileAmmo> missileammos;
    std::vector<HealPack> healpacks;
    std::vector<ScoreBoost> scoreboosts;
    std::vector<BoomObj> boomobjs;
    std::vector<Bullet> bullets;
    std::vector<Shotgun> shotguns1;
    std::vector<Shotgun> shotguns2;
    std::vector<Shotgun> shotguns3;
    std::vector<Missile> missiles;
    std::vector<sf::Vector2f> enemiesPositions;

    

    sf::Vector2f playerCenter;
    sf::Vector2f mousePosWindow;
    sf::Vector2f aimDir1;
    sf::Vector2f aimDir2;
    sf::Vector2f aimDir3;
    sf::Vector2f aimDirNorm1;
    sf::Vector2f aimDirNorm2;
    sf::Vector2f aimDirNorm3;

    std::random_device rd;
    std::mt19937 gen(rd());

    Bullet b1;
    Shotgun s1;
    Shotgun s2;
    Shotgun s3;
    Missile m1;
    
    while (window.isOpen())
    {
        
        sf::Event event;
        sf::Vector2f playerPosition = character.getBody().getPosition();
        sf::Vector2f worldMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape && gameStarted && !endGame && !showScore && !enterName) {
                    if (gameStarted) {
                        isPause = !isPause;
                        if (!isPause) {
                            movementClock.restart();
                        }
                    }
                }
            }
        }

        deltaTime = clock.restart().asSeconds();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && !gameStarted) {
                sf::Vector2f mousePosition(sf::Vector2f(sf::Mouse::getPosition(window)));

                if (menu.isPressPlayButton(mousePosition)) {
                    gameStarted = true;
                }
                if (menu.isPressExitButton(mousePosition)) {
                    window.close();
                }
                if (menu.isPressScoreButton(mousePosition)) {
                    showScore = true;
                    gameStarted = true;

                }
            }
        }

        if (isPause && gameStarted && !showScore && !endGame) {

            deltaTime = 0.0f;
            myMap.draw(window);
            character.draw(window);
            pauseMenu.setPosition(character.getBody().getPosition());
            pauseMenu.draw(window);

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (menu.isPressExitButton(worldMousePosition)) {
                        goto restart;
                    }
                }
            }
            
            menu.drawExit(window, playerPosition);
            window.display();
            continue;
        }

        //if (Howtoplay)

        if (!gameStarted) {
            window.clear();
            menu.draw(window);
            window.display();
            continue;
        }
        
        window.clear();

        //-----------------------------------------
        if (showScore) {
            //window.clear();
            if (!callfunction) {
                setScoreBoard();
                callfunction = true;
            }
            
            window.draw(black);
            scoreBoardText.setPosition(800, 100);
            
            setScoreText.setString(lineScore.str());
            setScoreText.setPosition(550, 200);

            menu.drawBack(window);
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (menu.isPressBackButton(worldMousePosition)) {
                        lineScore.clear();
                        //callfunction = false;
                        lineScore.str("");
                        goto restart;
                    }
                }
            }


            window.draw(scoreBoardText);
            window.draw(setScoreText);
            window.display();
            continue;
        }

        if (endGame) {
            deltaTime = 0.0f;
            myMap.draw(window);
            character.draw(window);
            std::stringstream ssonlyScore;
            ssonlyScore << "SCORE : " << score;
            onlyScore.setString(ssonlyScore.str());

            for (auto &i : enemies) {
                i.draw(window);
            }
            for (auto &i : enemies1) {
                i.draw(window);
            }
            for (auto &i : enemies2) {
                i.draw(window);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (menu.isPressMainMenuButton(worldMousePosition)) {
                        enterName = true;
                        endGame = false;
                    }
                }
            }

            onlyScore.setPosition(character.getBody().getPosition().x - xOffset , character.getBody().getPosition().y  - 100);
            showWave.setPosition(character.getBody().getPosition().x - xOffset - 400, character.getBody().getPosition().y  -100);

            window.draw(showWave);
            window.draw(onlyScore);

            gameOverText.setPosition(character.getBody().getPosition().x - xOffset - 160, character.getBody().getPosition().y - yOffset + 40);
            window.draw(gameOverText);

            menu.drawMainMenu(window, playerPosition);
            window.display();
            continue;
        }

        if (enterName) {
            goto record;
            window.clear();
            window.close();
            break;
            
        }


        if (enemies.empty() && !endGame) {
            waveDelay += deltaTime;
            if (waveDelay >= 1.f) {
                enemyPerWave += 5;
                wave++;
                nowEnemy = enemies.size();
                waveDelay = 0;
            }
            
        }

        if (character.getHP() <= 0) {
            endGame = true;
        }

        if (nowEnemy < enemyPerWave) {

            int edge = std::uniform_int_distribution<int>(0, 3)(gen);
            int type = std::uniform_int_distribution<int>(0, 2)(gen);

            float spawnX, spawnY;


            switch (type)
            {
            case 0:
                switch (edge) {
                case 0: // Top
                    spawnX = std::uniform_real_distribution<float>(playerPosition.x - SCREEN_WIDTH / 2, playerPosition.x + SCREEN_WIDTH / 2)(gen);
                    spawnY = (playerPosition.y - SCREEN_HEIGHT / 2 - ENEMY_SPAWN_MARGIN) - 60;
                    break;
                case 1: // Right
                    spawnX = playerPosition.x + SCREEN_WIDTH / 2 + ENEMY_SPAWN_MARGIN;
                    spawnY = std::uniform_real_distribution<float>(playerPosition.y - SCREEN_HEIGHT / 2, playerPosition.y + SCREEN_HEIGHT / 2)(gen);
                    break;
                case 2: // Bottom
                    spawnX = std::uniform_real_distribution<float>(playerPosition.x - SCREEN_WIDTH / 2, playerPosition.x + SCREEN_WIDTH / 2)(gen);
                    spawnY = playerPosition.y + SCREEN_HEIGHT / 2 + ENEMY_SPAWN_MARGIN;
                    break;
                case 3: // Left
                    spawnX = (playerPosition.x - SCREEN_WIDTH / 2 - ENEMY_SPAWN_MARGIN) - 60;
                    spawnY = std::uniform_real_distribution<float>(playerPosition.y - SCREEN_HEIGHT / 2, playerPosition.y + SCREEN_HEIGHT / 2)(gen);
                    break;
                default:
                    break;
                }
                nowEnemy++;
                enemies.push_back(Enemy(sf::Vector2f(spawnX,spawnY)));
                break;
            case 1:
                switch (edge) {
                case 0: // Top
                    spawnX = std::uniform_real_distribution<float>(playerPosition.x - SCREEN_WIDTH / 2, playerPosition.x + SCREEN_WIDTH / 2)(gen);
                    spawnY = (playerPosition.y - SCREEN_HEIGHT / 2 - ENEMY_SPAWN_MARGIN) - 60;
                    break;
                case 1: // Right
                    spawnX = playerPosition.x + SCREEN_WIDTH / 2 + ENEMY_SPAWN_MARGIN;
                    spawnY = std::uniform_real_distribution<float>(playerPosition.y - SCREEN_HEIGHT / 2, playerPosition.y + SCREEN_HEIGHT / 2)(gen);
                    break;
                case 2: // Bottom
                    spawnX = std::uniform_real_distribution<float>(playerPosition.x - SCREEN_WIDTH / 2, playerPosition.x + SCREEN_WIDTH / 2)(gen);
                    spawnY = playerPosition.y + SCREEN_HEIGHT / 2 + ENEMY_SPAWN_MARGIN;
                    break;
                case 3: // Left
                    spawnX = (playerPosition.x - SCREEN_WIDTH / 2 - ENEMY_SPAWN_MARGIN) - 60;
                    spawnY = std::uniform_real_distribution<float>(playerPosition.y - SCREEN_HEIGHT / 2, playerPosition.y + SCREEN_HEIGHT / 2)(gen);
                    break;
                default:
                    break;
                }
                nowEnemy++;
                enemies1.push_back(Enemy1(sf::Vector2f(spawnX, spawnY)));
                break;
            case 2:
                switch (edge) {
                case 0: // Top
                    spawnX = std::uniform_real_distribution<float>(playerPosition.x - SCREEN_WIDTH / 2, playerPosition.x + SCREEN_WIDTH / 2)(gen);
                    spawnY = (playerPosition.y - SCREEN_HEIGHT / 2 - ENEMY_SPAWN_MARGIN) - 60;
                    break;
                case 1: // Right
                    spawnX = playerPosition.x + SCREEN_WIDTH / 2 + ENEMY_SPAWN_MARGIN;
                    spawnY = std::uniform_real_distribution<float>(playerPosition.y - SCREEN_HEIGHT / 2, playerPosition.y + SCREEN_HEIGHT / 2)(gen);
                    break;
                case 2: // Bottom
                    spawnX = std::uniform_real_distribution<float>(playerPosition.x - SCREEN_WIDTH / 2, playerPosition.x + SCREEN_WIDTH / 2)(gen);
                    spawnY = playerPosition.y + SCREEN_HEIGHT / 2 + ENEMY_SPAWN_MARGIN;
                    break;
                case 3: // Left
                    spawnX = (playerPosition.x - SCREEN_WIDTH / 2 - ENEMY_SPAWN_MARGIN) - 60;
                    spawnY = std::uniform_real_distribution<float>(playerPosition.y - SCREEN_HEIGHT / 2, playerPosition.y + SCREEN_HEIGHT / 2)(gen);
                    break;
                default:
                    break;
                }
                nowEnemy++;
                enemies2.push_back(Enemy2(sf::Vector2f(spawnX, spawnY)));
                break;

            default:
                break;
            }

            
        }

        view.setCenter(static_cast<sf::Vector2f>(character.getBody().getPosition()));
        window.setView(view);

        sf::FloatRect playerBounds = character.getBody().getGlobalBounds();
        sf::FloatRect bulletBounds = b1.getShape().getGlobalBounds();
        sf::FloatRect shotgun1Bound = s1.getShape().getGlobalBounds();
        sf::FloatRect shotgun2Bound = s2.getShape().getGlobalBounds();
        sf::FloatRect shotgun3Bound = s3.getShape().getGlobalBounds();


        for (size_t i = 0; i < enemies.size(); ++i) {
            enemiesPositions.push_back(enemies[i].getSprite().getPosition());
            enemies[i].moveToPlayer(character.getBody().getPosition(), 7.f, deltaTime);
            enemies[i].update(playerBounds);

            if (enemies[i].colWithPlayer(playerBounds)) {
                character.takeDamage(10);
            }

            if (enemies[i].isDead()) {
                score++;
                int droprate = rand() % 100 + 1;
                if (droprate >= 90) {
                    int dropType = std::uniform_int_distribution<int>(0, 3)(gen);
                    switch (dropType)
                    {
                    case 0:
                        shotgunammos.push_back(ShotgunAmmo(sf::Vector2f(enemies[i].getSprite().getPosition())));
                        break;
                    case 1:
                        missileammos.push_back(MissileAmmo(sf::Vector2f(enemies[i].getSprite().getPosition())));
                        break;
                    case 2:
                        scoreboosts.push_back(ScoreBoost(sf::Vector2f(enemies[i].getSprite().getPosition())));
                        break;
                    case 3:
                        healpacks.push_back(HealPack(sf::Vector2f(enemies[i].getSprite().getPosition())));
                        break;
                    default:
                        break;
                    }
                }
                enemies.erase(enemies.begin() + i);
                i--;
            }

        }
        for (size_t i = 0; i < enemies1.size(); ++i) {
            enemiesPositions.push_back(enemies1[i].getSprite().getPosition());
            enemies1[i].moveToPlayer(character.getBody().getPosition(), 6.5f, deltaTime);
            enemies1[i].update(playerBounds);

            if (enemies1[i].colWithPlayer(playerBounds)) {
                character.takeDamage(10);
            }

            if (enemies1[i].isDead()) {
                int droprate = rand() % 100 + 1;
                if (droprate >= 90) {
                    int dropType = std::uniform_int_distribution<int>(0, 3)(gen);
                    switch (dropType)
                    {
                    case 0:
                        shotgunammos.push_back(ShotgunAmmo(sf::Vector2f(enemies1[i].getSprite().getPosition())));
                        break;
                    case 1:
                        missileammos.push_back(MissileAmmo(sf::Vector2f(enemies1[i].getSprite().getPosition())));
                        break;
                    case 2:
                        scoreboosts.push_back(ScoreBoost(sf::Vector2f(enemies1[i].getSprite().getPosition())));
                        break;
                    case 3:
                        healpacks.push_back(HealPack(sf::Vector2f(enemies1[i].getSprite().getPosition())));
                        break;
                    default:
                        break;
                    }
                }
                enemies1.erase(enemies1.begin() + i);
                score++;
                i--;
            }
        }
        for (size_t i = 0; i < enemies2.size(); ++i) {
            enemiesPositions.push_back(enemies2[i].getSprite().getPosition());
            enemies2[i].moveToPlayer(character.getBody().getPosition(), 6.f, deltaTime);
            enemies2[i].update(playerBounds);

            if (enemies2[i].colWithPlayer(playerBounds)) {
                character.takeDamage(10);
            }


            if (enemies2[i].isDead()) {
                int droprate = rand() % 100 + 1;
                score++;
                if (droprate >= 90) {
                    int dropType = std::uniform_int_distribution<int>(0, 3)(gen);

                    switch (dropType)
                    {
                    case 0:
                        shotgunammos.push_back(ShotgunAmmo(sf::Vector2f(enemies2[i].getSprite().getPosition())));
                        break;
                    case 1:
                        missileammos.push_back(MissileAmmo(sf::Vector2f(enemies2[i].getSprite().getPosition())));
                        break;
                    case 2:
                        scoreboosts.push_back(ScoreBoost(sf::Vector2f(enemies2[i].getSprite().getPosition())));
                        break;
                    case 3:
                        healpacks.push_back(HealPack(sf::Vector2f(enemies2[i].getSprite().getPosition())));
                        break;
                    default:
                        break;
                    }
                }
                enemies2.erase(enemies2.begin() + i);
                i--;

            }

        }

        for (size_t i = 0; i < shotgunammos.size(); i++) {
            float distanceShotgunI = sqrt(pow(shotgunammos[i].getShape().getPosition().x - character.getPosition().x, 2) + pow(shotgunammos[i].getShape().getPosition().y - character.getPosition().y, 2));
            if (distanceShotgunI >= 1000.f) {
                shotgunammos.erase(shotgunammos.begin() + i);

            }
            else if (shotgunammos[i].getShape().getGlobalBounds().intersects(character.getBody().getGlobalBounds())) {
                shotgunAmmo += 5;
                shotgunammos.erase(shotgunammos.begin() + i);
            }
        }

        for (size_t i = 0; i < missileammos.size(); i++) {
            float distanceMissileI = sqrt(pow(missileammos[i].getShape().getPosition().x - character.getPosition().x, 2) + pow(missileammos[i].getShape().getPosition().y - character.getPosition().y, 2));
            if (distanceMissileI >= 1000.f) {
                missileammos.erase(missileammos.begin() + i);

            }
            else if (missileammos[i].getShape().getGlobalBounds().intersects(character.getBody().getGlobalBounds())) {
                missileAmmo += 2;
                missileammos.erase(missileammos.begin() + i);
            }
        }

        for (size_t i = 0; i < scoreboosts.size(); i++) {
            float distanceBoostI = sqrt(pow(scoreboosts[i].getShape().getPosition().x - character.getPosition().x, 2) + pow(scoreboosts[i].getShape().getPosition().y - character.getPosition().y, 2));
            if (distanceBoostI >= 1000.f) {
                scoreboosts.erase(scoreboosts.begin() + i);

            }
            else if (scoreboosts[i].getShape().getGlobalBounds().intersects(character.getBody().getGlobalBounds())) {
                scoreBoost++;
                scoreboosts.erase(scoreboosts.begin() + i);
            }
        }

        for (size_t i = 0; i < healpacks.size(); i++) {
            float distanceHealI = sqrt(pow(healpacks[i].getShape().getPosition().x - character.getPosition().x, 2) + pow(healpacks[i].getShape().getPosition().y - character.getPosition().y, 2));
            if (distanceHealI >= 1000.f) {
                healpacks.erase(healpacks.begin() + i);

            }
            else if (healpacks[i].getShape().getGlobalBounds().intersects(character.getBody().getGlobalBounds())) {
                character.takeHeal(15);
                healpacks.erase(healpacks.begin() + i);
            }
        }


        playerCenter = sf::Vector2f(character.getPosition().x + 25.f, character.getPosition().y + 35.f);   

        sf::Vector2f dis(50.f, 50.f);


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

            aimDir1 = worldMousePosition - playerCenter;
            float sc = 1.0f / sqrt(pow(aimDir1.x, 2) + pow(aimDir1.y, 2));
            aimDirNorm1 = aimDir1 * sc;
            ang1 = std::atan2f(aimDirNorm1.x, aimDirNorm1.y) * 180 / 3.01415926535;
            std::cout << "ang  = " << ang1 << std::endl;
            if (rateFire < 6)
                rateFire++;
            if (rateFire >= 5 && bullets.size() < 10)
            {
                b1.shape.setPosition(playerCenter);

                b1.currVelocity = aimDirNorm1 * 30.f;

                b1.shape.setRotation(90 - ang1);

                bullets.push_back(Bullet(b1));
                rateFire = 0;
            }
        }

        for (size_t i = 0; i < bullets.size(); ++i) {
            bullets[i].shape.move(bullets[i].currVelocity);
            //out of bounds
            float distance = sqrt(pow(bullets[i].shape.getPosition().x - character.getPosition().x, 2) + pow(bullets[i].shape.getPosition().y - character.getPosition().y, 2));
            if (distance >= 1000) {
                bullets.erase(bullets.begin() + i);
            }
        }

        for (size_t i = 0; i < bullets.size(); i++) {
            for (size_t j = 0; j < enemies.size(); j++)
            {
                if (bullets[i].shape.getGlobalBounds().intersects(enemies[j].getSprite().getGlobalBounds()))
                {
                    bullets.erase(bullets.begin() + i);
                    enemies[j].takeDamage(1);
                    break;
                }
            }
        }
        for (size_t i = 0; i < bullets.size(); i++) {
            for (size_t j = 0; j < enemies1.size(); j++)
            {
                if (bullets[i].shape.getGlobalBounds().intersects(enemies1[j].getSprite().getGlobalBounds()))
                {
                    bullets.erase(bullets.begin() + i);
                    enemies1[j].takeDamage(1);
                    break;
                }
            }
        }
        for (size_t i = 0; i < bullets.size(); i++) {
            for (size_t j = 0; j < enemies2.size(); j++)
            {
                if (bullets[i].shape.getGlobalBounds().intersects(enemies2[j].getSprite().getGlobalBounds()))
                {
                    bullets.erase(bullets.begin() + i);
                    enemies2[j].takeDamage(1);
                    break;
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {

            aimDir1 = worldMousePosition - playerCenter;
            aimDir2 = worldMousePosition - playerCenter + dis;
            aimDir3 = worldMousePosition - playerCenter - dis;

            float sc1 = 1.0f / sqrt(pow(aimDir1.x, 2) + pow(aimDir1.y, 2));
            float sc2 = 1.0f / sqrt(pow(aimDir2.x, 2) + pow(aimDir2.y, 2));
            float sc3 = 1.0f / sqrt(pow(aimDir3.x, 2) + pow(aimDir3.y, 2));

            aimDirNorm1 = aimDir1 * sc1;
            aimDirNorm2 = aimDir2 * sc2;
            aimDirNorm3 = aimDir3 * sc3;
            ang1 = std::atan2f(aimDirNorm1.x, aimDirNorm1.y) * 180 / 3.01415926535;
            ang2 = std::atan2f(aimDirNorm2.x, aimDirNorm2.y) * 180 / 3.01415926535;
            ang3 = std::atan2f(aimDirNorm3.x, aimDirNorm3.y) * 180 / 3.01415926535;
            std::cout << "ang  = " << ang1 << std::endl;

            if (shotguns1.size() < 1 && shotgunAmmo > 0)
            {
                s1.shape.setPosition(playerCenter);

                s1.currVelocity = aimDirNorm1 * 18.f;

                s1.shape.setRotation(90 - ang1);

                shotguns1.push_back(Shotgun(s1));

                s2.shape.setPosition(playerCenter);

                s2.currVelocity = (aimDirNorm2) * 18.f;

                s2.shape.setRotation(90 - ang2);

                shotguns2.push_back(Shotgun(s2));

                s3.shape.setPosition(playerCenter);

                s3.currVelocity = aimDirNorm3 * 18.f;

                s3.shape.setRotation(90 - ang3);

                shotguns3.push_back(Shotgun(s3));

                shotgunAmmo--;
            }
        }

        for (size_t i = 0; i < shotguns1.size(); ++i)
        {
            shotguns1[i].shape.move(shotguns1[i].currVelocity);
            //out of bounds
            float distance1 = sqrt(pow(shotguns1[i].shape.getPosition().x - character.getPosition().x, 2) + pow(shotguns1[i].shape.getPosition().y - character.getPosition().y, 2));
            if (distance1 >= 300) {
                shotguns1.erase(shotguns1.begin() + i);
            }

        }

        for (size_t i = 0; i < shotguns2.size(); ++i)
        {
            shotguns2[i].shape.move(shotguns2[i].currVelocity);
            //out of bounds
            float distance2 = sqrt(pow(shotguns2[i].shape.getPosition().x - character.getPosition().x, 2) + pow(shotguns2[i].shape.getPosition().y - character.getPosition().y, 2));
            if (distance2 >= 300) {
                shotguns2.erase(shotguns2.begin() + i);
            }
        }

        for (size_t i = 0; i < shotguns3.size(); ++i)
        {
            shotguns3[i].shape.move(shotguns3[i].currVelocity);
            //out of bounds
            float distance3 = sqrt(pow(shotguns3[i].shape.getPosition().x - character.getPosition().x, 2) + pow(shotguns3[i].shape.getPosition().y - character.getPosition().y, 2));
            if (distance3 >= 300) {
                shotguns3.erase(shotguns3.begin() + i);
            }
        }

        for (size_t i = 0; i < shotguns1.size(); i++)
        {
            for (size_t j = 0; j < enemies.size(); j++)
            {
                if (shotguns1[i].shape.getGlobalBounds().intersects(enemies[j].getSprite().getGlobalBounds()))
                {
                    enemies[j].takeDamage(2);
                    break;
                }
            }
        }
        for (size_t i = 0; i < shotguns1.size(); i++)
        {
            for (size_t j = 0; j < enemies1.size(); j++)
            {
                if (shotguns1[i].shape.getGlobalBounds().intersects(enemies1[j].getSprite().getGlobalBounds()))
                {
                    enemies1[j].takeDamage(2);
                    break;
                }
            }
        }
        for (size_t i = 0; i < shotguns1.size(); i++)
        {
            for (size_t j = 0; j < enemies2.size(); j++)
            {
                if (shotguns1[i].shape.getGlobalBounds().intersects(enemies2[j].getSprite().getGlobalBounds()))
                {
                    enemies2[j].takeDamage(2);
                    break;
                }
            }
        }

        for (size_t i = 0; i < shotguns2.size(); i++) {
            for (size_t j = 0; j < enemies.size(); j++)
            {
                if (shotguns2[i].shape.getGlobalBounds().intersects(enemies[j].getSprite().getGlobalBounds()))
                {
                    enemies[j].takeDamage(2);
                    break;
                }
            }
        }
        for (size_t i = 0; i < shotguns2.size(); i++) {
            for (size_t j = 0; j < enemies1.size(); j++)
            {
                if (shotguns2[i].shape.getGlobalBounds().intersects(enemies1[j].getSprite().getGlobalBounds()))
                {
                    enemies1[j].takeDamage(2);
                    break;
                }
            }
        }
        for (size_t i = 0; i < shotguns2.size(); i++) {
            for (size_t j = 0; j < enemies2.size(); j++)
            {
                if (shotguns2[i].shape.getGlobalBounds().intersects(enemies2[j].getSprite().getGlobalBounds()))
                {
                    enemies2[j].takeDamage(2);
                    break;
                }
            }
        }

        for (size_t i = 0; i < shotguns3.size(); i++) {
            for (size_t j = 0; j < enemies.size(); j++)
            {
                if (shotguns3[i].shape.getGlobalBounds().intersects(enemies[j].getSprite().getGlobalBounds()))
                {
                    enemies[j].takeDamage(2);
                    break;
                }
            }
        }
        for (size_t i = 0; i < shotguns3.size(); i++) {
            for (size_t j = 0; j < enemies1.size(); j++)
            {
                if (shotguns3[i].shape.getGlobalBounds().intersects(enemies1[j].getSprite().getGlobalBounds()))
                {
                    enemies1[j].takeDamage(2);
                    break;
                }
            }
        }
        for (size_t i = 0; i < shotguns3.size(); i++) {
            for (size_t j = 0; j < enemies2.size(); j++)
            {
                if (shotguns3[i].shape.getGlobalBounds().intersects(enemies2[j].getSprite().getGlobalBounds()))
                {
                    enemies2[j].takeDamage(2);
                    break;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {

            aimDir1 = worldMousePosition - playerCenter;
            float sc = 1.0f / sqrt(pow(aimDir1.x, 2) + pow(aimDir1.y, 2));
            aimDirNorm1 = aimDir1 * sc;
            ang1 = std::atan2f(aimDirNorm1.x, aimDirNorm1.y) * 180 / 3.01415926535;
            std::cout << "ang  = " << ang1 << std::endl;

            if (missiles.size() < 1 && boomobjs.size() < 1 && missileAmmo > 0)
            {
                m1.shape.setPosition(playerCenter);

                m1.currVelocity = aimDirNorm1 * 30.f;

                m1.shape.setRotation(90 - ang1);

                missiles.push_back(Missile(m1));

                boomobjs.push_back(BoomObj(worldMousePosition));

                missileAmmo--;
            }
        }


        for (size_t i = 0; i < missiles.size(); ++i)
        {
            missiles[i].shape.move(missiles[i].currVelocity);
            float playerToMouse = sqrt(pow(playerCenter.x - worldMousePosition.x, 2) + pow(playerCenter.y - worldMousePosition.y,2));
            float distanceMissile = sqrt(pow(missiles[i].shape.getPosition().x - character.getPosition().x, 2) + pow(missiles[i].shape.getPosition().y - character.getPosition().y, 2));
            if (distanceMissile >= playerToMouse) {
                missiles.erase(missiles.begin() + i);
            }

        }

        for (size_t i = 0; i < boomobjs.size(); i++) {
            fx += deltaTime;
            boomobjs[i].boomAnimation(deltaTime);
            if (fx >= 0.4f) {
                boomobjs.erase(boomobjs.begin() + i);
                fx = 0;
            }
        }

        for (size_t i = 0; i < boomobjs.size(); i++) {
            for (size_t j = 0; j < enemies.size(); j++) {
                if (boomobjs[i].getSprite().getGlobalBounds().intersects(enemies[j].getSprite().getGlobalBounds()))
                {
                    enemies[j].takeDamage(5);
                    break;
                }
            }
        }
        for (size_t i = 0; i < boomobjs.size(); i++) {
            for (size_t j = 0; j < enemies1.size(); j++) {
                if (boomobjs[i].getSprite().getGlobalBounds().intersects(enemies1[j].getSprite().getGlobalBounds()))
                {
                    enemies1[j].takeDamage(5);
                    break;
                }
            }
        }
        for (size_t i = 0; i < boomobjs.size(); i++) {
            for (size_t j = 0; j < enemies2.size(); j++) {
                if (boomobjs[i].getSprite().getGlobalBounds().intersects(enemies2[j].getSprite().getGlobalBounds()))
                {
                    enemies2[j].takeDamage(5);
                    break;
                }
            }
        }

        

        sf::Vector2f mouse(sf::Mouse::getPosition());

        std::stringstream ss;
        ss << "wave : " << wave << " |";
        showWave.setString(ss.str());

        std::stringstream ssScore;
        ssScore << "BOOST X" << scoreBoost << "  SCORE : " << score;
        Score.setString(ssScore.str());

        std::stringstream ssHP;
        ssHP << "PLAYER HP : " << character.getHP();
        HP.setString(ssHP.str());


        std::stringstream ssAmmo;
        ssAmmo << "SHOTGUN AMMO : " << shotgunAmmo << "\n" << "MISSILE ROCKET : " << missileAmmo;
        Ammo.setString(ssAmmo.str());

        HPBarRed.setSize(sf::Vector2f(character.getHP()*700.f/100.f, 40.f));

        window.clear();

        Score.setPosition(character.getBody().getPosition().x - xOffset + 400 , character.getBody().getPosition().y - yOffset + 10);
        showWave.setPosition(character.getBody().getPosition().x - xOffset , character.getBody().getPosition().y - yOffset + 5);
        HP.setPosition(character.getBody().getPosition().x - xOffset - 700, character.getBody().getPosition().y - yOffset + 5);
        Ammo.setPosition(character.getBody().getPosition().x - xOffset - 900, character.getBody().getPosition().y - yOffset + 100);
        HPBar.setPosition(character.getBody().getPosition().x - xOffset - 900, character.getBody().getPosition().y - yOffset + 5);
        HPBarRed.setPosition(character.getBody().getPosition().x - xOffset - 900, character.getBody().getPosition().y - yOffset + 5);

        character.movementUpdate(deltaTime, mouse);


        myMap.draw(window);

        for (auto i : enemies) {
            i.draw(window);
        }
        for (auto i : enemies1) {
            i.draw(window);
        }
        for (auto i : enemies2) {
            i.draw(window);
        }
        for (auto i : shotgunammos) {
            i.draw(window);
        }
        for (auto i : missileammos) {
            i.draw(window);
        }
        for (auto i : scoreboosts) {
            i.draw(window);
        }
        for (auto i : healpacks) {
            i.draw(window);
        }
        for (auto i : bullets)
        {
            i.render(window);
        }
        for (auto i : shotguns1)
        {
            i.render(window);
        }
        for (auto i : shotguns2)
        {
            i.render(window);
        }
        for (auto i : shotguns3)
        {
            i.render(window);
        }
        for (auto i : missiles)
        {
            i.render(window);
        }
        for (auto i : boomobjs)
        {
            i.draw(window);
        }




        character.draw(window);
        window.draw(showWave);
        window.draw(Score);
        window.draw(HPBar);
        window.draw(HPBarRed);
        window.draw(HP);
        window.draw(Ammo);
        window.display();

    }
record:
    if (score != 0) {

        sf::RenderWindow windowREC(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game", sf::Style::Fullscreen);
        windowREC.setFramerateLimit(60);

        std::stringstream ssScoreNum;
        ssScoreNum << score;
 
        std::string inputText;

        while (windowREC.isOpen())
        {
            sf::Event eventREC;
            while (windowREC.pollEvent(eventREC))
            {
                if (eventREC.type == sf::Event::Closed)
                    windowREC.close();


                if (eventREC.type == sf::Event::TextEntered)
                {
                    if (eventREC.text.unicode < 128)
                    {
                        if (eventREC.text.unicode == '\b' && !inputText.empty())
                        {

                            inputText.pop_back();
                        }
                        else if (eventREC.text.unicode != '\b')
                        {

                            inputText += static_cast<char>(eventREC.text.unicode);
                        }
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                std::ofstream outputFile("score.txt", std::ios::app);
                inputText.pop_back();
                outputFile << inputText << " " << ssScoreNum.str() << "\n";

                outputFile.close();
                goto restart;
                break;

            }

            enterPlayerName.setPosition(1000,400);
            onlyScore.setPosition(500, 500);

            textBox.setString(inputText);
            textBox.setPosition(1000, 500);

            windowREC.clear();
            windowREC.draw(textBox);
            windowREC.draw(onlyScore);
            windowREC.draw(enterPlayerName);
            windowREC.display();
        }
    }



    return 0;
}

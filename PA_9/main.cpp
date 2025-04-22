#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "player.hpp"
#include "background.hpp"
#include "ball.hpp"
#include "Windows.h"
#include "MiscFunctions.hpp"
#include <vector>

int main()
{
    //Seed random time
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    //Open window and return dimensions
	sf::RenderWindow window = initWindow();

    //Start game in the menu
    Menu menu;
    menu.startMenu();

    //load player
	Player player = loadPlayer(window);

	//load background
    Background background = loadBackground();

    //load ball vector
    std::vector<Ball> enemies;
    sf::Texture ballTexture;
    ballTexture.loadFromFile("fBall.png");
    Ball ball(ballTexture);
    float scale = 0.1f + static_cast<float>(std::rand()) / RAND_MAX * 0.2f; //Between 0.05 and 0.2
    ball.setScale({ scale, scale });


    //initialize clock to keep track of game time
    sf::Clock spawnClock;
    float spawnRate = 7;

    while (window.isOpen())
    {
        //keep program running until window closes
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Time elapsed = spawnClock.getElapsedTime();

        if (elapsed.asSeconds() >= spawnRate)
        {
			enemies.push_back(ball);
			spawnClock.restart();
            if(spawnRate > 2)
				spawnRate -= 0.2f;
			for (int i = 0; i < enemies.size(); i++)
			{
                window.draw(enemies[i]);
			}

        }

        //update all objects
        ball.update(window.getSize());
        player.movePlayer(window.getSize());

        //empty screen
        window.clear();

        //draw all necessary objects back to screen
        window.draw(background);
        window.draw(player);
        window.draw(ball);

        //display window to screen
        window.display();
    }
        return 0;
}
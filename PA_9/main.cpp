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

    //load book textures
    sf::Texture bookTextures[3];
    bookTextures[0].loadFromFile("Book.png");
    bookTextures[1].loadFromFile("Book2.png");
    bookTextures[2].loadFromFile("Book3.png");

    //vector to store multiple books
	std::vector<Ball> balls;

    //first ball
    Ball newBall(bookTextures[std::rand() % 3]);
    float scale = 0.1f + ((float)(std::rand() % 5+1) / 60); // Between 0.1 and .15
    newBall.setScale({ scale, scale });
    balls.push_back(newBall);



    //initialize clock to keep track of game time
    sf::Clock spawnClock;

	//defines starting spawn rate of balls. decreases down to 3 seconds for difficulty increase
    float spawnRate = 6;

    while (window.isOpen())
    {
        //keep program running until window closes
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Spawn a new ball every spawnRate seconds
        if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
        {
            Ball newBall(bookTextures[std::rand() % 3]);
            float scale = 0.1f + ((float)(std::rand() % 5+1) / 60); // Between 0.1 and .15
            newBall.setScale({ scale, scale });
            balls.push_back(newBall);
            spawnClock.restart();
			if (spawnRate > 3) spawnRate -= 0.1f; // Decrease spawn rate to increase difficulty
        }

        // Update all balls
        for (auto& ball : balls)
        {
            ball.update(window.getSize());
        }
        std::cout << "Number of balls: " << balls.size() << std::endl;


        //update all objects
       // ball.update(window.getSize());
        player.movePlayer(window.getSize());

        //empty screen
        window.clear();

        //draw all necessary objects back to screen

        window.draw(background);
        window.draw(player);
        for (const auto& ball : balls)
        {
            window.draw(ball);
        }
        //window.draw(ball);

        //display window to screen
        window.display();
    }
    return 0;
}
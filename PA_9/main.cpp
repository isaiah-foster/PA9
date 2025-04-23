#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include "menu.hpp"
#include "player.hpp"
#include "background.hpp"
#include "ball.hpp"
#include "Windows.h"
#include "MiscFunctions.hpp"
#include <vector>
#include "pencil.hpp"
#include "textLabel.hpp"
#include "ScoreBoard.hpp"

int main()
{
    //Seed random time
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    //Open window and return dimensions
    sf::RenderWindow window = initWindow();
    sf::Vector2u windowSize = window.getSize();

    //Start game in the menu
    Menu menu;
    menu.startMenu();

    //load background music
    sf::Music track1;
    track1.openFromFile("track1.mp3");
    track1.play();

    //load player
    Player player = loadPlayer(window);

    //load background
    Background background = loadBackground();

    //track gamescore
    int score = 0;
    
    //load laser sound
    sf::Music laserSound;
    laserSound.openFromFile("LaserGunPew.wav");

    //load book textures
    sf::Texture bookTextures[3];
    bookTextures[0].loadFromFile("Book.png");
    bookTextures[1].loadFromFile("Book2.png");
    bookTextures[2].loadFromFile("Book3.png");

    //vectors to store books and pencils
	std::vector<Ball> balls;
	std::vector<Pencil> pencils; 

    //first ball
    Ball newBall(bookTextures[std::rand() % 3]);
    float scale = 0.1f + ((float)(std::rand() % 5+1) / 60); // Between 0.1 and .15
    newBall.setScale({ scale, scale });
    balls.push_back(newBall);

    //load first pencil in
    sf::Texture pencilTex;
    pencilTex.loadFromFile("pencil.png");
    Pencil pencil(pencilTex, player.getPosition());
	pencils.push_back(pencil);


    //initialize clock to keep track of game time
    sf::Clock ball_spawn_clock;
	sf::Clock pencil_spawn_clock;


    //make text stuff
	sf::Font font;
    if (!font.openFromFile("PressStart2P-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1; // Exit the program if the font fails to load
    }
	sf::Text scoreLabel(font, "Score = 0");
	scoreLabel.setCharacterSize(50);
	scoreLabel.setFillColor(sf::Color::Green);
	scoreLabel.setOrigin({ scoreLabel.getGlobalBounds().size.x / 2, scoreLabel.getGlobalBounds().size.y / 2 });
	scoreLabel.setPosition({ (float)windowSize.x /2 , (float)windowSize.y* .93f });

    sf::Text healthLabel(font, "Health = 5");
    healthLabel.setCharacterSize(50);
    healthLabel.setFillColor(sf::Color::Red);
    healthLabel.setOrigin({ healthLabel.getGlobalBounds().size.x / 2, healthLabel.getGlobalBounds().size.y / 2 });
    healthLabel.setPosition({ (float)windowSize.x / 2 - 500 *(windowSize.x/1920), (float)windowSize.y * .93f});



	//defines starting spawn rate of balls. decreases down to 3 seconds for difficulty increase
    float ballSpawnRate = 5;
    float pencilSpawnRate = 50.f;

    while (window.isOpen())
    {
        //keep program running until window closes
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //spawn a new ball every spawnRate seconds
        if (ball_spawn_clock.getElapsedTime().asSeconds() >= ballSpawnRate)
        {
            Ball newBall(bookTextures[std::rand() % 3]);
            float scale = 0.1f + ((float)(std::rand() % 5+1) / 60); // Between 0.1 and .15
            newBall.setScale({ scale, scale });
            balls.push_back(newBall);
            ball_spawn_clock.restart();
			if (ballSpawnRate > 1) ballSpawnRate -= 0.1f; // Decrease spawn rate to increase difficulty
            std::cout << "Number of balls: " << balls.size() << std::endl;
        }

        //spawn in a new pencil if pencil is shot
		if (pencils[pencils.size() - 1].getIsShooting() == true && pencil_spawn_clock.getElapsedTime().asMilliseconds() >= pencilSpawnRate)
		{
            if (pencils.size() >= 25)
            {
                pencils.erase(pencils.begin()); // Remove the first (oldest) pencil
            }

			Pencil newPencil(pencilTex, player.getPosition());
			pencils.push_back(newPencil);
			pencil_spawn_clock.restart();

		}

        //update all objects//
        
        
        //ipdate all balls
        for (auto& ball : balls)
        {
            ball.update(window.getSize());
			if (ball.getHealth() <= 0)
			{
                score+= ball.getOriginalHealth();
				//remove the ball from the vector if destoryed
				ball.setHealth(0);
				balls.erase(std::remove_if(balls.begin(), balls.end(), [](const Ball& b) { return b.getHealth() <= 0; }), balls.end());
                scoreLabel.setString("Score = " + std::to_string(score));
			}
        }
        
		//update all pencils
        for (auto& pencil : pencils)
        {
			pencil.update(window, laserSound, player);
            if (pencil.getIsHit())
            {
				//remove the pencil from the vector if it hits a book
				pencils.erase(std::remove_if(pencils.begin(), pencils.end(), [](const Pencil& p) { return p.getIsHit(); }), pencils.end());
            }
        }

		//check if pencils have hit a ball and if balls have hit the player
        for (auto& ball : balls)
        {
            if (checkIfPlayerIsHit(player, ball))
            {
                healthLabel.setString("Score = " + std::to_string(player.getHealth()));
            }
            for (auto& pencil : pencils)
            {
				checkShotHit(pencil, ball);
            }
        }

        //update player location & check hit
        player.movePlayer(window.getSize());

        //clear screen
        window.clear();

        //draw all objects back to screen//

        window.draw(background);
        window.draw(player);
		window.draw(scoreLabel);
        window.draw(healthLabel);

        //draw all balls
        for (const auto& ball : balls)
        {
            window.draw(ball);
        }

		//draw all pencils
		for (const auto& pencil : pencils)
		{
			window.draw(pencil);
		}

        //display window to screen
        window.display();

		if (player.getHealth() <= 0)
		{
			std::cout << "Game Over!" << std::endl;
			score = 0;
			menu.startMenu();
		}
    }
    return 0;
}
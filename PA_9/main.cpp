#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include "menu.hpp"
#include "player.hpp"
#include "background.hpp"
#include "ball.hpp"
#include "Windows.h"
#include "MiscFunctions.hpp"
#include <vector>
#include <string>
#include "pencil.hpp"
#include "ScoreBoard.hpp"
#include "GameOverScreen.hpp"

int main()
{
    //Seed random time
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    //Open window and return dimensions
    sf::RenderWindow window = initWindow();
    sf::Vector2u windowSize = window.getSize();

    

    //load menu background music
    sf::Music menuMusic;
    menuMusic.openFromFile("danceWeapon4.mp3");
    menuMusic.setVolume(15);
    menuMusic.play();
    menuMusic.setLooping(true);

    //load in-game background music
    sf::Music gameMusic;
    gameMusic.openFromFile("track1.mp3");
    gameMusic.setVolume(20);
    

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


    //initialize clocks to keep track of game time
    sf::Clock ball_spawn_clock;
	sf::Clock pencil_spawn_clock;
    sf::Clock hitRestrictor;


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

	sf::Text highScoreLable(font, "High Score = 0");
	highScoreLable.setCharacterSize(50);
	highScoreLable.setFillColor(sf::Color::Red);
	highScoreLable.setOrigin({ highScoreLable.getGlobalBounds().size.x / 2, highScoreLable.getGlobalBounds().size.y / 2 });
	highScoreLable.setPosition({ (float)windowSize.x / 2 + 500 * (windowSize.x / 1920), (float)windowSize.y * .93f });
	

	//defines starting spawn rate of balls. decreases down to 3 seconds for difficulty increase
    float ballSpawnRate = 5;
    float pencilSpawnRate = 50.f;



    //Start game in the menu
    Menu menu(background.getTexture(), player.getTexture(), font, windowSize);
    menu.startMenu(window);

    menuMusic.stop();

    gameMusic.play();
    gameMusic.setLooping(true);



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
            float scale = 0.1f + ((float)(std::rand() % 5 + 1) / 60); // Between 0.1 and .15
            newBall.setScale({ scale, scale });
            balls.push_back(newBall);
            ball_spawn_clock.restart();
            if (ballSpawnRate > 1) ballSpawnRate -= 0.1f; // Decrease spawn rate to increase difficulty
            std::cout << "Number of balls: " << balls.size() << std::endl;
        }

        //spawn in a new pencil if pencil is shot
        if (pencils[pencils.size() - 1].getIsShooting() == true && pencil_spawn_clock.getElapsedTime().asMilliseconds() >= pencilSpawnRate)
        {
            // pencils.erase(pencils.begin()); // Remove the first (oldest) pencil


            Pencil newPencil(pencilTex, player.getPosition());
            pencils.push_back(newPencil);
            pencil_spawn_clock.restart();
        }


        //update all objects//


        //update all balls
        for (auto& ball : balls)
        {
            ball.update(window.getSize());
            if (ball.getHealth() <= 0)
            {
                score += ball.getOriginalHealth() * 8;
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
            if ((pencil.getIsHit() || pencil.getPosition().y < 0) && pencils.size() > 2)
            {
                //remove the pencil from the vector if it hits a book
                pencils.erase(std::remove_if(pencils.begin(), pencils.end(), [](const Pencil& p) { return p.getIsHit() || p.getPosition().y < 0; }), pencils.end());
            }
        }


        //check if pencils have hit a ball and if balls have hit the player
        for (auto& ball : balls)
        {
            if (checkIfPlayerIsHit(player, ball) && hitRestrictor.getElapsedTime().asSeconds() >= 1)
            {
                player.setHealth(player.getHealth() - 1);
                healthLabel.setString("Health = " + std::to_string(player.getHealth()));
                hitRestrictor.restart();
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
        window.draw(highScoreLable);

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

            player.setPosition({ (float)windowSize.x / 2.f, (float)windowSize.y / 1.5f });
            window.clear();
            GameOverScreen gameOverScreen(background.getTexture(), player.getTexture(), font, windowSize);
            gameOverScreen.run(window);
            ballSpawnRate = 5;
            highScoreLable.setString("High Score= " + std::to_string(checkHighScore(score)));
            score = 0;
            scoreLabel.setString("Score = 0");
            player.setHealth(5);
            healthLabel.setString("Health = 5");
            balls.clear();
        }
    }
    
    return 0;

}
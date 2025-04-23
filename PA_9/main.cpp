#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "menu.hpp"
#include "player.hpp"
#include "background.hpp"
#include "target.hpp"
#include "classInteractions.hpp"
#include "pencil.hpp"



int main()
{
    //window settings
    sf::VideoMode desktop = sf::VideoMode::getFullscreenModes()[0];
    unsigned int width = desktop.size.x * 1;
    unsigned int height = desktop.size.y * 1;
    sf::RenderWindow window(desktop, "Game", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar);
    sf::Vector2u windowSize = window.getSize();


    sf::Texture shipTexture;
    shipTexture.loadFromFile("PlayerShip.png");


    sf::Texture pencil;
    pencil.loadFromFile("pencil.png");


    sf::Music laserSound;
    laserSound.openFromFile("LaserGunPew.wav");

    sf::Music explosion;
    explosion.openFromFile("explosion.mp3");

    sf::Music track1;
    track1.openFromFile("track1.mp3");

    sf::Music hitmarker;
    hitmarker.openFromFile("hitmarker.mp3");


    track1.setVolume(50.0);

    laserSound.setVolume(40.0);


    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("Background.jpeg");

    background backgroundSprite(backgroundTexture, { 0.f, 0.f });

    Player playerShip(shipTexture, { windowSize.x / 2.f, windowSize.y / 1.3f }, true);//bool determines if the texture is or is not the spaceship

    Pencil pencilGun1(pencil, { windowSize.x / 2.f + 37.5f, windowSize.y / 1.3f });





    track1.play();

    Target ball1;

    bool pencil1fired = false;

    sf::Clock clock;



    while (window.isOpen())
    {


        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //For flashing lights on ball
        float deltaTime = clock.restart().asSeconds();
        ball1.update(deltaTime);
        //



        window.clear();
        window.draw(backgroundSprite);


        window.draw(pencilGun1);
        window.draw(playerShip);
        window.draw(ball1);



        




        

        window.setFramerateLimit(110);

        window.display();



        playerShip.playerActions(window, true);
        pencilGun1.pencilActions(window, laserSound);

        classInteractions::interactionHandler(laserSound, pencil1fired, pencilGun1, ball1, playerShip, explosion, hitmarker);

        

    }
}
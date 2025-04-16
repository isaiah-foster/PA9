#include <SFML/Graphics.hpp>
#include <vector>
#include "menu.hpp"
#include "player.hpp"

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


    sf::Music track1;
    track1.openFromFile("track3.mp3");


    track1.setVolume(50.0);
    
    
    Player playerShip(shipTexture, { windowSize.x / 2.f, windowSize.y / 1.3f }, true);//bool determines if the texture is or is not the spaceship

    Player pencilGun(pencil, { windowSize.x / 2.f, windowSize.y / 1.3f }, false);




    /*std::vector<sf::Sprite*> sprites;

    sprites.push_back(&playerShip);
    sprites.push_back(&pencilGun);*/


    track1.play();

    
    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(playerShip);
        window.draw(pencilGun);
        window.display();

        playerShip.playerActions(window, laserSound, true);
        pencilGun.playerActions(window, laserSound, false);

    }

}
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

    Player pencilGun1(pencil, { windowSize.x / 2.f + 37.5f, windowSize.y / 1.3f }, false);


    //Pencil 2 was commented out:

    //Player pencilGun2(pencil, { windowSize.x / 1.85f, windowSize.y / 1.3f }, false);

    

    


    track1.play();

    

    bool pencil1fired = false;
    //bool pencil2fired = false;


    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(pencilGun1);
        window.draw(playerShip);

        //window.draw(pencilGun2);
        window.display();


        sf::Vector2f playerPOS = playerShip.getPosition();
        sf::Vector2f pencilPOS1 = pencilGun1.getPosition() + sf::Vector2f(37.5f, 0.f);
        //sf::Vector2f pencilPOS2 = playerShip.getPosition();

        //pencilPOS2.x += .15f;

        playerShip.playerActions(window, laserSound, true);
        pencilGun1.playerActions(window, laserSound, false);
        //pencilGun2.playerActions(window, laserSound, false);


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) //log player location to terminal
        {
            std::cout << "Player Position: (" << playerPOS.x << ", " << playerPOS.y << ")" << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !pencil1fired) 
        {
            pencil1fired = true;
            //pencil2fired = true;
            laserSound.play();
        }
        


        if (pencil1fired && pencilGun1.getPosition().y < 100) 
        {

            pencilGun1.setPosition(playerShip.getPosition() + sf::Vector2f(37.5f, 0.f));


            //pencilGun2.setPosition(playerShip.getPosition());

            
            //pencilGun2.setPosition(playerShip.getPosition());


            pencil1fired = false;
            //pencil2fired = false;
        }
        

        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)))
        {

            pencilGun1.setPosition(playerShip.getPosition() + sf::Vector2f(37.5f, 0.f));

        }



    }

}
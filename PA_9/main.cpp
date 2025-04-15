#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "player.hpp"

int main()
{
    //window settings

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Fullscreen Window");
	float width = desktop.size.x * 1;
	float height = desktop.size.y * 1;
    sf::Vector2u windowSize = window.getSize();


    sf::Texture shipTexture;
    shipTexture.loadFromFile("PlayerShip.png");
	player playerShip(shipTexture, { width, height});


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
			

        }
        playerShip.movePlayer(windowSize);
        window.clear();
        window.draw(playerShip);
        window.display();

    }
}


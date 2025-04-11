#include <SFML/Graphics.hpp>
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
    shipTexture.loadFromFile("player_ship.png");
	player playerShip(shipTexture, { windowSize.x / 2.f, windowSize.y / 2.f });


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();


        }

        window.clear();
        window.draw(playerShip);
        window.display();

    }
}


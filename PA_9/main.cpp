#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "player.hpp"
#include "background.hpp"
#include "ball.hpp"

int main()
{
    //window settings

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "School Shooter");
	float width = desktop.size.x;
	float height = desktop.size.y;
    sf::Vector2u windowSize = window.getSize();
    sf::Texture playerTexture;
	sf::Texture backgroundTexture;
    playerTexture.loadFromFile("Player.png");
	backgroundTexture.loadFromFile("Background.jpeg");
	player playerSprite(playerTexture, { width, height});
	background backgroundSprite(backgroundTexture, { 0.f, 0.f });


    sf::Texture shipTexture;
    shipTexture.loadFromFile("PlayerShip.png");
	player playerShip(shipTexture, { width, height});

	sf::Texture ballTexture;
	ballTexture.loadFromFile("fBall.png");
	Ball ball(ballTexture);
	ball.setScale({ 0.1f, 0.1f });
    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
			

        }

	
		ball.update(windowSize);

        playerShip.movePlayer(windowSize);
        }
        
        playerSprite.movePlayer(windowSize);
        window.clear();
		window.draw(backgroundSprite);
        window.draw(playerSprite);
		window.draw(ball);
        window.draw(playerShip);
        window.display();

    }
}


#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "player.hpp"
#include "background.hpp"
#include "ball.hpp"
#include "ScoreB.hpp"

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
	player playerSprite({ width, height}, playerTexture);
	background backgroundSprite(backgroundTexture, { 0.f, 0.f });

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

        playerSprite.movePlayer(windowSize);


        playerSprite.movePlayer(windowSize);
        window.clear();
        window.draw(backgroundSprite);
        window.draw(playerSprite);
        window.draw(ball);
        window.draw(playerSprite);
        window.display();
        


    }
        return 0;
}
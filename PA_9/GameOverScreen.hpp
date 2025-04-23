#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "player.hpp"
#include "background.hpp"

class GameOverScreen {
public:
    GameOverScreen(const sf::Texture& backgroundTexture, const sf::Texture& playerTexture, const sf::Font& font, sf::Vector2u windowSize)
        : background(backgroundTexture), player({ (float)windowSize.x, (float)windowSize.y }, playerTexture), 
        gameOverText(font, "GAME OVER", 100), escapeCont(font, "Press Escape To Play Again", 50)
    {
        //set up the background
        background.setPosition({ 0,0 });
        background.setScale({
            (float)windowSize.x / background.getTextureRect().size.x,
            (float)windowSize.y / background.getTextureRect().size.y
            });

        //set up the player
        player.setPosition({ (float)windowSize.x / 2, (float)windowSize.y / 2 });
        player.setScale({ 0.5f, 0.5f }); // Adjust scale as needed
        player.setOrigin({ player.getGlobalBounds().size.x / 2, player.getGlobalBounds().size.y / 2 });

        //set up the "Game Over" text
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setOrigin({ gameOverText.getGlobalBounds().size.x / 2, gameOverText.getGlobalBounds().size.y / 2 });
        gameOverText.setPosition({ (float)windowSize.x / 2, (float)windowSize.y / 4.1f });

        //set up escape text
        escapeCont.setFillColor(sf::Color::Red);
        escapeCont.setOrigin({ escapeCont.getGlobalBounds().size.x / 2, escapeCont.getGlobalBounds().size.y / 2 });
        escapeCont.setPosition({ (float)windowSize.x / 2, (float)windowSize.y / 2.85f });

    }

    //function to run the game over screen
    bool run(sf::RenderWindow& window) {
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
            //restart the game if Escape is pressed
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                return true;


            //draw the game over screen
            window.clear();
            window.draw(background);
            window.draw(player);
            window.draw(gameOverText);
			window.draw(escapeCont);
            window.display();
            
        }
        return false; //if the window is closed, do not restart
    }


private:
    Background background;
    Player player;
    sf::Text gameOverText;
    sf::Text escapeCont;
};

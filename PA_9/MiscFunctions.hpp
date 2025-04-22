#pragma once
#include <SFML/Graphics.hpp>
#include "background.hpp"
#include "player.hpp"
#include <cstdlib>
#include <ctime>


//Set window to fullscreen, set framerate limit, and return window size
sf::RenderWindow initWindow()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(desktop, "Book Blaster", sf::Style::None);
	window.setFramerateLimit(120);
	sf::Vector2u windowSize = window.getSize();
	return window;
}


//Load player into memory
Player loadPlayer(sf::RenderWindow &window)
{
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Player.png");
	Player playerSprite({ (float)window.getSize().x, (float)window.getSize().y }, playerTexture);
	return playerSprite;
}


//Load background into memory
Background loadBackground()
{
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Backdrop.png");
	Background backgroundSprite(backgroundTexture, { 0.f, 0.f });
	return backgroundSprite;
}


//Load ball into memory
void loadBall()
{
	sf::Texture bookTextures[3];
	bookTextures[0].loadFromFile("Book.png");
	bookTextures[1].loadFromFile("Book2.png");
	bookTextures[2].loadFromFile("Book3.png");
	Ball ball(bookTextures[std::rand() % 3]);
	float scale = 0.05f + (static_cast<float>(std::rand() % 5 + 1) / 20); //Between 0.05 and 0.2
	ball.setScale({ scale, scale });
}
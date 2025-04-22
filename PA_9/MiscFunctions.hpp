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
	sf::RenderWindow window(desktop, "Book Blaster");
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
	backgroundTexture.loadFromFile("Background.jpeg");
	Background backgroundSprite(backgroundTexture, { 0.f, 0.f });
	return backgroundSprite;
}
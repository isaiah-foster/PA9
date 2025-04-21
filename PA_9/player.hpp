#pragma once

#include <SFML/graphics.hpp>
#include <string>
using std::string;
#define PLAYER_SCALE 0.15f
#define PLAYER_SPEED .2f

class player : public sf::Sprite
{
public:
    player(sf::Vector2f position = { 0.f, 0.f }, const sf::Texture& playerTexture = sf::Texture());
void movePlayer(sf::Vector2u windowSize);

private:
float speed;

};

player::player(sf::Vector2f position, const sf::Texture& playerTexture)
	: sf::Sprite(playerTexture) // Explicitly call the sf::Sprite constructor
{
//sf::Texture playerTexture;
//playerTexture.loadFromFile("Player.png"); // Load the player texture
setTexture(playerTexture); // Set the texture for the sprite
setPosition({ position.x /2 , position.y/1.5f });
setScale({ PLAYER_SCALE, PLAYER_SCALE });
speed = PLAYER_SPEED;
}


void player::movePlayer(sf::Vector2u windowSize)
{
	// Get the size of the texture
    sf::Vector2u spriteSize = (getTexture().getSize());

    sf::Vector2f position = getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        if (position.x > 0)
            move({ -speed, 0 });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) 
        if (position.x + PLAYER_SCALE*spriteSize.x < windowSize.x) // *.1 to match scale
            move({ speed, 0 });
}
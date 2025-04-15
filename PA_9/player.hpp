#pragma once

#include <SFML/graphics.hpp>
#include <string>
using std::string;
#define PLAYER_SCALE 0.15f
#define PLAYER_SPEED 4

class player : public sf::Sprite
{
public:
player(const sf::Texture& texture, sf::Vector2f position = { 0.f, 0.f });
void movePlayer(sf::Vector2u windowSize);

private:
float speed;

};

player::player(const sf::Texture& texture, sf::Vector2f position)
: sf::Sprite(texture) // Explicitly call the sf::Sprite constructor with the texture
{
setPosition({ position.x /2 , position.y/1.2f });
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
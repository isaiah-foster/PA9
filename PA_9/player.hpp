#pragma once

#include <SFML/graphics.hpp>
#include <string>
using std::string;

class player : public sf::Sprite
{
public:
player(const sf::Texture& texture, sf::Vector2f position = { 0.f, 0.f });
void movePlayer();

private:
float speed;

};

player::player(const sf::Texture& texture, sf::Vector2f position)
: sf::Sprite(texture) // Explicitly call the sf::Sprite constructor with the texture
{
setPosition({ position.x, position.y });
setScale({ 0.1f, 0.1f });
speed = 3;
}


void player::movePlayer()
{
	// Get the size of the texture
    sf::Vector2u spriteSize = (getTexture().getSize());

    // Input handling (arrow keys or WASD)
    sf::Vector2f position = getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        if (position.x > 0)
            move({ -speed, 0 });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
   //     if (position.x + spriteSize.x < windowSize.x)
            move({ speed, 0 });
    }
}
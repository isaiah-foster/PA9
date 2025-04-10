#pragma once

#include <SFML/graphics.hpp>
#include <string>
using std::string;

class PlayerShip : public sf::Sprite
{
public:
PlayerShip(const sf::Texture& texture, sf::Vector2f position = { 0.f, 0.f });
void moveShip();

private:
float speed;
};

PlayerShip::PlayerShip(const sf::Texture& texture, sf::Vector2f position)
: sf::Sprite(texture) // Explicitly call the sf::Sprite constructor with the texture
{
setPosition({ position.x, position.y });
setScale({ 0.1f, 0.1f });
speed = 3;
}


void PlayerShip::moveShip()
{
    // Input handling (arrow keys or WASD)
    sf::Vector2f position = getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        if (position.x > 0)
            move({ -speed, 0 });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        if (position.x + spriteSize.x < windowSize.x)
            move({ speed, 0 });
    }

    // Move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        if (position.y > 0)
            playerShip.move({ 0, -speed });
    }

    // Move down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        if (position.y + spriteSize.y < windowSize.y)
            playerShip.move({ 0, speed });
    }

}
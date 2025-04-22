#pragma once

#include <SFML/graphics.hpp>
#include <string>
using std::string;
#define PLAYER_SCALE 0.15f
#define PLAYER_SPEED 6.f

class Player : public sf::Sprite
{
public:
    Player(sf::Vector2f position = { 0.f, 0.f }, const sf::Texture& playerTexture = sf::Texture());

    void movePlayer(sf::Vector2u windowSize);

private:
    sf::Texture texture; // Store the texture as a member variable
    float speed;
};

Player::Player(sf::Vector2f position, const sf::Texture& playerTexture)
    : sf::Sprite(playerTexture), texture(playerTexture) // Initialize the member texture
{
    setTexture(texture); // Use the member texture
    setPosition({ position.x / 2, position.y / 1.5f });
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    setScale({ PLAYER_SCALE * desktop.size.x / 1920, PLAYER_SCALE * desktop.size.x / 1920 });
    speed = PLAYER_SPEED * (static_cast<float>(desktop.size.x) / 1920);
}


void Player::movePlayer(sf::Vector2u windowSize)
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
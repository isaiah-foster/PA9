#pragma once
#include <SFML/graphics.hpp>
#include <string>
using std::string;

#define BACKGROUND_SCALE 7.f

class background : public sf::Sprite
{
public:
	background(const sf::Texture& texture, sf::Vector2f position = { 0.f, 0.f });
	void setPosition(sf::Vector2f position);
	void setScale(float scale);
private:
	float scale;
};

background::background(const sf::Texture& texture, sf::Vector2f position)
	: sf::Sprite(texture) // Explicitly call the sf::Sprite constructor with the texture
{
	setPosition(position);
	setScale(BACKGROUND_SCALE);
}

void background::setPosition(sf::Vector2f position)
{
	sf::Sprite::setPosition(position);
}

void background::setScale(float scale)
{
	sf::Sprite::setScale({ scale, scale });
	this->scale = scale;
}
#pragma once
#include <SFML/graphics.hpp>
#include <string>
using std::string;

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
	: sf::Sprite(texture) //call the sf::Sprite constructor with the texture
{
	setPosition(position);
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	//set the scale of the background to fit the screen no matter resolution or aspect ratio
	desktop.size.x / texture.getSize().x > desktop.size.y / texture.getSize().y ?
		setScale(desktop.size.x / texture.getSize().x) : 
		setScale(desktop.size.y/texture.getSize().y);
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



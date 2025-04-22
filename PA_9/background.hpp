#pragma once  
#include <SFML/graphics.hpp>  
#include <string>  
using std::string;  

class Background : public sf::Sprite  
{  
public:  
  Background(const sf::Texture& texture, sf::Vector2f position = { 0.f, 0.f });  

private:  
  sf::Texture texture; // Store the texture as a member variable  
  float scale;  
};  

Background::Background(const sf::Texture& texture, sf::Vector2f position)  
  : sf::Sprite(texture), texture(texture) // Initialize the member texture  
{  
  setTexture(this->texture); // Use the member texture  
  setPosition(position);  
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  
  setScale({ (float)desktop.size.x/ texture.getSize().x , (float)desktop.size.y / texture.getSize().y });
}
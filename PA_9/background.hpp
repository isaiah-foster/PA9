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
  float scaleFactor = desktop.size.x / static_cast<float>(texture.getSize().x) >  
                      desktop.size.y / static_cast<float>(texture.getSize().y) ?  
                      desktop.size.x / static_cast<float>(texture.getSize().x) :  
                      desktop.size.y / static_cast<float>(texture.getSize().y);  
  setScale({ scaleFactor, scaleFactor }); // Pass sf::Vector2f instead of float  
}  

//void Background::setPosition(sf::Vector2f position)  
//{  
//  sf::Sprite::setPosition(position);  
//}  
//
//void Background::setScale(float scale)  
//{  
//  sf::Sprite::setScale({ scale, scale });  
//  this->scale = scale;  
//}

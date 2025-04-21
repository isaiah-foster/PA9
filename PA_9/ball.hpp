#pragma once  
#include <SFML/graphics.hpp>  
#include <cmath>  

class Ball : public sf::Sprite {  
public:  
   Ball(const sf::Texture& tex)  
       : sf::Sprite(tex), velocity(sf::Vector2f{ 0.f, 0.f }) {  
       setOrigin(sf::Vector2f{  
           static_cast<float>(tex.getSize().x) / 2.f,  
           static_cast<float>(tex.getSize().y) / 2.f  
       });  
   }  

   void setVelocity(sf::Vector2f v) {  
       velocity = v;  
   }  

   sf::Vector2f getVelocity() const {  
       return velocity;  
   }  

   void update(sf::Vector2u windowSize);  

private:  
   sf::Vector2f velocity;  
};  

void Ball::update(sf::Vector2u windowSize) {  

   const float bounceFactor = 1.0f;


   move(velocity);  

   sf::Vector2f pos = getPosition();  
   float radius = getGlobalBounds().size.x / 2.f;

   // Bottom  
   if (pos.y + radius >= static_cast<float>(windowSize.y)) {  
       setPosition({ pos.x, static_cast<float>(windowSize.y) - radius });  
       velocity.y = -velocity.y * bounceFactor;
       if (std::abs(velocity.y) < 5.f) velocity.y = 0.f;  
   }  

   // Top  
   if (pos.y - radius <= 0.f) {  
       setPosition({ pos.x, radius });  
       velocity.y = -velocity.y * bounceFactor;  
   }  

   // Left  
   if (pos.x - radius <= 0.f) {  
       setPosition({ radius, pos.y });  
       velocity.x = -velocity.x * bounceFactor;  
   }  

   // Right  
   if (pos.x + radius >= static_cast<float>(windowSize.x)) {  
       setPosition({ static_cast<float>(windowSize.x) - radius, pos.y });  
       velocity.x = -velocity.x * bounceFactor;  
   }  
}
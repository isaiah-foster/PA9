#pragma once  
#include <SFML/graphics.hpp>  
#include <cmath>  

class Ball : public sf::Sprite {  
public:  
   Ball(const sf::Texture& tex)  
       : sf::Sprite(tex), velocity(sf::Vector2f{ -.2, -.2 }) {  
       setOrigin(sf::Vector2f{
           static_cast<float>(tex.getSize().x) / 2.f,
           static_cast<float>(tex.getSize().y) / 2.f  ,
          
       });  
   }  

   void setVelocity(sf::Vector2f v) {  
       velocity = v;  
   }  

   sf::Vector2f getVelocity() const {  
       return velocity;  
   }  

   void update(sf::Vector2u windowSize);  

   void moderateSpeed();

private:  
   sf::Vector2f velocity;  
};  

void Ball::update(sf::Vector2u windowSize) {  

   const float bounceFactor = 1.0f;

   moderateSpeed(); // keep speed in check

   move(velocity);  

   sf::Vector2f pos = getPosition();  
   float radius = getGlobalBounds().size.x / 2.f;

   // Bottom  
   if (pos.y + radius >= static_cast<float>(windowSize.y)) {  
       setPosition({ pos.x, static_cast<float>(windowSize.y) - radius });  
       velocity.y = -velocity.y * bounceFactor; //bounce the ball
	   velocity.x -= 0.1f; //slow down the ball slightly on bounce
   }  

   // Top  
   if (pos.y - radius <= 0.f) {  
       setPosition({ pos.x, radius });  
       velocity.y = -velocity.y * bounceFactor;  
	   velocity.x -= 0.1f; //slow down the ball slightly on bounce
   }  

   // Left  
   if (pos.x - radius <= 0.f) {  
       setPosition({ radius, pos.y });  
       velocity.x = -velocity.x * bounceFactor;  
	   velocity.y -= 0.1f; //slow down the ball slightly on bounce
   }  

   // Right  
   if (pos.x + radius >= static_cast<float>(windowSize.x)) {  
       setPosition({ static_cast<float>(windowSize.x) - radius, pos.y });  
       velocity.x = -velocity.x * bounceFactor;  
	   velocity.y -= 0.1f; //slow down the ball slightly on bounce
   }  
}


void Ball::moderateSpeed() 
{
    if (velocity.x > .7)
        velocity.x = 0.7f;
    else if (velocity.x < -.7)
        velocity.x = 0.7f;
    if (velocity.y > .7)
        velocity.y = 0.7f;
    else if (velocity.y < -.7)
        velocity.y = 0.7f;
}
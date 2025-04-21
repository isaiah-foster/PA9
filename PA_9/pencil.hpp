#pragma once
#ifndef PENCIL_HPP
#define PENCIL_HPP

#include <SFML/Audio.hpp>
#include "player.hpp"


class Pencil : public sf::Sprite
{
public:



    //constructor creates a pencil
   Pencil(const sf::Texture& texture, sf::Vector2f position = { 0.3f, 0.f }) ://the plus 50 offsets the starting position of the pencils to be located right underneath the spaceship
        sf::Sprite(texture), speed(.00002F)
   {
        setPosition(position);
        setScale(sf::Vector2f(0.1f, 0.1f));//adjust to change pencil size
   }
   
    


   void pencilActions(const sf::RenderWindow& window, sf::Music& laserSound)
   {

       sf::Vector2f movement(0.f, 0.f); //variable to track movement

       sf::Vector2u windowSize = window.getSize(); //get the window size

       //get the current position of the player
       sf::Vector2f playerPosition = getPosition();

       //move left
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && playerPosition.x > 0)
           movement.x -= speed;

       //move right
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && playerPosition.x < windowSize.x - getTexture().getSize().x * getScale().x)
           movement.x += speed;

       //move up
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && playerPosition.y > 700)
           movement.y -= speed;

       //move down
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && playerPosition.y + getTexture().getSize().y * getScale().y < windowSize.y + 100)
           movement.y += speed;




       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))//shoot laser
       {
           setIsShooting(true);



           movement.y -= 100;
          


           laserSound.play();
       }



       




       



       move(movement);
   }

   bool getIsShooting()const//get value of isShooting
   {
       return isShooting;
   }

   void setIsShooting(bool isShootingNewValue)
   {
       isShooting = isShootingNewValue;
   }
   
   /*~Pencil()
   {
       std::cout << "Pencil destructor invoked" << std::endl;
   }*/

private:

    float speed;
    bool isShooting;
};

#endif

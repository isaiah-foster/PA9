#pragma once

#ifndef CLASSINTERACTIONS_HPP
#define CLASSINTERACTIONS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cmath>
#include "player.hpp"
#include "target.hpp"
#include "pencil.hpp"
#include "ball.hpp"


class classInteractions
{
private:



public:



    static bool checkShotHit(const Pencil& bullet, const Target& enemy)
    {
        if (bullet.getIsShooting())
        {

            float bulletX = bullet.getPosition().x;
            float enemyX = enemy.getPosition().x;

            float bulletY = bullet.getPosition().y;
            float enemyY = enemy.getPosition().y;


            float tolerance = 60.f; // adjust this to change hitboxes


            return (std::abs(bulletX - enemyX) < tolerance) &&
                (std::abs(bulletY - enemyY) < tolerance);
                
        }

        return false;
    }



    //handles 
    static void interactionHandler(sf::Music& laserSound, bool pencil1fired, Pencil& pencilGun1, Target& ball1, Player& playerShip, sf::Music& explosion, sf::Music& hitmarker)
    {




        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !pencil1fired)
        {

            pencil1fired = true;
            laserSound.play();


        }
        else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)))
        {

            pencil1fired = false;

            pencilGun1.setIsShooting(false);

        }




        if (classInteractions::checkShotHit(pencilGun1, ball1))
        {
            
            hitmarker.play();


            if (ball1.getHealth() == 0)
            {
                explosion.play();
            }


            std::cout << "TARGET HIT!\n" << std::endl;
        }
        else
        {

            //std::cout << "BIG BALLS NOT HIT!\n" << std::endl;

        }


        



        if ((pencil1fired && pencilGun1.getPosition().y < 100))
        {



            pencilGun1.setPosition(playerShip.getPosition() + sf::Vector2f(37.5f, 0.f));



            pencil1fired = false;
        }


        if (classInteractions::checkShotHit(pencilGun1, ball1))
        {
            pencilGun1.setPosition(playerShip.getPosition() + sf::Vector2f(37.5f, 0.f));

            ball1.decrementHealth();
        }

        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)))
        {

            pencilGun1.setPosition(playerShip.getPosition() + sf::Vector2f(37.5f, 0.f));

        }


        std::cout << ball1.getHealth() << std::endl;


        
    }

};



#endif
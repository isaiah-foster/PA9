#pragma once

#ifndef CLASSINTERACTIONS_HPP
#define CLASSINTERACTIONS_HPP

#include <SFML/Graphics.hpp>
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


            float tolerance = 50.f; // adjust this to change hitboxes


            return (std::abs(bulletX - enemyX) < tolerance) &&
                (std::abs(bulletY - enemyY) < tolerance);
                
        }

        return false;
    }



    static void interactionHandler(sf::Music& laserSound, bool pencil1fired, Pencil& pencilGun1, Target& ball1, Player& playerShip)
    {


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !pencil1fired)
        {

            pencil1fired = true;
            //pencil2fired = true;
            laserSound.play();

            //std::cout << "AW LAWD HE SHEWTIN" << std::endl;

        }
        else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)))
        {

            pencil1fired = false;

            pencilGun1.setIsShooting(false);

        }




        if (classInteractions::checkShotHit(pencilGun1, ball1))
        {

            std::cout << "TARGET HIT!\n" << std::endl;

        }
        else
        {

            std::cout << "BIG BALLS NOT HIT!\n" << std::endl;

        }




        if ((pencil1fired && pencilGun1.getPosition().y < 100) || (classInteractions::checkShotHit(pencilGun1, ball1)))
        {



            pencilGun1.setPosition(playerShip.getPosition() + sf::Vector2f(37.5f, 0.f));



            pencil1fired = false;
        }


        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)))
        {

            pencilGun1.setPosition(playerShip.getPosition() + sf::Vector2f(37.5f, 0.f));

        }





    }

    




};



#endif
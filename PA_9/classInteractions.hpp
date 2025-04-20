#pragma once

#ifndef CLASSINTERACTIONS_HPP
#define CLASSINTERACTIONS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "player.hpp"
#include "target.hpp"

class classInteractions
{
private:


	
public:
	
    static bool checkShotHit(const Player& bullet, const target& enemy)
    {
        if (bullet.getIsShooting())
        {
            float bulletX = bullet.getPosition().x;
            float enemyX = enemy.getPosition().x;

            float tolerance = 10.f; // You can adjust this
            return std::abs(bulletX - enemyX) < tolerance;
        }

        return false;
    }

};



#endif
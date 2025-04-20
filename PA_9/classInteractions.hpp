#pragma once

#ifndef CLASSINTERACTIONS_HPP
#define CLASSINTERACTIONS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "player.hpp"
#include "target.hpp"
#include "pencil.hpp"

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

            float tolerance = 10.f; // adjust this to change hitboxes
            return std::abs(bulletX - enemyX) < tolerance;
        }

        return false;
    }

};



#endif
#pragma once

#ifndef TARGET_HPP
#define TARGETHPP

#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics/Shape.hpp>
#include <cstddef>
#include <SFML/Graphics/Export.hpp>
#include <cstdint>

using std::string;

class Target : public sf::Drawable
{
public:


    Target() : health(20)
    {

        circle.setRadius(50.f);
        circle.setFillColor(sf::Color::Red);
        circle.setOrigin(sf::Vector2f(50.f, 50.f)); // center the origin
        circle.setPosition(sf::Vector2f(400.f, 300.f)); // default position

    }

    sf::FloatRect getBounds() const
    {
        return circle.getGlobalBounds();
    }
    

    void setPosition(float x, float y) 
    {
        circle.setPosition(sf::Vector2f(x, y));
    }

    sf::Vector2f getPosition() const 
    {
        return circle.getPosition();
    }

    float getRadius() const 
    {
        return circle.getRadius();
    }



    int getHealth()const
    {
        return health;
    }

    void setHealth(int newHealth)
    {
        health = newHealth;
    }



    void decrementHealth()
    {
        if (health > 0)
        {
            health -= 1;
            if (health == 0)
            {
                isExploding = true;
                flashTimer = 0.2f; // Flash duration in seconds
                

                
                

            }
        }
    }


    void update(float deltaTime)
    {
        if (isExploding)
        {
            if (flashTimer > 0.0f)
            {
                flashTimer -= deltaTime;
                circle.setFillColor(sf::Color::White);
            }
            else
            {
                // Fade out after flash
                if (fadeAlpha > 0)
                {
                    fadeAlpha = std::max(0, fadeAlpha - static_cast<int>(deltaTime * 255));
                    circle.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(fadeAlpha)));
                }
            }
        }
    }

    bool isDead() const
    {
        return health <= 0 && fadeAlpha == 0;
    }

       
private:

    sf::CircleShape circle;
    int health;
    bool isExploding;
    int fadeAlpha;
    float flashTimer;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(circle, states);
    }
    

};


#endif
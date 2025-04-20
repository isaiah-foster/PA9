#pragma once

#ifndef TARGET_HPP
#define TARGETHPP

#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics/Shape.hpp>
#include <cstddef>
#include <SFML/Graphics/Export.hpp>

using std::string;

class target : public sf::Drawable
{
public:
    sf::FloatRect getBounds() const
    {
        return circle.getGlobalBounds();
    }


    target() 
    {
        circle.setRadius(50.f);
        circle.setFillColor(sf::Color::Red);
        circle.setOrigin(sf::Vector2f(50.f, 50.f)); // center the origin
        circle.setPosition(sf::Vector2f(400.f, 300.f)); // default position
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

private:

    sf::CircleShape circle;

    //required draw override from sf::Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
    {
        target.draw(circle, states);
    }

};


#endif
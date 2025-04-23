#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ball.hpp"

class Player : public sf::Sprite 
{
public:

    float original_yaxis;
    float original_xaxis;

    

    //constructor that initializes the player with a texture and an optional position
    Player(const sf::Texture& texture, sf::Vector2f position = { 0.f, 0.f }, bool isSpaceShip = true)
        : sf::Sprite(texture), speed(50.0f), original_yaxis(position.y), original_xaxis(position.x)
    {
        setPosition(position);
        setScale({ 0.1f, 0.1f });  //adjust scale if needed

    }




    //constructor creates a pencil using the player class
    //Player(const sf::Texture& texture, bool isSpaceShip = false, bool respawn = false, sf::Vector2f position = { 0.3f + 50.f, 0.f }) ://the plus 50 offsets the starting position of the pencils to be located right underneath the spaceship
    //    sf::Sprite(texture), speed(.5f)
    //{
    //    position = getPosition();
    //}



    



    // Function to move the player based on keyboard input and window size
    void playerActions(const sf::RenderWindow& window, bool isSpaceShip)
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




        


        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && isSpaceShip)
        {
           // std::cout << "current speed: " << movement.x << "  " << movement.y << std::endl;

        }
        
        

        move(movement);
    }





    //this function checks if the player is hit by a target/book
    static bool checkIfPlayerIsHit(const Player& player, const Ball& ball)
    {
        float playerX = player.getPosition().x;
        float playerY = player.getPosition().y;

        float ballX = ball.getPosition().x;
        float ballY = ball.getPosition().y;

        float tolerance = 50.f; // tweak this to change the hit box of the player

        return (std::abs(playerX - ballX) < tolerance) &&
            (std::abs(playerY - ballY) < tolerance);
    }

    


    void decrementPlayerHealth()
    {
        if (health > 0)
        {
            health -= 1;
            
        }
    }


    bool checkIfPlayerIsDead()
    {
        if (health == 0)
        {
            return true;
            //end game and reset
        }
        else
        {
            return false;
        }
    }

private:

    int health;
    float speed;
};

#endif
#include <SFML/Audio.hpp>

class Player : public sf::Sprite 
{
public:

    float original_yaxis;
    float original_xaxis;

    

    //constructor that initializes the player with a texture and an optional position
    Player(const sf::Texture& texture, sf::Vector2f position = { 0.f, 0.f }, bool isSpaceShip = true)
        : sf::Sprite(texture), speed(3.0f), original_yaxis(position.y), original_xaxis(position.x)
    {
        setPosition(position);
        setScale({ 0.1f, 0.1f });  //adjust scale if needed

    }




    //constructor creates a pencil using the player class
    Player(const sf::Texture& texture, bool isSpaceShip = false, bool respawn = false, sf::Vector2f position = { 0.3f + 50.f, 0.f }) :
        sf::Sprite(texture), speed(.5f)
    {
        position = getPosition();
    }



    



    // Function to move the player based on keyboard input and window size
    void playerActions(const sf::RenderWindow& window, sf::Music& laserSound, bool isSpaceShip)
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




        //THIS is kinda dumb. the pencil constructor is only invoked when the player shoots. But it works
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !isSpaceShip)//shoot laser
        {


            movement.y -= 15;
            movement.y -= 15;
            movement.y -= 15;
            



            laserSound.play();
        }


        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && isSpaceShip)
        {
            std::cout << "current speed: " << movement.x << "  " << movement.y << std::endl;

        }
        



        /*if (!isSpaceShip)
        {

            if (playerPosition.y > 500)
            {
                setPosition(savePencilLoco);
                return;
            }

        }*/
            
        

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


private:
    bool isShooting;


    float speed;
};
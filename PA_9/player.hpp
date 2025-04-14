class Player : public sf::Sprite {
public:
    // Constructor that initializes the player with a texture and an optional position
    Player(const sf::Texture& texture, sf::Vector2f position = { 0.f, 0.f })
        : sf::Sprite(texture), speed(3.0f)
    {
        setPosition(position);
        setScale({ 0.1f, 0.1f });  // Adjust scale as needed
    }

    // Function to move the player based on keyboard input and window size
    void movePlayer(const sf::RenderWindow& window)
    {
        sf::Vector2f movement(0.f, 0.f); // Variable to track movement

        sf::Vector2u windowSize = window.getSize(); // Get the window size

        // Get the current position of the player
        sf::Vector2f playerPosition = getPosition();

        // Prevent player from moving outside the bounds of the window (invisible box)
        // Move Left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && playerPosition.x > 0)
            movement.x -= speed;

        // Move Right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && playerPosition.x < windowSize.x - getTexture().getSize().x * getScale().x)
            movement.x += speed;

        // Move Up
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && playerPosition.y > 700)
            movement.y -= speed;

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && playerPosition.y + getTexture().getSize().y * getScale().y < windowSize.y - 100)
            movement.y += speed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))//shoot laser
        {

        }

        // Apply movement to the player sprite
        move(movement);
    }

private:
    float speed; // Speed of player movement
};

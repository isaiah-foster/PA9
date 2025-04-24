#include <iostream>
#include <SFML/Audio.hpp>

class TestCases
{
public:

    //run all test cases
    bool testAll()
    {
        if (testAudioFilesLoaded() && testTextureLoading() && testProjectileCleanupWithoutImage())
        {
            return true;
        }
        else
        {
            return false;
        }
        

    }

	//test case for loading audio files
    bool testAudioFilesLoaded()
    {
        std::vector<std::string> audioFiles = {
            "danceWeapon4.mp3",
            "track1.mp3",
            "LaserGunPew.wav",
            "pencil_hit.mp3",
            "pencil_hit.mp3"
        };

        bool allLoaded = true;
        for (const auto& file : audioFiles)
        {
            sf::Music testMusic;
            if (!testMusic.openFromFile(file))
            {
                std::cout << "Error: Failed to load audio file: " << file << std::endl;
                allLoaded = false;
                return false;
            }
            else
            {
                std::cout << "Loaded successfully: " << file << std::endl;
                return true;
            }
        }
        return allLoaded;
    }



    bool testTextureLoading() 
    {
        sf::Texture book1, book2, book3, pencil, playerTex, backgroundTex;

        bool allLoaded =
            book1.loadFromFile("Book.png") &&
            book2.loadFromFile("Book2.png") &&
            book3.loadFromFile("Book3.png") &&
            pencil.loadFromFile("pencil.png") &&
            playerTex.loadFromFile("player.png") &&
            backgroundTex.loadFromFile("background.png");

        if (allLoaded) 
        {
            std::cout << "Texture loading test passed\n";
            return true;
        }
        else 
        {
            std::cout << "Texture loading test failed\n";
            return false;
        }

        return allLoaded;
    }


    bool testProjectileCleanupWithoutImage()
        {
        sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Test Window");
        sf::Music dummyMusic;
        Player player;

        // Declare a dummy texture — no need to load from image
        sf::Texture dummyTexture;

        //makes some pencils
        std::vector<Pencil> projectiles;
        for (int i = 0; i < 5; ++i) {
            projectiles.emplace_back(dummyTexture, sf::Vector2f(100.f, 500.f));
            projectiles.back().setIsShooting(true);
        }

        //simulation
        for (int frame = 0; frame < 100; ++frame) {
            for (auto& pencil : projectiles) {
                pencil.update(window, dummyMusic, player);
            }

            //remove pencils that have moved off screen
            projectiles.erase(
                std::remove_if(projectiles.begin(), projectiles.end(),
                    [&](const Pencil& pencil) {
                        return pencil.getPosition().y < 0;
                    }),
                projectiles.end()
            );
        }

        //test results
        if (projectiles.empty()) 
        {
            std::cout << "Projectile Cleanup Test Passed\n";
            return true;
        }
        else
        {
            std::cout << "Projectile Cleanup Test Failed: " << projectiles.size() << " projectiles still exist.\n";
            return false;
        }
    }


};


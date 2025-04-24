#include <iostream>
#include <SFML/Audio.hpp>

bool testAudioFilesLoaded() {
    std::vector<std::string> audioFiles = {
        "danceWeapon4.mp3",
        "track1.mp3",
        "LaserGunPew.wav",
        "pencil_hit.mp3"
    };

    bool allLoaded = true;
    for (const auto& file : audioFiles) {
        sf::Music testMusic;
        if (!testMusic.openFromFile(file)) {
            std::cerr << "Error: Failed to load audio file: " << file << std::endl;
            allLoaded = false;
        }
        else {
            std::cout << "Loaded successfully: " << file << std::endl;
        }
    }

    return allLoaded;
}

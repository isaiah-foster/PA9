#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include "menu.hpp"
#include "player.hpp"
#include "background.hpp"
#include "ball.hpp"
#include "Windows.h"
#include "MiscFunctions.hpp"
#include <vector>
#include <string>
#include "pencil.hpp"

#include "GameOverScreen.hpp"

class TestCases {
public:
    void testFunctions(){
        testCheckHighScore();
    }

private:
    void testCheckHighScore() {
        
        std::ofstream file("HighScore.txt");
        file << 40;
        file.close();

        
        int result = checkHighScore(75);

        
        std::ifstream verify("HighScore.txt");
        int fileScore;
        verify >> fileScore;
        verify.close();

        
        if (result == 75 && fileScore == 75) {
            std::cout << "Test passed: high score was updated correctly.\n";
        }
        else {
            std::cout << "Test failed!\n";
            std::cout << "Returned: " << result << ", File Score: " << fileScore << std::endl;
        }
    }
};
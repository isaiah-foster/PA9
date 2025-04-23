#pragma once
#include <SFML/graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


class ScoreBoard {
public:
	ScoreBoard() {
		this->score = 0;
		TimePlayed time;
		time.min = 0;
		time.sec = 0;
		this->playTime = time;
		this->objectsHit = 0;
		this->HighScore = nullptr;



	}

	struct TimePlayed {
		int min;
		int sec;
	};
	void setScore(int newScore) {
		score = newScore;

	}

	int getScore() {
		return score;
	}


	void setPlayTime(int minutes, int seconds) {
		playTime.min = minutes;
		playTime.sec = seconds;
	}
	TimePlayed getPlaytime() {
		return playTime;
	}

	void setObjectsHit(int input) {
		objectsHit = input;
	}
	int getObjectsHit() {
		return objectsHit;
	}

	void LoadHighScore() {
		std::ifstream file("HighScore.txt");

		ScoreBoard* High = new ScoreBoard();

		std::string line;
		int token1, token2;

		// reads the score
		std::getline(file, line, ':');
		std::getline(file, line);
		token1 = std::stoi(line);
		High->setScore(token1);

		// reads the time
		std::getline(file, line, ':');
		std::getline(file, line, ':');
		token1 = std::stoi(line);
		std::getline(file, line);
		token2 = std::stoi(line);
		High->setPlayTime(token1, token2);

		// reads the objects hit
		std::getline(file, line, ':');
		std::getline(file, line);
		token1 = std::stoi(line);
		High->setObjectsHit(token1);


		file.close();

		// sets highscore based on file readings
		HighScore = High;




	}
	void setHighScore(ScoreBoard* input) {
		HighScore = input;
	}

	ScoreBoard* getHighScore() {
		return HighScore;
	}
	void saveHighScore() {
		std::ofstream file("HighScore.txt");




		file << "Score:" << HighScore->getScore() << std::endl;
		file << "TimePlayed:" << HighScore->getPlaytime().min << ":" << HighScore->getPlaytime().sec << std::endl;
		file << "ObjectsHit:" << HighScore->getObjectsHit() << std::endl;

		file.close();

	}

	void updateHighScore() {
		if (score > HighScore->getScore()) {
			ScoreBoard* newHigh = new ScoreBoard();

			newHigh->setScore(score);
			newHigh->setPlayTime(playTime.min, playTime.sec);
			newHigh->setObjectsHit(objectsHit);

			newHigh->setHighScore(newHigh);

			HighScore = newHigh;

		}
	}
	void displayHighScore() {

	}
	void loadFont(sf::Font& font, std::string str) {
		if (!font.openFromFile(str)) {
			std::cerr << "Error" << std::endl;
		}
	}

private:
	int score;
	TimePlayed playTime;
	int objectsHit;
	ScoreBoard* HighScore;



};
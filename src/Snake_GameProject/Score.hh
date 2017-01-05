#pragma once
#include "FruitSpawn.hh"

class Score {
public:
	int score = 0;
	int highscore;

	void addScore() {
		if(FruitSpawn::EatFruit) score += 10;
	}

	void newHighscore() {
		if (score > highscore) {
			highscore = score;
		}
	}
};
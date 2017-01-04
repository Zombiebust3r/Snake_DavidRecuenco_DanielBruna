#pragma once

class Score {
public:
	int score = 0;
	int highscore;

	void addScore();
};

void Score::addScore() {
	score += 10;
}
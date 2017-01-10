#pragma once
namespace {
	class Score {
	public:
		int score;
		int highscore;
		int lifes;

		void addScore();
		void decreaseLifes();
	};

	void Score::addScore() {
		score += 100;
		if (score > highscore) {
			highscore = score;
		}
	}

	void Score::decreaseLifes() {
		lifes--;
		if (lifes == 0) {
			// LA SNAKE MUERE, DE UNA MANERA MUY HORRIBLE
		}
	}
}
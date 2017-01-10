#pragma once
namespace {
	class Score {
	public:
		int score;
		int highscore;
		int lifes;

		void addScore(int fruits);
		bool decreaseLifes();
	};

	void Score::addScore(int fruits) {
		score += 100*fruits;
		if (score > highscore) {
			highscore = score;
		}
	}

	bool Score::decreaseLifes() {
		lifes--;
		if (lifes == 0) {
			return true;
		}
		return false;
	}
}
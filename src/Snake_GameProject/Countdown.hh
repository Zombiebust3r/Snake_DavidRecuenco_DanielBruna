#pragma once
#include "SnakeGrid.hh"
namespace {
	class Countdown {
	public:
		int time;
		Sprite bar;
		bool timer(Mode mode);
		void drawTimer();
		void resetTimer();
	};

	bool Countdown::timer(Mode mode) {
		if (time <= 0) return true;
		else if (time > 0) {
			bar = { { 0, 120, time, 15 }, ObjectID::TIMEBAR };
			switch (mode) {
			case EASY: time -= 1; break;
			case MEDIUM: time -= 2; break;
			case HARD: time -= 3; break;
			}
			return false;
		}
		return false;
	}

	void Countdown::drawTimer() {
		bar.Draw();
	}

	void Countdown::resetTimer() {
		time = W.GetWidth();
	}
}
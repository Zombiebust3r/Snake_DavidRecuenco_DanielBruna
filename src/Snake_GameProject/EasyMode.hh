#pragma once
#include "Sprite.hh"
#include "Scene.hh"

#include "FruitSpawn.hh"
#include "Snake.hh"
#include "Score.hh"

// GameScene class with the main gameplay mode
class EasyMode : public Scene {
public:
	explicit EasyMode();
	~EasyMode() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	bool beatedHighScore;
	Score score;
	Snake snake;
	FruitSpawn fruit;
	Sprite background;
};
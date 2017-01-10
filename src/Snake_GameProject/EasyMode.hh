#pragma once
#include "Scene.hh"

#include "FruitSpawn.hh"

// GameScene class with the main gameplay mode
class EasyMode : public Scene {
public:
	explicit EasyMode();
	~EasyMode() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	
	int fruitsEaten;
	int mode;

	Score score;
	int highscore;
	SnakeGrid grid;
	Snake snake;
	FruitSpawn fruit;
	Sprite background;

	int tiempoEjecutar;
};
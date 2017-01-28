#pragma once
#include "Scene.hh"
#include "XML_FUNCTIONS.hh"
#include "FruitSpawn.hh"

// GameScene class with the main gameplay mode
class HardMode : public Scene {
public:
	explicit HardMode();
	~HardMode() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

	int fruitsEaten;
	// No necesita en fruitCount ya que no hace falta saber cuantas se come seguidas para saber si pasar al siguiente nivel (no hay siguiente nivel)

	Score score;
	int highscore;
	SnakeGrid grid;
	Snake snake;
	FruitSpawn fruit;
	Sprite background;
	Countdown timer;
	int tiempoEjecutar;
	int tiempoInicial;

	int r, c, z, x, y, t;
};
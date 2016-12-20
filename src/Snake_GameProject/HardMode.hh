#pragma once
#include "Sprite.hh"
#include "Scene.hh"

// GameScene class with the main gameplay mode
class HardMode : public Scene {
public:
	explicit HardMode();
	~HardMode() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	bool beatedHighScore;

	Sprite background;
};
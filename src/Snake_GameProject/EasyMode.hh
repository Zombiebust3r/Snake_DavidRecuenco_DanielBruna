#pragma once
#include "Sprite.hh"
#include "Scene.hh"

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

	Sprite background;
};
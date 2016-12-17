#pragma once
#include "Grid.hh"
#include "Scene.hh"

// GameScene class with the main gameplay mode
class MainMenu : public Scene {
public:
	explicit MainMenu();
	~MainMenu() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite background;
	Sprite easy;
	Sprite medium;
	Sprite hard;
	Sprite exit;
};
#pragma once

#include <GameConfig.h>
#include <GameObject.h>
#include <SDL.h>

enum PaddleType
{
	Left,
	Right
};

class Paddle : public GameObject
{
public:
	Paddle(PaddleType _type);

	void HandleEvent(SDL_Event& e) override;

	void Move(double deltaTime) override;

private:
	PaddleType type;
	PaddleKeybind keybind;
};
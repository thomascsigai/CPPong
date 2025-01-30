#pragma once

#include <GameConfig.h>
#include <Djipi.h>
#include <SDL.h>

enum PaddleType
{
	Left,
	Right
};

class Paddle : public Djipi::GameObject
{
public:
	Paddle(PaddleType _type);

	void HandleEvent(SDL_Event& e) override;

	void Update(double deltaTime) override;

private:
	PaddleType type;
	PaddleKeybind keybind;
};
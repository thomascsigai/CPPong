#pragma once

#include <GameConfig.h>
#include <SDL.h>

enum PaddleType
{
	Left,
	Right
};

class Paddle
{
public:
	static const int PADDLE_WIDTH = 5;
	static const int PADDLE_HEIGHT = 75;
				 
	static const int PADDLE_SPEED = 10;

	Paddle(PaddleType _type);

	void HandleEvent(SDL_Event& e);

	void Move();

	void Render(SDL_Renderer* renderer);

private:
	PaddleType type;
	PaddleKeybind keybind;

	int posX, posY;
	int velY;
};
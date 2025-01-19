#pragma once

#include <GameConfig.h>
#include <SDL.h>

class Ball
{
public:
	static const int BALL_SIZE = 5;
	static const int BALL_SPEED = 5;

	Ball();

	void Move();

	void Render(SDL_Renderer* renderer);

private:
	int posX, posY;
	int velX, velY;
};
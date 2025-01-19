#pragma once

#include <GameConfig.h>
#include <SDL.h>

class Ball
{
public:
	Ball();

	void Move();

	void Render(SDL_Renderer* renderer);

private:
	int posX, posY;
	int velX, velY;
};
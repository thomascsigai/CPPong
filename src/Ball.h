#pragma once

#include <GameConfig.h>
#include <SDL.h>

class Ball
{
public:
	Ball();

	void Move();

	void Render(SDL_Renderer* renderer);

	void OnCollide();

	SDL_Rect GetCollider();

private:
	int posX, posY;
	int velX, velY;

	SDL_Rect collider;
};
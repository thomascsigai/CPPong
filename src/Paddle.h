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
	Paddle(PaddleType _type);

	void HandleEvent(SDL_Event& e);

	void Move();

	void Render(SDL_Renderer* renderer);

	SDL_Rect GetCollider();

private:
	PaddleType type;
	PaddleKeybind keybind;

	int posX, posY;
	int velY;

	SDL_Rect collider;
};
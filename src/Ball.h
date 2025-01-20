#pragma once

#include <GameConfig.h>
#include <GameObject.h>
#include <SDL.h>

class Ball : public GameObject
{
public:
	Ball();

	void Move() override;

	void Render(SDL_Renderer* renderer) override;

	void OnCollide(GameObject other) override;

	void OnCollide()
	{
		velX *= -1;
	}
};
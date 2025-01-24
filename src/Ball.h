#pragma once

#include <GameConfig.h>
#include <GameObject.h>
#include <Timer.h>
#include <SDL.h>
#include <UserEvents.h>

class Ball : public GameObject
{
public:
	Ball();

	void Move(double deltaTime) override;

	void OnCollide(GameObject& other) override;

private:
	// Events
	SDL_Event OnBallOut = { UserEvents::BALL_OUT };
};
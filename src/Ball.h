#pragma once

#include <Djipi.h>
#include <SDL.h>
#include <UserEvents.h>

class Ball : public Djipi::GameObject
{
public:
	Ball();

	void Move(double deltaTime) override;

	void OnCollide(GameObject& other) override;

private:
	// Events
	SDL_Event OnBallOut = { UserEvents::BALL_OUT };

	Djipi::Timer serveTimer;
};
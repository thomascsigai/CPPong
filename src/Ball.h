#pragma once

#include <Djipi.h>
#include <SDL.h>
#include <UserEvents.h>

class Ball : public Djipi::GameObject
{
public:
	Ball();

	void Update(double deltaTime) override;

	void OnCollide(GameObject& other) override;

private:
	// Events
	SDL_Event OnBallOut = { UserEvents::BALL_OUT };
	SDL_Event OnWallTouch = { UserEvents::WALL_TOUCH };

	Djipi::Timer serveTimer;
};
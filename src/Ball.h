#pragma once

#include <GameConfig.h>
#include <GameObject.h>
#include <Timer.h>
#include <SDL.h>

class Ball : public GameObject
{
public:
	Ball();

	void Move(double deltaTime) override;

	void OnCollide(GameObject& other) override;
};
#include <Ball.h>

Ball::Ball()
{
	posX = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
	posY = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;

	velX = BALL_SPEED;
	velY = BALL_SPEED;
}

void Ball::Render(SDL_Renderer* renderer)
{
	SDL_Rect ballRect = { posX, posY, BALL_SIZE, BALL_SIZE };
	SDL_RenderFillRect(renderer, &ballRect);
}

void Ball::Move()
{
	// Checks for screen up and down collision to rebound
	if (posY >= SCREEN_HEIGHT - BALL_SIZE || posY <= BALL_SIZE)
	{
		velY *= -1;
	}

	// Checks for screen left and right collision (point scored)
	if (posX >= SCREEN_WIDTH - BALL_SIZE || posX <= BALL_SIZE)
	{
		velX *= -1;
	}
	
	posX += velX;
	posY += velY;
}
#include <Ball.h>
#include <Paddle.h>

Ball::Ball()
{
	transform.SetPosition(SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2);
	transform.SetSize(BALL_SIZE, BALL_SIZE);

	velX = BALL_SPEED;
	velY = BALL_SPEED;
}

void Ball::Render(SDL_Renderer* renderer)
{
	SDL_Rect ballRect = { transform.x, transform.y, BALL_SIZE, BALL_SIZE };
	SDL_RenderFillRect(renderer, &ballRect);

	//Debug draw collider

	/*SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &transform.collider);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);*/
}

void Ball::Move()
{
	// Checks for screen up and down collision to rebound
	if (transform.y >= SCREEN_HEIGHT - BALL_SIZE || transform.y <= BALL_SIZE)
	{
		velY *= -1;
	}

	// Checks for screen left and right collision (point scored)
	if (transform.x >= SCREEN_WIDTH - BALL_SIZE || transform.x <= BALL_SIZE)
	{
		transform.SetPosition(SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2);
	}
	
	GameObject::Move();
}

void Ball::OnCollide(GameObject& other)
{
	if (typeid(other) == typeid(Paddle))
	{
		velX *= -1;
	}
}
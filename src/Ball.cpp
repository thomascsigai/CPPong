#include <Ball.h>
#include <Paddle.h>

Ball::Ball()
{
	transform.SetPosition(SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2);
	transform.SetSize(BALL_SIZE, BALL_SIZE);

	velX = BALL_SPEED;
	velY = BALL_SPEED;
}

void Ball::Move(double deltaTime)
{
	// Checks for screen up and down collision to rebound
	if (transform.y < 0)
	{
		velY *= -1;
		// Set ball position to avoid reinvert
		transform.SetPosition(transform.x, 1);
	}
	if (transform.y > SCREEN_HEIGHT - BALL_SIZE)
	{
		velY *= -1;
		// Set ball position to avoid reinvert
		transform.SetPosition(transform.x, SCREEN_HEIGHT - BALL_SIZE - 1);
	}

	// Checks for screen left and right collision (point scored)
	if (transform.x >= SCREEN_WIDTH - BALL_SIZE || transform.x <= BALL_SIZE)
	{
		transform.SetPosition(SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2);
	}
	
	GameObject::Move(deltaTime);
}

void Ball::OnCollide(GameObject& other)
{
	if (typeid(other) == typeid(Paddle))
	{
		velX *= -1;
	}
}
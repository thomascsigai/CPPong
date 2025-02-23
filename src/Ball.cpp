#include <Ball.h>
#include <Paddle.h>

Ball::Ball()
{
	m_Transform.SetPosition(SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2);
	m_Transform.SetSize(BALL_SIZE, BALL_SIZE);

	velX = BALL_SPEED;
	velY = BALL_SPEED;

	serveTimer = Djipi::Timer();
	serveTimer.Start();
}

void Ball::Update(double deltaTime)
{
	if (serveTimer.IsStarted())
	{
		if (serveTimer.GetTicks() >= BALL_SERVE_TIME) serveTimer.Stop();
		else return;
	}

	// Checks for screen up collision to rebound
	if (m_Transform.y < 0)
	{
		velY *= -1;
		// Set ball position to avoid reinvert
		m_Transform.SetPosition(m_Transform.x, 1);
		SDL_PushEvent(&OnWallTouch);
	}

	// Checks for screen down collision to rebound
	if (m_Transform.y > SCREEN_HEIGHT - BALL_SIZE)
	{
		velY *= -1;
		// Set ball position to avoid reinvert
		m_Transform.SetPosition(m_Transform.x, SCREEN_HEIGHT - BALL_SIZE - 1);
		SDL_PushEvent(&OnWallTouch);
	}

	// Checks for screen left and right collision (point scored)
	if (m_Transform.x >= SCREEN_WIDTH - BALL_SIZE || m_Transform.x <= BALL_SIZE)
	{
		OnBallOut.user.data1 = &velX;
		SDL_PushEvent(&OnBallOut);
		m_Transform.SetPosition(SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2);

		serveTimer.Start();
	}

	GameObject::Move(deltaTime);
}

void Ball::OnCollide(GameObject& other)
{
	if (typeid(other) == typeid(Paddle))
	{
		// -sign(velX) * (1 + BALL_SIZE)
		float newPosX = other.GetTransform().x + -(velX / abs(velX)) * (1 + BALL_SIZE);

		velX *= -1;

		// Teleport ball next to the paddle to avoid unwanted collisions
		m_Transform.SetPosition(newPosX, m_Transform.y);
	}
}
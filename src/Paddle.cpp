#include <Paddle.h>

Paddle::Paddle(PaddleType _type) : type(_type)
{
	int x = (type == PaddleType::Left) ? 50 : SCREEN_WIDTH - 50;
	int y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

	m_Transform.SetPosition(x, y);
	m_Transform.SetSize(PADDLE_WIDTH, PADDLE_HEIGHT);

	keybind = (type == PaddleType::Left) ? LEFT_PADDLE_KEYBIND : RIGHT_PADDLE_KEYBIND;
}

void Paddle::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if (e.key.keysym.sym == keybind.UP) velY -= PADDLE_SPEED;
		if (e.key.keysym.sym == keybind.DOWN) velY += PADDLE_SPEED;
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		if (e.key.keysym.sym == keybind.UP) velY += PADDLE_SPEED;
		if (e.key.keysym.sym == keybind.DOWN) velY -= PADDLE_SPEED;
	}
}

void Paddle::Move(double deltaTime)
{
	m_Transform.y += velY * deltaTime;

	if (m_Transform.y <= 0 || m_Transform.y >= SCREEN_HEIGHT - PADDLE_HEIGHT)
	{
		m_Transform.y -= velY * deltaTime;
	}

	m_Transform.UpdateCollider();
}
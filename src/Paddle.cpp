#include <Paddle.h>

Paddle::Paddle(PaddleType _type) : type(_type)
{
	int x = (type == PaddleType::Left) ? 50 : SCREEN_WIDTH - 50;
	int y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

	transform.SetPosition(x, y);
	transform.SetSize(PADDLE_WIDTH, PADDLE_HEIGHT);

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
	transform.y += velY * deltaTime;

	if (transform.y <= 0 || transform.y >= SCREEN_HEIGHT - PADDLE_HEIGHT)
	{
		transform.y -= velY * deltaTime;
	}

	transform.UpdateCollider();
}
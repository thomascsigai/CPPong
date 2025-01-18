#include <Paddle.h>

Paddle::Paddle(PaddleType _type) : type(_type)
{
	posX = (type == PaddleType::Left) ? 50 : SCREEN_WIDTH - 50;
	posY = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

	velY = 0;

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

void Paddle::Move()
{
	posY += velY;

	if (posY <= 0 || posY >= SCREEN_HEIGHT - PADDLE_HEIGHT)
	{
		posY -= velY;
	}
}

void Paddle::Render(SDL_Renderer* renderer)
{
	SDL_Rect paddleRect = { posX, posY, PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_RenderFillRect(renderer, &paddleRect);
}
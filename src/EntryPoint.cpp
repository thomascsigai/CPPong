// Defines application entry point.
//

#include <string>

#include <Djipi.h>
#include <GameConfig.h>
#include <UserEvents.h>

#include <Paddle.h>
#include <Ball.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The renderer
SDL_Renderer* gRenderer = NULL;

// Font used in game
TTF_Font* gFont = NULL;
// Texture score P1
Djipi::Texture gScoreTextureP1;
// Texture score P2
Djipi::Texture gScoreTextureP2;

// Sounds
Mix_Chunk* gBallTouchSound = NULL;
Mix_Chunk* gPointScoreSound = NULL;

// Players scores
static Uint16 gScoreP1 = 0;
static Uint16 gScoreP2 = 0;

// Draws the divider line in the middle of the screen
void DrawDividers()
{
	const int NUMBER_OF_DIVIDERS = SCREEN_HEIGHT / (DIVIDER_HEIGHT + SPACE_BETWEEN_DIVIDERS);

	for (int i = 0; i < NUMBER_OF_DIVIDERS; i++)
	{
		int newPosX = SCREEN_WIDTH / 2 - DIVIDER_WIDTH / 2;
		int newPosY = i * (DIVIDER_HEIGHT + SPACE_BETWEEN_DIVIDERS);
		
		SDL_Rect newDiv = { newPosX, newPosY, DIVIDER_WIDTH, DIVIDER_HEIGHT };
		SDL_RenderFillRect(gRenderer, &newDiv);
	}
}

bool CheckCollision(SDL_FRect a, SDL_FRect b)
{
	float leftA, rightA, topA, bottomA;
	float leftB, rightB, topB, bottomB;

	leftA = a.x;	rightA  = a.x + a.w;
	topA  = a.y;	bottomA = a.y + a.h;

	leftB = b.x;	rightB  = b.x + b.w;
	topB  = b.y;	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB) return false;
	if (topA >= bottomB) return false;
	if (rightA <= leftB) return false;
	if (leftA >= rightB) return false;

	//If none of the sides from A are outside B
	return true;
}

bool LoadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont(BIT_FONT_DIR_PATH, 75);
	if (gFont == NULL)
	{
		printf("Failed to load bit font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 255, 255 };
		if (!gScoreTextureP1.LoadFromRenderedText(to_string(gScoreP1), textColor, gFont, gRenderer))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gScoreTextureP2.LoadFromRenderedText(to_string(gScoreP2), textColor, gFont, gRenderer))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	gBallTouchSound = Mix_LoadWAV(BALL_TOUCH_SOUND_DIR_PATH);
	if (gBallTouchSound == NULL)
	{
		printf("Failed to load ball touch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	
	gPointScoreSound = Mix_LoadWAV(POINT_SCORE_SOUND_DIR_PATH);
	if (gPointScoreSound == NULL)
	{
		printf("Failed to load point score sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

bool UpdateScore()
{
	bool success = true;

	if (gFont == NULL)
	{
		cerr << "Failed to load bit font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 255, 255 };
		if (!gScoreTextureP1.LoadFromRenderedText(to_string(gScoreP1), textColor, gFont, gRenderer))
		{
			cerr << "Failed to render text texture!" << endl;
			success = false;
		}
		if (!gScoreTextureP2.LoadFromRenderedText(to_string(gScoreP2), textColor, gFont, gRenderer))
		{
			cerr << "Failed to render text texture!" << endl;
			success = false;
		}
	}

	if (gPointScoreSound != NULL)
	{
		Mix_PlayChannel(-1, gPointScoreSound, 0);
	}
	else
	{
		cerr << "Failed to play score point sound effect!" << endl;
		success = false;
	}

	return success;
}

int main(int argc, char* argv[])
{
	bool quit = false;

	SDL_Event e;

	Djipi::Window appWindow = Djipi::Window();
	appWindow.Init();

	gWindow = appWindow.GetWindow();
	gRenderer = appWindow.GetRenderer();

	Paddle leftPaddle = Paddle(PaddleType::Left);
	Paddle rightPaddle = Paddle(PaddleType::Right);

	Ball ball = Ball();

	Uint64 previousTime = SDL_GetTicks();
	Uint64 currentTime;
	double deltaTime;

	if (!LoadMedia())
	{
		cerr << "Failed to load media !" << endl;
	}

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			else if (e.type == UserEvents::BALL_OUT)
			{
				int ballDir = *static_cast<int*>(e.user.data1) > 0 ? gScoreP1++ : gScoreP2++;
				UpdateScore();
			}

			else if (e.type == UserEvents::WALL_TOUCH)
			{
				Mix_PlayChannel(-1, gBallTouchSound, 0);
			}

			leftPaddle.HandleEvent(e);
			rightPaddle.HandleEvent(e);
		}

		currentTime = SDL_GetTicks();
		deltaTime = (double)(currentTime - previousTime) / 1000;
		previousTime = currentTime;
		
		rightPaddle.Update(deltaTime);
		leftPaddle.Update(deltaTime);

		ball.Update(deltaTime);

		if (CheckCollision(ball.GetCollider(), leftPaddle.GetCollider()))
		{
			Mix_PlayChannel(-1, gBallTouchSound, 0);
			ball.OnCollide(leftPaddle);
		}
		if (CheckCollision(ball.GetCollider(), rightPaddle.GetCollider()))
		{
			Mix_PlayChannel(-1, gBallTouchSound, 0);
			ball.OnCollide(rightPaddle);
		}

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

		DrawDividers();

		leftPaddle.Render(gRenderer);
		rightPaddle.Render(gRenderer);

		ball.Render(gRenderer);

		gScoreTextureP1.Render(SCREEN_WIDTH / 4 - gScoreTextureP1.GetWidth() / 2, 50, gRenderer);
		gScoreTextureP2.Render(3 * SCREEN_WIDTH / 4 - gScoreTextureP1.GetWidth() / 2, 50, gRenderer);

		SDL_RenderPresent(gRenderer);
	}

	appWindow.Close();

	return 0;
}
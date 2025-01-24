// Defines application entry point.
//

#include <GameConfig.h>
#include <Paddle.h>
#include <Ball.h>
#include <Timer.h>
#include <Texture.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <UserEvents.h>

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The renderer
SDL_Renderer* gRenderer = NULL;

// Font used in game
TTF_Font* gFont = NULL;
// Texture score P1
Texture gScoreTextureP1;
// Texture score P2
Texture gScoreTextureP2;

static Uint16 gScoreP1 = 0;
static Uint16 gScoreP2 = 0;

bool Init()
{
	bool success = true;

	// SDL Initialization
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "SDL could not initialize ! SDL_Error: " << SDL_GetError() << endl;
	}
	else
	{
		// Create Window
		gWindow = SDL_CreateWindow("GameDev QuickStart", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			cerr << "Window could not be created ! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			// Create Renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer == NULL)
			{
				cerr << "Renderer could not be created ! SDL_Error: " << SDL_GetError() << endl;
				success = false;
			}

			if (TTF_Init() < 0)
			{
				cerr << "SDL_ttf could not initialize : " << TTF_GetError() << endl;
				success = false;
			}
		}
	}

	return success;
}

void Close()
{
	// Free score textures
	gScoreTextureP1.Free();
	gScoreTextureP2.Free();

	// Close font
	TTF_CloseFont(gFont);
	gFont = NULL;

	// Destroy Renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	// Destroy Window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	TTF_Quit();
	SDL_Quit();
}

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

	return success;
}

int main(int argc, char* argv[])
{
	bool quit = false;

	SDL_Event e;

	Init();

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
				int ballDir = *static_cast<int*>(e.user.data1) > 0 ? 1 : -1;
				if (ballDir < 0) cout << "P1 : " << gScoreP1 << " P2 : " << ++gScoreP2 << endl;
				else cout << "P1 : " << ++gScoreP1 << " P2 : " << gScoreP2 << endl;
			}

			leftPaddle.HandleEvent(e);
			rightPaddle.HandleEvent(e);
		}

		currentTime = SDL_GetTicks();
		deltaTime = (double)(currentTime - previousTime) / 1000;
		previousTime = currentTime;
		
		rightPaddle.Move(deltaTime);
		leftPaddle.Move(deltaTime);

		ball.Move(deltaTime);

		if (CheckCollision(ball.GetCollider(), leftPaddle.GetCollider())) ball.OnCollide(leftPaddle);
		if (CheckCollision(ball.GetCollider(), rightPaddle.GetCollider())) ball.OnCollide(rightPaddle);

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

		DrawDividers();

		leftPaddle.Render(gRenderer);
		rightPaddle.Render(gRenderer);

		ball.Render(gRenderer);

		gScoreTextureP1.Render(0, 50, gRenderer);
		gScoreTextureP2.Render(0, 50, gRenderer);

		SDL_RenderPresent(gRenderer);
	}

	Close();

	return 0;
}
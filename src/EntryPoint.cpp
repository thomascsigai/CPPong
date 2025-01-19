// Defines application entry point.
//

#include <GameConfig.h>
#include <Paddle.h>
#include <Ball.h>
#include <Timer.h>
#include <SDL.h>

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The renderer
SDL_Renderer* gRenderer = NULL;

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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (gRenderer == NULL)
			{
				cerr << "Renderer could not be created ! SDL_Error: " << SDL_GetError() << endl;
				success = false;
			}
		}
	}

	return success;
}

void ProcessEvents(SDL_Event& e, bool& quit)
{
	
}

void Close()
{
	// Destroy Renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	// Destroy Window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

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

int main(int argc, char* argv[])
{
	bool quit = false;

	SDL_Event e;

	Init();

	Paddle leftPaddle = Paddle(PaddleType::Left);
	Paddle rightPaddle = Paddle(PaddleType::Right);

	Ball ball = Ball();

	Timer fpsTimer = Timer();
	
	//Start counting frames per second
	int countedFrames = 0;
	fpsTimer.Start();

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			leftPaddle.HandleEvent(e);
			rightPaddle.HandleEvent(e);
		}
		
		rightPaddle.Move();
		leftPaddle.Move();

		ball.Move();
				
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

		DrawDividers();

		leftPaddle.Render(gRenderer);
		rightPaddle.Render(gRenderer);

		ball.Render(gRenderer);

		SDL_RenderPresent(gRenderer);
		
		//Calculate and correct fps
		/*float avgFPS = countedFrames / (fpsTimer.GetTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}
		cout << "Average FPS : " << avgFPS << endl;*/

		++countedFrames;
	}

	Close();

	return 0;
}
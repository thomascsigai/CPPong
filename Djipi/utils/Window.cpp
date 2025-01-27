#include <Window.h>

namespace Djipi
{
	Window::Window()
	{
		mWindow = NULL;
		mRenderer = NULL;
	}

	bool Window::Init()
	{
		bool success = true;

		// SDL Initialization
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			std::cerr << "SDL could not initialize ! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			// Create Window
			mWindow = SDL_CreateWindow("CPPong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

			if (mWindow == NULL)
			{
				cerr << "Window could not be created ! SDL_Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				// Create Renderer
				mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

				if (mRenderer == NULL)
				{
					cerr << "Renderer could not be created ! SDL_Error: " << SDL_GetError() << endl;
					success = false;
				}

				if (TTF_Init() < 0)
				{
					cerr << "SDL_ttf could not initialize : " << TTF_GetError() << endl;
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}

		return success;
	}

	void Window::Close()
	{
		// Destroy Renderer
		SDL_DestroyRenderer(mRenderer);
		mRenderer = NULL;

		// Destroy Window
		SDL_DestroyWindow(mWindow);
		mWindow = NULL;

		Mix_Quit();
		TTF_Quit();
		SDL_Quit();
	}
}
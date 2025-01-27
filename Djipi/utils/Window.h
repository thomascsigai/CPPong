#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>
#include <GameConfig.h>

namespace Djipi
{
	class Window
	{
	public:
		Window();

		bool Init();

		void Close();

		SDL_Window* GetWindow() { return mWindow; }
		SDL_Renderer* GetRenderer() { return mRenderer; }

	private:
		SDL_Renderer* mRenderer;
		SDL_Window* mWindow;
	};
}
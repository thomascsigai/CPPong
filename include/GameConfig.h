#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

// WINDOW SETTINGS -------------------------------------------------

constexpr uint16_t SCREEN_WIDTH = 800;
constexpr uint16_t SCREEN_HEIGHT = 600;


// KEYBINDS ---------------------------------------------------------

// Paddles keybinds
struct PaddleKeybind
{
	SDL_Keycode UP;
	SDL_Keycode DOWN;
};

constexpr PaddleKeybind LEFT_PADDLE_KEYBIND = { SDLK_z, SDLK_s };
constexpr PaddleKeybind RIGHT_PADDLE_KEYBIND = { SDLK_UP, SDLK_DOWN };

#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

// WINDOW SETTINGS --------------------------------------------------

constexpr Uint16 SCREEN_WIDTH = 800;
constexpr Uint16 SCREEN_HEIGHT = 600;

// GAME SPECIFIC SETTINGS -------------------------------------------

// Divider in the middle of the screen
constexpr Uint16 DIVIDER_WIDTH = 2;
constexpr Uint16 DIVIDER_HEIGHT = 15;
constexpr Uint16 SPACE_BETWEEN_DIVIDERS = 10;

// KEYBINDS ---------------------------------------------------------

// Paddles keybinds
struct PaddleKeybind
{
	SDL_Keycode UP;
	SDL_Keycode DOWN;
};

constexpr PaddleKeybind LEFT_PADDLE_KEYBIND = { SDLK_z, SDLK_s };
constexpr PaddleKeybind RIGHT_PADDLE_KEYBIND = { SDLK_UP, SDLK_DOWN };

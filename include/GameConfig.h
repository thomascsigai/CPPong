#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

// WINDOW SETTINGS -------------------------------------------------

constexpr Uint16 SCREEN_WIDTH = 800;
constexpr Uint16 SCREEN_HEIGHT = 600;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


// KEYBINDS ---------------------------------------------------------

// Paddles keybinds
struct PaddleKeybind
{
	SDL_Keycode UP;
	SDL_Keycode DOWN;
};

constexpr PaddleKeybind LEFT_PADDLE_KEYBIND = { SDLK_z, SDLK_s };
constexpr PaddleKeybind RIGHT_PADDLE_KEYBIND = { SDLK_UP, SDLK_DOWN };

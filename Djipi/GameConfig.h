#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

// WINDOW SETTINGS --------------------------------------------------

constexpr Uint16 SCREEN_WIDTH = 800;
constexpr Uint16 SCREEN_HEIGHT = 600;



// RESOURCES SETTINGS ---------------------------------------------------

#define RESOURCES_DIR_PATH "resources/"

//fonts
#define BIT_FONT_DIR_PATH "resources/fonts/bit5x3.ttf"

//Sounds
#define BALL_TOUCH_SOUND_DIR_PATH "resources/sounds/ballTouch.wav"
#define POINT_SCORE_SOUND_DIR_PATH "resources/sounds/pointScore.wav"



// GAME SPECIFIC SETTINGS -------------------------------------------

// Divider in the middle of the screen
constexpr Uint16 DIVIDER_WIDTH = 2;
constexpr Uint16 DIVIDER_HEIGHT = 15;
constexpr Uint16 SPACE_BETWEEN_DIVIDERS = 10;

// Ball Settings
constexpr Uint16 BALL_SIZE = 5;
constexpr Uint16 BALL_SPEED = 500;

// Time before serving the ball and moving it (in ms)
constexpr Uint16 BALL_SERVE_TIME = 3000;

// Paddle Settings
static const int PADDLE_WIDTH = 5;
static const int PADDLE_HEIGHT = 75;

static const int PADDLE_SPEED = 750;

// KEYBINDS ---------------------------------------------------------

// Paddles keybinds
struct PaddleKeybind
{
	SDL_Keycode UP;
	SDL_Keycode DOWN;
};

constexpr PaddleKeybind LEFT_PADDLE_KEYBIND = { SDLK_z, SDLK_s };
constexpr PaddleKeybind RIGHT_PADDLE_KEYBIND = { SDLK_UP, SDLK_DOWN };

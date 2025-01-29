#pragma once

#include <SDL.h>

namespace UserEvents
{
	const inline Uint32 BALL_OUT = SDL_RegisterEvents(1);
	const inline Uint32 WALL_TOUCH = SDL_RegisterEvents(1);
}
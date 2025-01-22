#include <Timer.h>

Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;

	started = false;
	paused = false;
}

void Timer::Start()
{
	started = true;
	paused = false;
	
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void Timer::Stop()
{
	started = false;
	paused = false;

	startTicks = 0;
	pausedTicks = 0;
}

void Timer::Pause()
{
	if (started && !paused)
	{
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Timer::Unpause()
{
	if (started && paused)
	{
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

Uint32 Timer::GetTicks() const
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
		{
			time = pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

bool Timer::IsStarted() const
{
	return started;
}

bool Timer::IsPaused() const
{
	return paused && started;
}
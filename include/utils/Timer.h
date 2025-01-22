#pragma once

#include <GameConfig.h>
#include <SDL.h>

class Timer
{
public:
    Timer();

    void Start();
    void Stop();
    void Pause();
    void Unpause();

    Uint32 GetTicks() const;

    bool IsStarted() const;
    bool IsPaused() const;

private:
    Uint32 startTicks;
    Uint32 pausedTicks;

    bool paused;
    bool started;
};
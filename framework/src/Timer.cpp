/*
 * This proprietary software may be used only as
 * authorised by a licensing agreement from Botson Limited
 * (C) COPYRIGHT 2019 Botson Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Botson Limited.
 */

#include "Timer.h"
#include <sys/time.h>

namespace BotsonSDK
{
    Timer::Timer()
        : startTime()
        , currentTime()
        , lastIntervalTime(0.0f)
        , frameCount(0)
        , fpsTime(0.0f)
        , fps(0.0f)
    {    
        startTime.tv_sec = 0;
        startTime.tv_usec = 0;
        currentTime.tv_sec = 0;
        currentTime.tv_usec = 0;

        reset();
    }

    void Timer::reset()
    {
        gettimeofday(&startTime, NULL);
        lastIntervalTime = 0.0;

        frameCount = 0;
        fpsTime = 0.0f;
    }

    float Timer::getTime()
    {
        gettimeofday(&currentTime, NULL);
        float seconds = (currentTime.tv_sec - startTime.tv_sec);
        float milliseconds = (float(currentTime.tv_usec - startTime.tv_usec)) / 1000000.0f;
        return seconds + milliseconds;
    }

    float Timer::getInterval()
    {
        float time = getTime();
        float interval = time - lastIntervalTime;
        lastIntervalTime = time;
        return interval;
    }

    float Timer::getFPS()
    {
        if (getTime() - fpsTime > 1.0f)
        {
            fps = static_cast<float>(frameCount) / (getTime() - fpsTime);
            frameCount = 0;
            fpsTime = getTime();
        }
        ++frameCount;
        return fps;
    }
}

namespace BotsonSDK
{
    bool Timer::isTimePassed(float seconds)
    {
        float time = getTime();
        if (time - lastTime > seconds)
        {
            lastTime = time;
            return true;
        }
        return false;
    }
}

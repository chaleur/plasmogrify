///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Timer.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Timer for the Plasma Application
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Timer.h"
#include <windows.h>

namespace Plasmogrify
{
    namespace Application
    {
        Timer::Timer()
            : mLastCount(0)
            , mfSecondsPerCount(1.0f)
            , mfDeltaTime(0.0f)
        {
            uint64_t freq = 0;
            QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
            mfSecondsPerCount = 1.0f / (float)freq;

            QueryPerformanceCounter((LARGE_INTEGER*)&mLastCount);
        }

        Timer::~Timer()
        {
        }

        void Timer::Tick()
        {
            uint64_t count;
            QueryPerformanceCounter((LARGE_INTEGER*)&count);
            mfDeltaTime = (float)(count - mLastCount) * mfSecondsPerCount;
            if (mfDeltaTime < 0.0f) mfDeltaTime = 0.0f;
            mLastCount = count;
        }

        float Timer::GetDeltaTime()
        {
            return mfDeltaTime;
        }

    } // namespace Application
} // namespace Plasmogrify
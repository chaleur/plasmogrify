///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Timer.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Timer for the Plasma Application
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_APPLICATION_TIMER
#define PLASMOGRIFY_APPLICATION_TIMER

#include "Config.h"
#include <windows.h>

namespace Plasmogrify
{
    namespace Application
    {
        class Timer
        {
            public:
                Timer();
                ~Timer();

                void Tick();
                float GetDeltaTime();

            private:
                uint64_t    mLastCount;
                float       mfSecondsPerCount;
                float       mfDeltaTime;
        };

    } // namespace Application
} // namespace Plasmogrify

#endif // PLASMOGRIFY_APPLICATION_TIMER
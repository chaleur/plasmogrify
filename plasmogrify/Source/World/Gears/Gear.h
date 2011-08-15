///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Gear.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Gear for Gears Sample
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_WORLD_GEAR
#define PLASMOGRIFY_WORLD_GEAR

#include "../../System/Graphics/Model.h"

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            class Context;
            class Device;
        }
    }

    namespace World
    {
        namespace Gears
        {
            class Gear
            {
                public:
                    Gear();
                    ~Gear();

                public:
                    void Init(System::Graphics::Device* pDevice);
                    void Update(float dt);
                    void Draw(System::Graphics::Context* pContext);

                private:
                    bool                              mbInit;
                    System::Graphics::Model*          mpModel;
            };

        } // namespace Gears
    } // namespace World
} // namespace Plasmogrify

#endif // PLASMOGRIFY_WORLD_GEAR
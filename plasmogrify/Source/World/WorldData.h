///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        WorldData.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma WorldData
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_WORLDDATA
#define PLASMOGRIFY_WORLDDATA

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
            class GearBox;
        }

        class WorldData
        {
            public:
                WorldData();
                ~WorldData();

                void Cleanup();

                void Init(System::Graphics::Device* pDevice);
                void Update(float dt);

                void Draw(System::Graphics::Context* pContext);

            private:
                bool                   mbInit;
                Gears::GearBox*        mpGearBox;
                
        };

    } // namespace World
} // namespace Plasmogrify

#endif // PLASMOGRIFY_WORLDDATA
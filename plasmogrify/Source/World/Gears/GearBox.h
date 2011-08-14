///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        GearBox.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Gearbox for Gears Sample
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_WORLD_GEARBOX
#define PLASMOGRIFY_WORLD_GEARBOX

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
            class Gear;

            class GearBox
            {
                public:
                    GearBox();
                    ~GearBox();

                    void Init(System::Graphics::Device *pDevice);
                    void Update(float dt);

                    void Draw(System::Graphics::Context* pContext);

                private:
                    bool                mbInit;

                    // \\\ TODO: Make this a set of gears.
                    Gear*               mpGear; 
            };

        } // namespace Gears
    } // namespace World
} // namespace Plasmogrify

#endif // PLASMOGRIFY_WORLD_GEARBOX
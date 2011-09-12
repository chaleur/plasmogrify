///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        GearBox.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify GearBox for Gears Sample
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "GearBox.h"
#include "Gear.h"
#include "../../Config.h"

namespace Plasmogrify
{
    namespace World
    {    
        namespace Gears
        {
            GearBox::GearBox()
                : mbInit(false)
                , mpGear(NULL)
            {
            }

            GearBox::~GearBox()
            {
                if (mpGear)
                {
                    delete mpGear;
                    mpGear = NULL;
                }
            }

            void GearBox::Init(System::Graphics::Device *pDevice)
            {
                mbInit = true;
                mpGear = new Gear();
                mpGear->Init(pDevice);
            }

            void GearBox::Update(float dt)
            {
                mpGear->Update(dt);
            }

            void GearBox::Draw(System::Graphics::Context* pContext)
            {
                mpGear->Draw(pContext);
            }

        } // namespace Gears
    } // namespace World
} // namespace Plasmogrify
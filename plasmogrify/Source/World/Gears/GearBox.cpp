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
                , mpGear0(NULL)
                , mpGear1(NULL)
            {
            }

            GearBox::~GearBox()
            {
                if (mpGear0)
                {
                    delete mpGear0;
                    mpGear0 = NULL;
                }

                if (mpGear1)
                {
                    delete mpGear1;
                    mpGear1 = NULL;
                }
            }

            void GearBox::Init(System::Graphics::Device *pDevice)
            {
                if (mbInit)
                {
                    return;
                }

                mbInit = true;
                mpGear0 = new Gear();
                mpGear0->Init(pDevice, Gear::kGearType_Small);
                mpGear1 = new Gear();
                mpGear1->Init(pDevice, Gear::kGearType_Big);
            }

            void GearBox::Update(float dt)
            {
                mpGear0->Update(dt);
                mpGear1->Update(dt);
            }

            void GearBox::Draw(System::Graphics::Context* pContext)
            {
                mpGear0->Draw(pContext);
                mpGear1->Draw(pContext);
            }

        } // namespace Gears
    } // namespace World
} // namespace Plasmogrify
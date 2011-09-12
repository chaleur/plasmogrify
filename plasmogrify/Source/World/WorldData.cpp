///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        WorldData.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Application
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "WorldData.h"
#include "Gears/GearBox.h"
#include "../Config.h"

namespace Plasmogrify
{
    namespace World
    {    
        
        WorldData::WorldData()
            : mbInit(false)
            , mpGearBox(NULL)
        {
        }

        WorldData::~WorldData()
        {
        }

        void WorldData::Init(System::Graphics::Device* pDevice)
        {
            mbInit = true;
            mpGearBox = new Gears::GearBox();
            mpGearBox->Init(pDevice);
        }

        void WorldData::Cleanup()
        {
            if (mpGearBox)
            {
                delete mpGearBox;
                mpGearBox = NULL;
            }
        }

        void WorldData::Update(float dt)
        {
            mpGearBox->Update(dt);
        }

        void WorldData::Draw(System::Graphics::Context* pContext)
        {
            mpGearBox->Draw(pContext);
        }

    } // namespace World
} // namespace Plasmogrify
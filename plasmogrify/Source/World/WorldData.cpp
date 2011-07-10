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

        void WorldData::Init()
        {
            mbInit = true;

            mpGearBox = new Gears::GearBox();
            mpGearBox->Init();
        }

        void WorldData::Update()
        {
            // \\\TODO: Update World Data
        }

    } // namespace World
} // namespace Plasmogrify
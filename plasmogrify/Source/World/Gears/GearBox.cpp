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
            }

            void GearBox::Init()
            {
                mbInit = true;
                mpGear = new Gear();
            }

        } // namespace Gears
    } // namespace World
} // namespace Plasmogrify
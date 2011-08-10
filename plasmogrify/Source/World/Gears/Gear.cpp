///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Gear.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Gear for Gears Sample
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Gear.h"

namespace Plasmogrify
{
    namespace World
    {    
        namespace Gears
        {
            Gear::Gear()
                : mbInit(false)
                , mpVertexList(NULL)
            {
            }

            Gear::~Gear()
            {
                if (mpVertexList)
                {
                    delete mpVertexList;
                }
            }

            void Gear::Init()
            {
                mbInit = true;
                mpVertexList = new System::Graphics::VertexList();
            }

            void Gear::Update(float dt)
            {
            }

            void Gear::Draw()
            {
            }

        } // namespace Gears
    } // namespace World
} // namespace Plasmogrify
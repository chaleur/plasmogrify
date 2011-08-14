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

            void Gear::Init(System::Graphics::Device *pDevice)
            {
                mbInit = true;
                mpVertexList = new System::Graphics::VertexList();
                mpVertexList->Init(pDevice, System::Graphics::VertexList::kTriangle_Type1);
            }

            void Gear::Update(float dt)
            {
            }

            void Gear::Draw(System::Graphics::Context* pContext)
            {
                mpVertexList->Draw(pContext);
            }

        } // namespace Gears
    } // namespace World
} // namespace Plasmogrify
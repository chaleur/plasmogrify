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
                , mpModel(NULL)
            {
            }

            Gear::~Gear()
            {
                if (mpModel)
                {
                    delete mpModel;
                }
            }

            void Gear::Init(System::Graphics::Device *pDevice)
            {
                mbInit = true;
                mpModel = new System::Graphics::Model();
                mpModel->Init(pDevice, System::Graphics::Model::kTriangle_Type1);
            }

            void Gear::Update(float dt)
            {
            }

            void Gear::Draw(System::Graphics::Context* pContext)
            {
                mpModel->Draw(pContext);
            }

        } // namespace Gears
    } // namespace World
} // namespace Plasmogrify
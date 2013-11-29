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
            const uint32_t Gear::kSegments = 4;

            Gear::Gear()
                : mbInit(false)
                , mpModel(NULL)
            {
            }

            Gear::~Gear()
            {
                if (mpModel)
                {
                    mpModel->Cleanup();
                    delete mpModel;
                    mpModel = NULL;
                }
            }

            void Gear::Init(System::Graphics::Device *pDevice, eGearType gearType)
            {
                if (mbInit)
                {
                    return;
                }

                mbInit = true;

                mpModel = new System::Graphics::Model();
                BuildGear(gearType);
                mpModel->Init(pDevice);
            }

            void Gear::BuildGear(eGearType gearType)
            {
                uint32_t numVerts = kSegments * 3;
                mpModel->CreateVertexList(numVerts);

                uint32_t numIndicies = kSegments * 3;
                mpModel->CreateIndexList(numIndicies);

                XMFLOAT3 center = XMFLOAT3(0.45f, 0.00f, 0.0f);
                
                switch ( gearType )
                {
                    case kGearType_Small:
                    {
                        center = XMFLOAT3(0.00f, 0.10f, 0.0f);
                        break;
                    }
                    case kGearType_Big:
                    {
                        center = XMFLOAT3(0.00f, -0.45f, 0.0f);
                        break;
                    }
                }

                for (uint32_t i = 0; i < kSegments; ++i)
                {
                    uint32_t offset = i * 3;

                    float angle = (float)i / (2.0f * 3.1415926f);

                    mpModel->SetVertex(offset + 0, XMFLOAT3(0.0f, 0.5f + center.y, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
                    mpModel->SetVertex(offset + 1, XMFLOAT3(0.45f, 0.0f + center.y, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
                    mpModel->SetVertex(offset + 2, XMFLOAT3(-0.45f, 0.0f + center.y, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));

                    mpModel->SetIndex(offset + 0, offset + 0);
                    mpModel->SetIndex(offset + 1, offset + 1);
                    mpModel->SetIndex(offset + 2, offset + 2);
                }

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
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
                uint32_t numVerts = kSegments + 1;
                mpModel->CreateVertexList(numVerts);

                uint32_t numIndicies = kSegments * 3;
                mpModel->CreateIndexList(numIndicies);

                uint32_t vertex = 0;
                uint32_t index = 0;

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

				static XMFLOAT4 kColorHack[5] =
				{
					XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
					XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f),
										XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f),
															XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),
																				XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
				};

				mpModel->SetVertex(vertex, XMFLOAT3(0.0f, center.y, 0.0f), kColorHack[vertex] );
                ++vertex;

                float angleIncrement = (2.0f * 3.1415926f) / kSegments;
                for (uint32_t i = 0; i < kSegments; ++i)
                {

                    float angle = i * angleIncrement;
                    float cosAngle = cos(angle) * 0.5f;
                    float sinAngle = sin(angle) * 0.5f;

                    mpModel->SetVertex(vertex, XMFLOAT3(cosAngle, sinAngle + center.y, 0.0f), kColorHack[vertex] );

                    mpModel->SetIndex(index, 0);
					++index;

					// If this is the last one, loop back around to index 1 (index 0 is the centre)
					if ( vertex < kSegments ) 
						mpModel->SetIndex(index, vertex+1);
					else
						mpModel->SetIndex(index, 1);
					++index;

                    mpModel->SetIndex(index, vertex);
					++index;
					
                    ++vertex;
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
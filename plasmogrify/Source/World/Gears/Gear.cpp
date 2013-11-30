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
#if 1
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

#if 0
                // Add the center vertex.
                mpModel->SetVertex(vertex, XMFLOAT3(0.0f, center.y, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) );
                ++vertex;
				mpModel->SetVertex(vertex, XMFLOAT3(0.5f, 0.0f + center.y, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
				++vertex;
				mpModel->SetVertex(vertex, XMFLOAT3(0.0f, 0.5f + center.y, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
				++vertex;
				mpModel->SetVertex(vertex, XMFLOAT3(-0.5f, 0.0f + center.y, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
				++vertex;
				mpModel->SetVertex(vertex, XMFLOAT3(0.0f, -0.5f + center.y, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
				++vertex;
#if 1
				mpModel->SetIndex(index, 0);
				++index;
				mpModel->SetIndex(index, 2);
				++index;
				mpModel->SetIndex(index, 1);
				++index;
#endif
				mpModel->SetIndex(index, 0);
				++index;
				mpModel->SetIndex(index, 3);
				++index;
				mpModel->SetIndex(index, 2);
				++index;

				mpModel->SetIndex(index, 0);
				++index;
				mpModel->SetIndex(index, 4);
				++index;
				mpModel->SetIndex(index, 3);
				++index;

				mpModel->SetIndex(index, 0);
				++index;
				mpModel->SetIndex(index, 1);
				++index;
				mpModel->SetIndex(index, 4);
				++index;
#else
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
#if 1
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
#endif
					
                    ++vertex;
                }

#if 0
				mpModel->SetIndex(index, 0);
				++index;
				mpModel->SetIndex(index, 2);
				++index;
				mpModel->SetIndex(index, 1);
				++index;
#endif
#endif

#else

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

                    mpModel->SetVertex(offset + 0, XMFLOAT3(0.0f, 0.5f + center.y, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
                    mpModel->SetVertex(offset + 1, XMFLOAT3(0.45f, 0.0f + center.y, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
                    mpModel->SetVertex(offset + 2, XMFLOAT3(-0.45f, 0.0f + center.y, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));

                    mpModel->SetIndex(offset + 0, offset + 0);
                    mpModel->SetIndex(offset + 1, offset + 1);
                    mpModel->SetIndex(offset + 2, offset + 2);
                }
#endif

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
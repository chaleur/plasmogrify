///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Geometry.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Geometry Definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Geometry.h"
#include "Device.h"
#include "Context.h"
#include <math.h>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            VertexList::VertexList()
                : mpVertexBuffer(NULL)
                , mpVertexShader(NULL)
                , mpPixelShader(NULL)
                , mpVertexList(NULL)
                , mVertexCount(0)
            {
            }

            VertexList::~VertexList()
            {
                if (mpVertexList)
                {
                    delete[] mpVertexList;
                }
            }

            void VertexList::Init(Device* pDevice, eTriangleType type)
            {
                BuildGear(type);

                D3D11_BUFFER_DESC bd;
                ZeroMemory( &bd, sizeof(bd) );
                bd.Usage = D3D11_USAGE_DYNAMIC;
                bd.ByteWidth = sizeof( Vertex ) * 6;
                bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

                D3D11_SUBRESOURCE_DATA srd;
                srd.pSysMem = mpVertexList;

                pDevice->CreateBuffer( &bd, &srd, &mpVertexBuffer );

                mpVertexShader = pDevice->GetVertexShader();
                mpPixelShader = pDevice->GetPixelShader();
            }

            void VertexList::Draw(Context* pContext)
            {
                uint32_t stride = sizeof( Vertex );
                uint32_t offset = 0; // sizeof(Vertex) * 3;

                pContext->SetVertexBuffers( 0, 1, &mpVertexBuffer, &stride, &offset );
                pContext->Draw(mpVertexShader, mpPixelShader, mVertexCount);
            }

            Vertex* VertexList::GetVertexList()
            {
                return mpVertexList;
            }

            size_t VertexList::GetVertexListSize()
            {
                return sizeof(Vertex) * mVertexCount;
            }

            uint32_t VertexList::GetVertexCount()
            {
                return mVertexCount;
            }

            void VertexList::BuildGear(eTriangleType type)
            {
                if (mpVertexList)
                {
                    delete[] mpVertexList;
                    mVertexCount = 0;
                }

                uint32_t segments = 4;

                mVertexCount = segments * 3;
                mpVertexList = new Vertex[mVertexCount];

                XMFLOAT3 center = XMFLOAT3(0.45f, 0.00f, 0.0f);
                
                switch ( type )
                {
                    case kTriangle_Type0:
                    {
                        center = XMFLOAT3(0.00f, 0.10f, 0.0f);
                        break;
                    }
                    case kTriangle_Type1:
                    {
                        center = XMFLOAT3(0.00f, -0.45f, 0.0f);
                        break;
                    }
                }

                for (uint32_t i = 0; i < segments; ++i)
                {
                    uint32_t offset = i * 3;

                    float angle = (float)i / (2.0f * 3.1415926f);

                    mpVertexList[offset + 0].Pos =    XMFLOAT3(0.0f, 0.5f + center.y, 0.0f);
                    mpVertexList[offset + 0].Colour = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

                    mpVertexList[offset + 1].Pos =    XMFLOAT3(0.45f, 0.0f + center.y, 0.0f) ;
                    mpVertexList[offset + 1].Colour = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

                    mpVertexList[offset + 2].Pos =    XMFLOAT3(-0.45f, 0.0f + center.y, 0.0f);
                    mpVertexList[offset + 2].Colour = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
                }

            }

            static float sign0 = 1.0f;
            static float sign1 = 1.0f;
            static float sign2 = 1.0f;

            void VertexList::Update()
            {
                mpVertexList[0].Pos.y += sign0 * 0.01f;
                if ( (mpVertexList[0].Pos.y > 0.8f) || (mpVertexList[0].Pos.y < 0.8f) )
                {
                    sign0 *= -1.0f;
                }
            }
                    
        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
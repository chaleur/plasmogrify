///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Model.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Model Definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Model.h"
#include "Device.h"
#include "Context.h"
#include "Effect.h"
#include <math.h>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            Model::Model()
                : mpVertexBuffer(NULL)
                , mpVertexList(NULL)
                , mVertexCount(0)
                , mpEffect(NULL)
            {
            }

            Model::~Model()
            {
            }

            void Model::Cleanup()
            {
                if (mpVertexBuffer) mpVertexBuffer->Release();
                if (mpVertexList)
                {
                    delete[] mpVertexList;
                    mpVertexList = NULL;
                }
                
                if (mpEffect)
                {
                    mpEffect->Cleanup();
                    delete mpEffect;
                    mpEffect = NULL;
                }
            }

            void Model::InitMaterial(Device* pDevice)
            {
                mpEffect = new Effect();
                mpEffect->Init(pDevice);
            }

            void Model::InitGeometry(Device* pDevice)
            {

                D3D11_BUFFER_DESC bd;
                ZeroMemory( &bd, sizeof(bd) );
                bd.Usage = D3D11_USAGE_DYNAMIC;
                bd.ByteWidth = sizeof( Vertex ) * 6;
                bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

                D3D11_SUBRESOURCE_DATA srd;
                srd.pSysMem = mpVertexList;

                pDevice->CreateBuffer( &bd, &srd, &mpVertexBuffer );
            }

            bool  Model::CreateVertexList(uint32_t vertexCount)
            {
                if (mpVertexList)
                {
                    return false;
                }

                mpVertexList = new Vertex[vertexCount];
                mVertexCount = vertexCount;

                return true;
            }

            void Model::SetVertex(uint32_t index, XMFLOAT3& pos, XMFLOAT4& colour)
            {
                if (index >= mVertexCount)
                {
                    return;
                }

                mpVertexList[index].Pos = pos;
                mpVertexList[index].Colour = colour;

            }

            void Model::Init(Device* pDevice)
            {
                InitMaterial(pDevice);
                InitGeometry(pDevice);
            }

            void Model::Draw(Context* pContext)
            {
                mpEffect->Apply(pContext);

                uint32_t stride = sizeof( Vertex );
                uint32_t offset = 0; // sizeof(Vertex) * 3;
                
                pContext->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
                pContext->SetVertexBuffers( 0, 1, &mpVertexBuffer, &stride, &offset );
                pContext->Draw(mVertexCount);
            }

            Vertex* Model::GetVertexList()
            {
                return mpVertexList;
            }

            size_t Model::GetVertexListSize()
            {
                return sizeof(Vertex)* mVertexCount;
            }

            uint32_t Model::GetVertexCount()
            {
                return mVertexCount;
            }

            static float sign0 = 1.0f;
            static float sign1 = 1.0f;
            static float sign2 = 1.0f;

            void Model::Update()
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
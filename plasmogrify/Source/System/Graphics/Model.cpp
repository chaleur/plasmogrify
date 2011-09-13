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
                : mbInit(false)
                , mpVertexBuffer(NULL)
                , mpVertexList(NULL)
                , mVertexCount(0)
                , mpIndexBuffer(NULL)
                , mpIndexList(NULL)
                , mIndexCount(0)
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
                    mVertexCount = 0;
                }

                if (mpIndexBuffer) mpIndexBuffer->Release();
                if (mpVertexList)
                {
                    delete[] mpVertexList;
                    mpVertexList = NULL;
                    mIndexCount = 0;
                }
                
                if (mpEffect)
                {
                    mpEffect->Cleanup();
                    delete mpEffect;
                    mpEffect = NULL;
                }
            }

            bool Model::CreateVertexList(uint32_t vertexCount)
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

            bool Model::CreateIndexList(uint32_t indexCount)
            {
                if (mpIndexList)
                {
                    return false;
                }

                mpIndexList = new uint32_t[indexCount];
                mIndexCount = indexCount;

                return true;
            }

            void Model::SetIndex(uint32_t index, uint32_t value)
            {
                if (index >= mIndexCount)
                {
                    return;
                }

                mpIndexList[index] = value;
            }

            void Model::CreateVertexBuffer(Device* pDevice)
            {
                D3D11_BUFFER_DESC bd;
                ZeroMemory( &bd, sizeof(bd) );
                bd.Usage = D3D11_USAGE_IMMUTABLE;
                bd.ByteWidth = sizeof( Vertex ) * mVertexCount;
                bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                bd.CPUAccessFlags = 0;
                bd.MiscFlags = 0;

                D3D11_SUBRESOURCE_DATA srd;
                srd.pSysMem = mpVertexList;

                pDevice->CreateBuffer( &bd, &srd, &mpVertexBuffer );
            }

            void Model::CreateIndexBuffer(Device* pDevice)
            {
                D3D11_BUFFER_DESC bd;
                ZeroMemory( &bd, sizeof(bd) );
                bd.Usage = D3D11_USAGE_IMMUTABLE;
                bd.ByteWidth = sizeof( DWORD ) * mIndexCount;
                bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
                bd.CPUAccessFlags = 0;
                bd.MiscFlags = 0;

                D3D11_SUBRESOURCE_DATA srd;
                srd.pSysMem = mpIndexList;

                pDevice->CreateBuffer( &bd, &srd, &mpIndexBuffer );
            }

            void Model::InitGeometry(Device* pDevice)
            {
                CreateVertexBuffer(pDevice);
                CreateIndexBuffer(pDevice);
            }

            void Model::InitMaterial(Device* pDevice)
            {
                mpEffect = new Effect();
                mpEffect->Init(pDevice);
            }

            void Model::Init(Device* pDevice)
            {
                if (mbInit)
                {
                    return;
                }

                InitGeometry(pDevice);
                InitMaterial(pDevice);
            }

            void Model::Draw(Context* pContext)
            {
                mpEffect->Apply(pContext);

                uint32_t stride = sizeof( Vertex );
                uint32_t offset = 0; // sizeof(Vertex) * 3;
                
                pContext->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
                pContext->SetVertexBuffers( 0, 1, &mpVertexBuffer, &stride, &offset );
                pContext->SetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

                //pContext->Draw(mVertexCount);
                pContext->DrawIndexed(mIndexCount, 0, 0);
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
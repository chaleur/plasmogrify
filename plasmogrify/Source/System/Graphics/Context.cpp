///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Context.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Render Context
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Context.h"

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {

            Context::Context()
                : mpContext(NULL)
            {
            }

            Context::~Context()
            {
            }

            void Context::Cleanup()
            {
                ClearState();
            }

            void Context::ClearState()
            {
                if (mpContext)
                {
                    mpContext->ClearState();
                }
            }

            void Context::Release()
            {
                if (mpContext)
                {
                    mpContext->Release();
                }
            }

            void Context::PreDraw(ID3D11RenderTargetView* pRenderTargetView, ID3D11DepthStencilView* pDepthStencilView)
            {
                float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
                mpContext->ClearRenderTargetView( pRenderTargetView, ClearColor );
                mpContext->ClearDepthStencilView( pDepthStencilView, D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL, 1.0f, 0);
            }

            void Context::Draw(uint32_t vertexCount)
            {
                mpContext->Draw( vertexCount, 0 );
            }

            HRESULT Context::SetVertexBuffers(uint32_t startSlot, uint32_t numBuffers, ID3D11Buffer** ppVertexBuffers, uint32_t* stride, uint32_t* offset)
            {
                if (!mpContext)
                {
                    return E_POINTER;
                }

                mpContext->IASetVertexBuffers( startSlot, numBuffers, ppVertexBuffers, stride, offset );

                return S_OK;
            }

            HRESULT Context::SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
            {
                if (!mpContext)
                {
                    return E_POINTER;
                }

                mpContext->IASetPrimitiveTopology( topology );

                return S_OK;
            }

            HRESULT Context::Map(ID3D11Resource* pResource, uint32_t subResource, D3D11_MAP mapType, uint32_t mapFlags, D3D11_MAPPED_SUBRESOURCE* pMappedSubresource)
            {
                if (!mpContext)
                {
                    return E_POINTER;
                }

                return mpContext->Map(pResource, subResource, mapType, mapFlags, pMappedSubresource);
            }

            HRESULT Context::Unmap(ID3D11Resource* pResource, uint32_t subResource)
            {
                if (!mpContext)
                {
                    return E_POINTER;
                }

                mpContext->Unmap(pResource, subResource);

                return S_OK;
            }

            HRESULT Context::SetInputLayout(ID3D11InputLayout* inputLayout)
            {
                if (!mpContext)
                {
                    return E_POINTER;
                }

                mpContext->IASetInputLayout( inputLayout );

                return S_OK;
            }

            HRESULT Context::SetViewports(uint32_t viewportCount, D3D11_VIEWPORT* viewPorts )
            {
                if (!mpContext)
                {
                    return E_POINTER;
                }

                mpContext->RSSetViewports( viewportCount, viewPorts );

                return S_OK;
            }

            HRESULT Context::SetRenderTargets(uint32_t targetCount, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView)
            {
                if (!mpContext)
                {
                    return E_POINTER;
                }

                mpContext->OMSetRenderTargets( targetCount, ppRenderTargetViews, pDepthStencilView );

                return S_OK;
            }

            HRESULT Context::SetVertexShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, uint32_t numClassInstances)
            {
                if (!mpContext)
                {
                    return E_POINTER;
                }

                mpContext->VSSetShader( pVertexShader, ppClassInstances, numClassInstances );

                return S_OK;
            }

            HRESULT Context::SetPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, uint32_t numClassInstances)
            {
                if (!mpContext)
                {
                    return E_POINTER;
                }

                mpContext->PSSetShader( pPixelShader, ppClassInstances, numClassInstances );

                return S_OK;
            }

            ID3D11DeviceContext** Context::GetContextPtr()
            {
                return &mpContext;
            }

                    
        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Context.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Render Context
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_SYSTEM_GRAPHICS_CONTEXT
#define PLASMOGRIFY_SYSTEM_GRAPHICS_CONTEXT

#include "../../Config.h"
#include <d3d11.h>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            class Context
            {
                public:
                    Context();
                    ~Context();

                    void Cleanup();
                    void ClearState();
                    void Release();

                    void PreDraw(ID3D11RenderTargetView* pRenderTargetView, ID3D11DepthStencilView* pDepthStencilView);
                    void DrawIndexed(uint32_t indexCount, uint32_t startIndexLocation, int32_t baseVertexLocation);
                    void Draw(uint32_t vertexCount);

                    HRESULT SetVertexBuffers(uint32_t startSlot, uint32_t numBuffers, ID3D11Buffer** ppVertexBuffers, uint32_t* stride, uint32_t* offset);
                    HRESULT SetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, uint32_t offset);

                    HRESULT SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);

                    HRESULT Map(ID3D11Resource* pResource, uint32_t subResource, D3D11_MAP mapType, uint32_t mapFlags, D3D11_MAPPED_SUBRESOURCE* pMappedSubresource);
                    HRESULT Unmap(ID3D11Resource* pResource, uint32_t subResource);

                    HRESULT SetViewports(uint32_t viewportCount, D3D11_VIEWPORT* viewPorts );
                    HRESULT SetRenderTargets(uint32_t targetCount, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView);

                    HRESULT SetVertexShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, uint32_t numClassInstances);
                    HRESULT SetPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, uint32_t numClassInstances);
                    HRESULT SetInputLayout(ID3D11InputLayout* inputLayout);

                    ID3D11DeviceContext** GetContextPtr();
                
                private:
                    ID3D11DeviceContext*    mpContext;
            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify

#endif // PLASMOGRIFY_SYSTEM_GRAPHICS_CONTEXT
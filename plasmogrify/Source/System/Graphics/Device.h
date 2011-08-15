///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Device.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Device Implementation
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_SYSTEM_GRAPHICS_DEVICE
#define PLASMOGRIFY_SYSTEM_GRAPHICS_DEVICE

#include "../../Config.h"
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            class Context;

            class Device
            {
                public:
                    Device();
                    ~Device();

                    HRESULT Init(HWND hWnd);

                    void CreateBuffer(D3D11_BUFFER_DESC* pDesc, D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer);
                    
                    void PreRender();
                    void Render();
                    void PostRender();

                    void Cleanup();

                    Context* GetRenderContext();
                    ID3D11VertexShader* GetVertexShader();
                    ID3D11PixelShader* GetPixelShader();

                private:

                    HRESULT InitDeviceAndSwapChain(HWND hWnd, uint32_t width, uint32_t height);
                    HRESULT InitRenderTargetView(uint32_t width, uint32_t height);
                    HRESULT InitDepthStencilBuffer(uint32_t width, uint32_t height);
                    HRESULT InitRenderTargets(uint32_t width, uint32_t height);
                    HRESULT InitViewport(uint32_t width, uint32_t height);
                    HRESULT InitPipeline();
                    HRESULT InitGeometry();
                    HRESULT InitFont();

                    HRESULT CompileShader( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut );

                private:

                    ID3D11Device*           mpDevice;
                    Context*                mpContext;

                    IDXGISwapChain*         mpSwapChain;
                    ID3D11RenderTargetView* mpRenderTargetView;
                    ID3D11Texture2D*        mpDepthStencilBuffer;
                    ID3D11DepthStencilView* mpDepthStencilView;
                    ID3D11VertexShader*     mpVertexShader;
                    ID3D11PixelShader*      mpPixelShader;
                    ID3D11InputLayout*      mpVertexLayout;
            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify

#endif // PLASMOGRIFY_SYSTEM_GRAPHICS_DEVICE
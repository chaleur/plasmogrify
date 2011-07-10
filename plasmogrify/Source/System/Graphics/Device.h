///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Device.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Device Implementation
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "../../Config.h"
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>

#include "Geometry.h"

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            class Device
            {
                public:
                    Device();
                    ~Device();

                    void Init(HWND hWnd);
                    void Render();
                    void Cleanup();

                private:

                    void InitDeviceAndSwapChain(HWND hWnd, uint32_t width, uint32_t height);
                    void InitRenderTargetView(uint32_t width, uint32_t height);
                    void InitPipeline();
                    void InitGeometry();

                    HRESULT CompileShader( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut );

                private:

                    ID3D11Device*           mpDevice;
                    ID3D11DeviceContext*    mpContext;
                    IDXGISwapChain*         mpSwapChain;
                    ID3D11RenderTargetView* mpRenderTargetView;
                    ID3D11VertexShader*     mpVertexShader;
                    ID3D11PixelShader*      mpPixelShader;
                    ID3D11InputLayout*      mpVertexLayout;
                    ID3D11Buffer*           mpVertexBuffer;

                    VertexList              mVertexList;

                    
            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
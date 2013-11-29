///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Device.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Device Implementation
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Device.h"
#include "Context.h"
//#include <iostream>
//#include <vector>
#include <d3dcompiler.h>
#include <DxErr.h>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            Device::Device()
                : mpDevice(NULL)
                , mpContext(NULL)
                , mpSwapChain(NULL)
                , mpRenderTargetView(NULL)
                , mpDepthStencilBuffer(NULL)
                , mpDepthStencilView(NULL)
            {
            }

            Device::~Device()
            {

            }

            Context* Device::GetRenderContext()
            {
                return mpContext;
            }

            //ID3D11VertexShader* Device::GetVertexShader()
            //{
            //    return mpVertexShader;
            //}

            //ID3D11PixelShader* Device::GetPixelShader()
            //{
            //    return mpPixelShader;
            //B}

            HRESULT Device::InitDeviceAndSwapChain(HWND hWnd, uint32_t width, uint32_t height)
            {
                HRESULT hr = S_OK;

                DXGI_SWAP_CHAIN_DESC scd;    // create a struct to hold various swap chain information

                ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));    // clear out the struct for use

                scd.BufferCount = 1;  
                scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
                scd.BufferDesc.Width = width;    
                scd.BufferDesc.Height = height; 
                scd.BufferDesc.RefreshRate.Numerator = 60;
                scd.BufferDesc.RefreshRate.Denominator = 1;
                scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
                scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
                scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
                scd.SampleDesc.Count = 1; 
                scd.SampleDesc.Quality = 0;  
                scd.OutputWindow = hWnd; 
                scd.Windowed = TRUE; 
                scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
                //scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

                D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

                hr = D3D11CreateDeviceAndSwapChain( NULL, driverType, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, &scd, &mpSwapChain, &mpDevice, NULL, mpContext->GetContextPtr() );
                HRTRACE(hr, L"Failed to Create Device and Swap Chain.");

                
                HRESULT result;

                IDXGIFactory* pFactory;
                result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));
                HRTRACE(result, L"Failed to Create DXGI Factory.");

                // Count Adapters and check properties.
                //char buffer[5000];
                //uint8_t adapterCount = 0; 
                //IDXGIAdapter* pAdapter; 
                //std::vector <IDXGIAdapter*> vAdapters; 
                //while(pFactory->EnumAdapters(adapterCount, &pAdapter) != DXGI_ERROR_NOT_FOUND) 
                //{ 
	            //    vAdapters.push_back(pAdapter); 
                //    LARGE_INTEGER version10 = {0,0};
                //    LARGE_INTEGER version11 = {0,0};
                //    HRESULT v11 = pAdapter->CheckInterfaceSupport(__uuidof(ID3D11Device), &version11);
                //    HRESULT v10 = pAdapter->CheckInterfaceSupport(__uuidof(ID3D10Device), &version10);
                //
                //    UINT outputCount = 0;
                //    IDXGIOutput* pOutput;
                //    std::vector<IDXGIOutput*> vOutputs;
                //    while(pAdapter->EnumOutputs(outputCount, &pOutput) != DXGI_ERROR_NOT_FOUND)
                //    {
                //        vOutputs.push_back(pOutput);
                //
                //        uint32_t num = 0;
                //        DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
                //        pOutput->GetDisplayModeList( format, 0, &num, 0);
                //
                //        DXGI_MODE_DESC * pDescs = new DXGI_MODE_DESC[num];
                //        pOutput->GetDisplayModeList( format, 0, &num, pDescs);
                //
                //        sprintf(buffer, "Adapter %d: Output %d", adapterCount, outputCount);
                //        char temp[64];
                //        for (uint32_t i = 0; i < num; ++i )
                //        {
                //            sprintf(temp, "Width: %d, Height: %d, Refresh: %d/%d\n", pDescs[i].Width, pDescs[i].Height, pDescs[i].RefreshRate.Numerator, pDescs[i].RefreshRate.Denominator);
                //            strcat(buffer, temp);
                //        }
                //
                //        MessageBox(NULL, buffer, "Output", MB_OK); 
                //
                //        ++outputCount;
                //    }
                //
                //    sprintf(buffer, "Adapter %d: DX10: %s, DX11: %s, Outputs: %d", adapterCount, v10 == S_OK ? "Yes" : "No", v11 == S_OK ? "Yes" : "No", outputCount );
                //    MessageBox(NULL, buffer, "Outputs", MB_OK); 
                //
	            //    ++adapterCount; 
                //} 

                //sprintf(buffer, "Adapter Count is %d\n", adapterCount);
                //MessageBox(NULL, buffer, "Adapters", MB_OK); 

                // TODO: This method fails of creating device and swap chain fails on CreateSwapChain, which returns 'DXGI_ERROR_INVALID_CALL'.  Why?

                //result = D3D11CreateDevice( NULL, driverType, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, &mpDevice, NULL, &mpContext);
                //HRTRACE(result, L"Failed to create D3D11 Device.");

                //result = pFactory->CreateSwapChain(mpDevice, &scd, &mpSwapChain);
                //HRTRACE(result, L"Failed to create swap chain");

                return hr;

            }

            HRESULT Device::InitRenderTargetView(uint32_t width, uint32_t height)
            {
                HRESULT result, hr = S_OK;

                ID3D11Texture2D* pBackBuffer = NULL;

                result = mpSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
                HRTRACE(result, L"Failed to get Back Buffer.");
                hr |= result;

                result = mpDevice->CreateRenderTargetView( pBackBuffer, NULL, &mpRenderTargetView );
                HRTRACE(result, L"Failed to create Render Target View.");
                hr |= result;

                pBackBuffer->Release();

                return hr;

            }

            HRESULT Device::InitDepthStencilBuffer(uint32_t width, uint32_t height)
            {
                HRESULT result, hr = S_OK;

                D3D11_TEXTURE2D_DESC depthStencilDesc;
                depthStencilDesc.Width = width;
                depthStencilDesc.Height = height;
                depthStencilDesc.MipLevels = 1;
                depthStencilDesc.ArraySize = 1;
                depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
                depthStencilDesc.SampleDesc.Count = 1;
                depthStencilDesc.SampleDesc.Quality = 0;
                depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
                depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
                depthStencilDesc.CPUAccessFlags = 0;
                depthStencilDesc.MiscFlags = 0;

                result = mpDevice->CreateTexture2D( &depthStencilDesc, 0, &mpDepthStencilBuffer);
                HRTRACE(result, L"Failed to create depth stencil buffer texture.");
                hr |= result;

                result = mpDevice->CreateDepthStencilView( mpDepthStencilBuffer, 0, &mpDepthStencilView);
                HRTRACE(result, L"Failed to create depth stencil view.");
                hr |= result;

                return hr;

            }

            HRESULT Device::InitRenderTargets(uint32_t width, uint32_t height)
            {
                HRESULT result, hr = S_OK;

                result = InitRenderTargetView(width, height);
                HRTRACE(result, L"Failed to init render target view.");
                hr |= result;

                result = InitDepthStencilBuffer(width, height);
                HRTRACE(result, L"Failed to init depth stencil buffer.");
                hr |= result;

                result = mpContext->SetRenderTargets( 1, &mpRenderTargetView, mpDepthStencilView );
                HRTRACE(result, L"Failed to set render targets.");
                hr |= result;

                return hr;
            }


            HRESULT Device::InitViewport(uint32_t width, uint32_t height)
            {
                HRESULT hr = S_OK;

                D3D11_VIEWPORT viewport;
                ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

                viewport.Width = (FLOAT)width;
                viewport.Height = (FLOAT)height;
                viewport.MinDepth = 0.0f;
                viewport.MaxDepth = 1.0f;
                viewport.TopLeftX = 0;
                viewport.TopLeftY = 0;

                hr = mpContext->SetViewports( 1, &viewport );
                HRTRACE(hr, L"Failed to set viewport.");

                return hr;
            }

            HRESULT Device::InitFont()
            {
                return S_OK;
            }


            HRESULT Device::Init(HWND hWnd)
            {
                HRESULT result, hr = S_OK;
                
                RECT rc;
                GetClientRect( hWnd, &rc );
                UINT width = rc.right - rc.left;
                UINT height = rc.bottom - rc.top;

                mpContext = new Context();

                result = InitDeviceAndSwapChain(hWnd, width, height);
                HRTRACE(result, L"Failed to init Device and Swap Chain.");
                hr |= result;

                //To disable DXGI monitoring message queue.
                //IDXGIFactory* pFactory;
                //HRESULT sresult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));
                //pFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_WINDOW_CHANGES);

                result = InitRenderTargets(width, height);
                HRTRACE(result, L"Failed to init render targets.");
                hr |= result;

                result = InitViewport(width, height);
                HRTRACE(result, L"Failed to init viewport.");
                hr |= result;

                result = InitFont();
                HRTRACE(result, L"Failed to init font.");
                hr |= result;

                //mpDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

                return hr;

            }

            void Device::CreateBuffer(D3D11_BUFFER_DESC* pDesc, D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
            {
                mpDevice->CreateBuffer(pDesc, pInitialData, ppBuffer );
            }

            HRESULT Device::CreateVertexShader(void* pShaderBytecode, size_t bytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
            {
                return mpDevice->CreateVertexShader(pShaderBytecode, bytecodeLength, pClassLinkage, ppVertexShader );
            }

            HRESULT Device::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, uint32_t numElements, void* pShaderBytecodeWithInputSignature, size_t bytecodeLength, ID3D11InputLayout** ppInputLayout)
            {
                return mpDevice->CreateInputLayout(pInputElementDescs, numElements, pShaderBytecodeWithInputSignature, bytecodeLength, ppInputLayout);
            }

            HRESULT Device::CreatePixelShader(const void* pShaderBytecode, size_t byteCodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
            {
                return mpDevice->CreatePixelShader(pShaderBytecode, byteCodeLength, pClassLinkage, ppPixelShader);
            }

            void Device::PreRender()
            {
                mpContext->PreDraw(mpRenderTargetView, mpDepthStencilView);
            }

            void Device::Render()
            {
            }

            void Device::PostRender()
            {
                mpSwapChain->Present( 0, 0 );
            }

            void Device::Cleanup()
            {
                if (mpContext)
                {
                    mpContext->Cleanup();
                    delete mpContext;
                    mpContext = NULL;
                }

                if (mpRenderTargetView) mpRenderTargetView->Release();
                if (mpDepthStencilView) mpDepthStencilView->Release();
                if (mpDepthStencilBuffer) mpDepthStencilBuffer->Release();
                if (mpSwapChain) mpSwapChain->Release();
                if (mpContext) mpContext->Release();
                if (mpDevice) mpDevice->Release();
            }

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
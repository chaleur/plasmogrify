///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Device.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Device Implementation
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Device.h"
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
                , mpVertexShader(NULL)
                , mpPixelShader(NULL)
                , mpVertexLayout(NULL)
                , mpVertexBuffer(NULL)
            {

            }

            Device::~Device()
            {

            }

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
                scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

                D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

                hr = D3D11CreateDeviceAndSwapChain( NULL, driverType, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, &scd, &mpSwapChain, &mpDevice, NULL, &mpContext );
                HRTRACE(hr, L"Failed to Create Device and Swap Chain.");

                // TODO: This method fails.  Why?

                //HRESULT result;
                //result = D3D11CreateDevice( NULL, driverType, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, &mpDevice, NULL, &mpContext);
                //HRTRACE(result, L"Failed to create D3D11 Device.");

                //IDXGIFactory* pFactory;
                //result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));
                //HRTRACE(result, L"Failed to Create DXGI Factory.");
                
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

                mpContext->OMSetRenderTargets( 1, &mpRenderTargetView, mpDepthStencilView );

                return hr;
            }


            HRESULT Device::InitViewport(uint32_t width, uint32_t height)
            {
                D3D11_VIEWPORT viewport;
                ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

                viewport.Width = (FLOAT)width;
                viewport.Height = (FLOAT)height;
                viewport.MinDepth = 0.0f;
                viewport.MaxDepth = 1.0f;
                viewport.TopLeftX = 0;
                viewport.TopLeftY = 0;

                mpContext->RSSetViewports( 1, &viewport );

                return S_OK;
            }

            HRESULT CompileShaderFromFile( char* szFileName, char* szEntryPoint, char* szShaderModel, ID3DBlob** ppBlobOut )
            {
                HRESULT hr = S_OK;

                DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

                ID3DBlob* pErrorBlob;
                hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
                char* szErrorString = pErrorBlob ? (char*)pErrorBlob->GetBufferPointer() : "Error Compiling Shader from File.";
                HROUTPUT(hr, szErrorString);
                HRTRACE(hr, L"Error compiling shader from file.");

                if (pErrorBlob)
                {
                    pErrorBlob->Release();
                }

                return hr;
            }

            HRESULT Device::InitPipeline()
            {
                HRESULT result, hr = S_OK;

                ID3DBlob* pVSBlob = NULL;
                result = CompileShaderFromFile( "Shaders/generic.fx", "VS", "vs_4_0", &pVSBlob );
                HRTRACE(result, L"Failed to compile vertex shader.");
                hr |= result;

                result = mpDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &mpVertexShader ), L"Failed to create vertex shader.";
                HRTRACE(result, L"Failed to compile vertex shader.");
                hr |= result;

                D3D11_INPUT_ELEMENT_DESC layout[] =
                {
                    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
                };
                UINT numElements = ARRAYSIZE( layout );

                result = mpDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &mpVertexLayout );
                HRTRACE(result, L"Failed to create input layout.");
                hr |= result;

                if (pVSBlob) pVSBlob->Release();

                mpContext->IASetInputLayout( mpVertexLayout );

                ID3DBlob* pPSBlob = NULL;
                result = CompileShaderFromFile( "Shaders/generic.fx", "PS", "ps_4_0", &pPSBlob );
                HRTRACE(result, L"Failed to compile pixel shader.");
                hr |= result;

                result = mpDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &mpPixelShader );
                HRTRACE(result, L"Failed to create pixel shader.");
                hr |= result;

                if (pPSBlob) pPSBlob->Release();

                return hr;

            }

            HRESULT Device::InitGeometry()
            {
                HRESULT hr = S_OK;

                Vertex verts[] =
                {
                    {XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
                    {XMFLOAT3(0.45f, 0.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
                    {XMFLOAT3(-0.45f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
                    {XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
                    {XMFLOAT3(0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
                    {XMFLOAT3(-0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}
                };

                D3D11_BUFFER_DESC bd;
                ZeroMemory( &bd, sizeof(bd) );
                bd.Usage = D3D11_USAGE_DYNAMIC;
                bd.ByteWidth = sizeof( Vertex ) * 6;
                bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

                mpDevice->CreateBuffer( &bd, NULL, &mpVertexBuffer );
                D3D11_MAPPED_SUBRESOURCE ms;
                hr = mpContext->Map(mpVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
                HRTRACE(hr, L"Failed to map vertex buffer."); 
                memcpy(ms.pData, mVertexList.GetVertexList(), mVertexList.GetVertexListSize()); 
                mpContext->Unmap(mpVertexBuffer, NULL);

                UINT stride = sizeof( Vertex );
                UINT offset = 0; // sizeof(Vertex) * 3;
                mpContext->IASetVertexBuffers( 0, 1, &mpVertexBuffer, &stride, &offset );

                mpContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

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

                result = InitDeviceAndSwapChain(hWnd, width, height);
                HRTRACE(result, L"Failed to init Device and Swap Chain.");
                hr |= result;

                InitRenderTargets(width, height);
                HRTRACE(result, L"Failed to init render targets.");
                hr |= result;

                InitViewport(width, height);
                HRTRACE(result, L"Failed to init viewport.");
                hr |= result;

                InitPipeline();
                HRTRACE(result, L"Failed to init pipeline.");
                hr |= result;

                InitGeometry();
                HRTRACE(result, L"Failed to init geometry.");
                hr |= result;

                InitFont();
                HRTRACE(result, L"Failed to init font.");
                hr |= result;

                //mpDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

                return hr;

            }

            void Device::Render()
            {
                float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
                mpContext->ClearRenderTargetView( mpRenderTargetView, ClearColor );
                mpContext->ClearDepthStencilView( mpDepthStencilView, D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL, 1.0f, 0);

                mpContext->VSSetShader( mpVertexShader, NULL, 0 );
                mpContext->PSSetShader( mpPixelShader, NULL, 0 );
                mpContext->Draw( mVertexList.GetVertexCount(), 0 );

                mpSwapChain->Present( 0, 0 );
            }

            void Device::Cleanup()
            {
                if (mpContext) mpContext->ClearState();

                if (mpVertexBuffer) mpVertexBuffer->Release();
                if (mpVertexLayout) mpVertexLayout->Release();
                if (mpPixelShader) mpPixelShader->Release();
                if (mpVertexShader) mpVertexShader->Release();
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
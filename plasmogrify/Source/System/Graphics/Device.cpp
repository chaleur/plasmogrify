///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Application.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Application
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Device.h"
#include <d3dcompiler.h>

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
                , mpVertexShader(NULL)
                , mpPixelShader(NULL)
                , mpVertexLayout(NULL)
                , mpVertexBuffer(NULL)
            {

            }

            Device::~Device()
            {

            }

            void Device::InitDeviceAndSwapChain(HWND hWnd, uint32_t width, uint32_t height)
            {
                DXGI_SWAP_CHAIN_DESC scd;    // create a struct to hold various swap chain information

                ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));    // clear out the struct for use

                scd.BufferCount = 1;  
                scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
                scd.BufferDesc.Width = width;    
                scd.BufferDesc.Height = height; 
                scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  
                scd.OutputWindow = hWnd; 
                scd.SampleDesc.Count = 1; 
                scd.SampleDesc.Quality = 0;  
                scd.Windowed = TRUE; 
                scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

                D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

                D3D11CreateDeviceAndSwapChain( NULL, driverType, NULL, NULL, NULL, NULL,
                    D3D11_SDK_VERSION, &scd, &mpSwapChain, &mpDevice, NULL, &mpContext );
            }

            void Device::InitRenderTargetView(uint32_t width, uint32_t height)
            {
                ID3D11Texture2D* pBackBuffer = NULL;
                mpSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );

                mpDevice->CreateRenderTargetView( pBackBuffer, NULL, &mpRenderTargetView );
                pBackBuffer->Release();

                D3D11_VIEWPORT viewport;
                ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

                viewport.Width = (FLOAT)width;
                viewport.Height = (FLOAT)height;
                viewport.MinDepth = 0.0f;
                viewport.MaxDepth = 1.0f;
                viewport.TopLeftX = 0;
                viewport.TopLeftY = 0;

                mpContext->RSSetViewports( 1, &viewport );

                mpContext->OMSetRenderTargets( 1, &mpRenderTargetView, NULL );
            }

            HRESULT CompileShaderFromFile( char* szFileName, char* szEntryPoint, char* szShaderModel, ID3DBlob** ppBlobOut )
            {
                HRESULT result = S_OK;
                DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

                ID3DBlob* pErrorBlob;
                result = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
                    dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
                if( FAILED(result) )
                {
                    if( pErrorBlob != NULL )
                        OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
                    if( pErrorBlob ) pErrorBlob->Release();
                    return result;
                }
                if( pErrorBlob ) pErrorBlob->Release();

                return S_OK;
            }

            void Device::InitPipeline()
            {
                ID3DBlob* pVSBlob = NULL;
                HRESULT result = CompileShaderFromFile( "Shaders/generic.fx", "VS", "vs_4_0", &pVSBlob );
                if( FAILED( result ) )
                {
                    MessageBox( NULL,  "Plasmogrify: Vertex Shader Error.\n", "Error", MB_OK );
                    return;
                }

                mpDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &mpVertexShader );

                D3D11_INPUT_ELEMENT_DESC layout[] =
                {
                    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
                };
                UINT numElements = ARRAYSIZE( layout );

                mpDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &mpVertexLayout );
                
                pVSBlob->Release();

                mpContext->IASetInputLayout( mpVertexLayout );

                ID3DBlob* pPSBlob = NULL;
                result = CompileShaderFromFile( "Shaders/generic.fx", "PS", "ps_4_0", &pPSBlob );
                if( FAILED( result ) )
                {
                    MessageBox( NULL,  "Plasmogrify: Pixel Shader Error.\n", "Error", MB_OK );
                    return;
                }

                mpDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &mpPixelShader );
                pPSBlob->Release();

            }

            void Device::InitGeometry()
            {
                Vertex verts[] =
                {
                    {XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
                    {XMFLOAT3(0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
                    {XMFLOAT3(-0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}
                };

                D3D11_BUFFER_DESC bd;
                ZeroMemory( &bd, sizeof(bd) );
                bd.Usage = D3D11_USAGE_DYNAMIC;
                bd.ByteWidth = sizeof( Vertex ) * 3;
                bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

                mpDevice->CreateBuffer( &bd, NULL, &mpVertexBuffer );

                D3D11_MAPPED_SUBRESOURCE ms;
                mpContext->Map(mpVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); 
                memcpy(ms.pData, verts, sizeof(verts));
                mpContext->Unmap(mpVertexBuffer, NULL);

                UINT stride = sizeof( Vertex );
                UINT offset = 0;
                mpContext->IASetVertexBuffers( 0, 1, &mpVertexBuffer, &stride, &offset );

                mpContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

            }


            void Device::Init(HWND hWnd)
            {
                RECT rc;
                GetClientRect( hWnd, &rc );
                UINT width = rc.right - rc.left;
                UINT height = rc.bottom - rc.top;

                InitDeviceAndSwapChain(hWnd, width, height);
                InitRenderTargetView(width, height);
                InitPipeline();
                InitGeometry();

            }

            void Device::Render()
            {
                float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
                mpContext->ClearRenderTargetView( mpRenderTargetView, ClearColor );

                mpContext->VSSetShader( mpVertexShader, NULL, 0 );
                mpContext->PSSetShader( mpPixelShader, NULL, 0 );
                mpContext->Draw( 3, 0 );

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
                if (mpSwapChain) mpSwapChain->Release();
                if (mpContext) mpContext->Release();
                if (mpDevice) mpDevice->Release();
            }

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
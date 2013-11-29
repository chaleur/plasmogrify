///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Effect.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Shader Effect
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Effect.h"
#include "Device.h"
#include "Context.h"
#include <d3dcompiler.h>
#include <d3dx11.h>
#include <DxErr.h>


namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            Effect::Effect()
                : mpVertexShader(NULL)
                , mpPixelShader(NULL)
                , mpInputLayout(NULL)
            {
            }

            Effect::~Effect()
            {
            }

            void Effect::Cleanup()
            {
                if (mpVertexShader) mpVertexShader->Release();
                if (mpPixelShader) mpPixelShader->Release();
                if (mpInputLayout) mpInputLayout->Release();
            }

            HRESULT Effect::LoadShader(char* fileName, char* entryPoint, char* shaderModel, ID3DBlob** ppBlobOut)
            {
                DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

                ID3DBlob* pErrorBlob = NULL;
                HRESULT hr = D3DX11CompileFromFile( fileName, NULL, NULL, entryPoint, shaderModel, dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
                char* errorString = pErrorBlob ? (char*)pErrorBlob->GetBufferPointer() : "Error Compiling Shader from File.";
                HROUTPUT(hr, errorString);
                HRTRACE(hr, L"Error compiling shader from file.");

                if (pErrorBlob)
                {
                    pErrorBlob->Release();
                }

                return hr;
            }

            HRESULT Effect::InitVertexShader(Device* pDevice, ID3DBlob** ppVSBlob)
            {
                HRESULT result, hr = S_OK;

                result = LoadShader( "Shaders/generic.fx", "VS", "vs_4_0", ppVSBlob );
                HRTRACE(result, L"Failed to compile vertex shader.");
                hr |= result;

                result = pDevice->CreateVertexShader( (*ppVSBlob)->GetBufferPointer(), (*ppVSBlob)->GetBufferSize(), NULL, &mpVertexShader);
                HRTRACE(result, L"Failed to compile vertex shader.");
                hr |= result;

                return hr;
            }

            HRESULT Effect::InitInputLayout(Device *pDevice, ID3DBlob* pVSBlob)
            {
                D3D11_INPUT_ELEMENT_DESC layout[] =
                {
                    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
                };
                UINT numElements = ARRAYSIZE( layout );

                HRESULT result = pDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &mpInputLayout );
                HRTRACE(result, L"Failed to create input layout.");
                return result;
            }

            HRESULT Effect::InitPixelShader(Device *pDevice, ID3DBlob* pPSBlob)
            {
                HRESULT result, hr = S_OK;
                
                result = LoadShader( "Shaders/generic.fx", "PS", "ps_4_0", &pPSBlob );
                HRTRACE(result, L"Failed to compile pixel shader.");
                hr |= result;

                result = pDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &mpPixelShader );
                HRTRACE(result, L"Failed to create pixel shader.");
                hr |= result;

                return S_OK;
            }

            HRESULT Effect::Init(Device *pDevice)
            {
                // Create vertex shader and input layout
                ID3DBlob* pVSBlob = NULL;
                InitVertexShader(pDevice, &pVSBlob);
                InitInputLayout(pDevice, pVSBlob);
                if (pVSBlob) pVSBlob->Release();

                // Create Pixel Shader
                ID3DBlob* pPSBlob = NULL;
                InitPixelShader(pDevice, pPSBlob);
                if (pPSBlob) pPSBlob->Release();

                return S_OK;
            }

            HRESULT Effect::Apply(Context* pContext) 
            {
                pContext->SetVertexShader( mpVertexShader, NULL, 0 );
                pContext->SetPixelShader( mpPixelShader, NULL, 0 );
                
                HRESULT result = pContext->SetInputLayout( mpInputLayout );
                HRTRACE(result, L"Failed to set input layout.");
                return result;
            }

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
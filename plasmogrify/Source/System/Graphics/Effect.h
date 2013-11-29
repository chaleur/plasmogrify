///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Effect.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Shader Effect
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_SYSTEM_GRAPHICS_EFFECT
#define PLASMOGRIFY_SYSTEM_GRAPHICS_EFFECT

#include "../../Config.h"
#include <d3d11.h>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            class Device;
            class Context;

            class Effect
            {
                public:
                    Effect();
                    ~Effect();

                    void                   Cleanup();

                public:

                    HRESULT                 Init(Device *pDevice);
                    HRESULT                 Apply(Context* pContext);

                private:

                    HRESULT                 LoadShader(char* fileName, char* entryPoint, char* shaderModel, ID3DBlob** ppBlobOut);

                    HRESULT                 InitVertexShader(Device *pDevice, ID3DBlob** ppVSBlob);
                    HRESULT                 InitInputLayout(Device *pDevice, ID3DBlob* pVSBlob);
                    HRESULT                 InitPixelShader(Device *pDevice, ID3DBlob* pPSBlob);

                private:
                    ID3D11VertexShader*     mpVertexShader;
                    ID3D11PixelShader*      mpPixelShader;
                    ID3D11InputLayout*      mpInputLayout;

            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify

#endif // PLASMOGRIFY_SYSTEM_GRAPHICS_EFFECT
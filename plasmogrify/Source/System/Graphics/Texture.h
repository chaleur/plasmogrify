///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Texture.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       A Font Class
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_SYSTEM_GRAPHICS_TEXTURE
#define PLASMOGRIFY_SYSTEM_GRAPHICS_TEXTURE

#include "../../Config.h"
#include <d3d11.h>
#include <xnamath.h>
#include <fstream>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            class Texture
            {
                public:
                    Texture();
                    ~Texture();

                    bool Init(ID3D11Device* pDevice, WCHAR* texFile);
                    void Cleanup();

                    ID3D11ShaderResourceView* GetTextureResourceView();

               private:
                    ID3D11ShaderResourceView*       mpTextureResourceView;

            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify

#endif // PLASMOGRIFY_SYSTEM_GRAPHICS_TEXTURE
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Texture.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       A Texture Class
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Texture.h"

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {

            Texture::Texture()
                : mpTextureResourceView(NULL)
            {
            }

            Texture::~Texture()
            {
            }

            bool Texture::Init(ID3D11Device* pDevice, WCHAR* texFile)
            {
                return true;
            }

            void Texture::Cleanup()
            {
                if (mpTextureResourceView) mpTextureResourceView->Release();
            }

            ID3D11ShaderResourceView* Texture::GetTextureResourceView()
            {
                return mpTextureResourceView;
            }

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
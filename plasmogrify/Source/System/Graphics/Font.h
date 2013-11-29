///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Font.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       A Font Class
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_SYSTEM_GRAPHICS_FONT
#define PLASMOGRIFY_SYSTEM_GRAPHICS_FONT

#include "../../Config.h"
#include <d3d11.h>
#include <xnamath.h>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            class Texture;

            class Font
            {
                private:
                    struct TypeFace
	                {
		                float left;
                        float right;
		                int32_t size;
	                };

                    struct FontVertex
                    {
                        XMFLOAT3 Pos;
                        XMFLOAT2 Texture;
                    };

                public:
                    Font();
                    ~Font();

                    bool Init(ID3D11Device* pDevice, char* fontFile, WCHAR* textureFile);
                    void Cleanup();

                    void BuildFontVertexData(void* vertIndex, char* textBuffer, float x, float y);
                    ID3D11ShaderResourceView* GetTextureResourceView();

                private:

                    bool LoadFont(char* fontFile);
                    void CleanupFont();

                    bool LoadTexture(ID3D11Device* pDevice, WCHAR* texFile);
                    void CleanupTexture();

                private:
                    static const uint32_t               kFontCharacters;
                    static const uint32_t               kFontHeight;
                    static const float                  kSpaceWidth;
                    static const float                  kKernWidth;

                private:
	                TypeFace*                           mpFont;
	                Texture*                            mpTexture;

            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify

#endif // PLASMOGRIFY_SYSTEM_GRAPHICS_FONT
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Font.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       A Font Class
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Font.h"
#include "Texture.h"
#include <fstream>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {

            const uint32_t Font::kFontCharacters = 95;
            const uint32_t Font::kFontHeight = 16;
            const float Font::kSpaceWidth = 3.0f;
            const float Font::kKernWidth = 1.0f;

            Font::Font()
                : mpFont(NULL)
                , mpTexture(NULL)
            {
            }

            Font::~Font()
            {
            }

            bool Font::Init(ID3D11Device* pDevice, char* fontFile, WCHAR* texFile)
            {
	            if (!LoadFont(fontFile))
                {
                    return false;
                }

	            if (!LoadTexture(pDevice, texFile))
	            {
		            return false;
	            }

                return true;
            }

            void Font::Cleanup()
            {
                CleanupTexture();
                CleanupFont();
            }

            void Font::BuildFontVertexData(void* vertexBuffer, char* textBuffer, float x, float y)
            {
                FontVertex* vb = (FontVertex*)vertexBuffer;
                size_t length = strlen(textBuffer);

                uint32_t vertIndex = 0;

	            for(uint32_t i = 0; i < length; ++i)
	            {
		            int32_t ch = ((int32_t)textBuffer[i]) - 32;
		            if(!ch)
		            {
			            x += kSpaceWidth;
		            }
		            else
		            {
			            // TL
			            vb[vertIndex].Pos = XMFLOAT3(x, y, 0.0f);
			            vb[vertIndex].Texture = XMFLOAT2(mpFont[ch].left, 0.0f);
			            ++vertIndex;

                        // BR
			            vb[vertIndex].Pos = XMFLOAT3((x + mpFont[ch].size), (y - kFontHeight), 0.0f);
			            vb[vertIndex].Texture = XMFLOAT2(mpFont[ch].right, 1.0f);
			            ++vertIndex;

                        // BL
			            vb[vertIndex].Pos = XMFLOAT3(x, (y - kFontHeight), 0.0f);
			            vb[vertIndex].Texture = XMFLOAT2(mpFont[ch].left, 1.0f);
			            ++vertIndex;

                        // TL
			            vb[vertIndex].Pos = XMFLOAT3(x, y, 0.0f);
			            vb[vertIndex].Texture = XMFLOAT2(mpFont[ch].left, 0.0f);
			            ++vertIndex;

                        // TR
			            vb[vertIndex].Pos = XMFLOAT3(x + mpFont[ch].size, y, 0.0f);
			            vb[vertIndex].Texture = XMFLOAT2(mpFont[ch].right, 0.0f);
			            ++vertIndex;
                        
                        // BR
			            vb[vertIndex].Pos = XMFLOAT3((x + mpFont[ch].size), (y - kFontHeight), 0.0f);
			            vb[vertIndex].Texture = XMFLOAT2(mpFont[ch].right, 1.0f);
			            ++vertIndex;

			            x += mpFont[ch].size;
                        x += kKernWidth;
		            }
	            }
            }

            ID3D11ShaderResourceView* Font::GetTextureResourceView()
            {
                return mpTexture->GetTextureResourceView();
            }
            
            bool Font::LoadFont(char* fontFile)
            {
                std::ifstream io;

                if (mpFont)
                {
                    delete[] mpFont;
                    mpFont = NULL;
                }

	            mpFont = new TypeFace[kFontCharacters];
	            if(!mpFont)
	            {
		            return false;
	            }

                io.open(fontFile);
	            if(io.fail())
	            {
		            return false;
	            }

                char buffer;
                for(uint32_t i = 0; i < kFontCharacters; ++i)
	            {
		            io.get(buffer);
		            while(buffer != ' ')
		            {
			            io.get(buffer);
		            }
		            io.get(buffer);
		            while(buffer != ' ')
		            {
			            io.get(buffer);
		            }

		            io >> mpFont[i].left;
		            io >> mpFont[i].right;
		            io >> mpFont[i].size;
	            }

	            io.close();

                return true;

            }

            void Font::CleanupFont()
            {
	            if(mpFont)
	            {
		            delete[] mpFont;
		            mpFont = NULL;
	            }
            }

            bool Font::LoadTexture(ID3D11Device* pDevice, WCHAR* texFile)
            {
                mpTexture = new Texture();
                if(!mpTexture)
                {
	                return false;
                }

                if (!(mpTexture->Init(pDevice, texFile)))
                {
	                return false;
                }

                return true;
            }

            void Font::CleanupTexture()
            {
                if(mpTexture)
                {
                    mpTexture->Cleanup();
                    delete mpTexture;
                    mpTexture = NULL;
                }
            }

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
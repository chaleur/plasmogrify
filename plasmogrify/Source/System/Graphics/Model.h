///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Model.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Model Definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_SYSTEM_GRAPHICS_MODEL
#define PLASMOGRIFY_SYSTEM_GRAPHICS_MODEL

#include "../../Config.h"
#include <d3d11.h>
#include <xnamath.h>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
            class Context;
            class Device;

            struct Vertex
            {
                XMFLOAT3 Pos;
                XMFLOAT4 Colour;
            };

            class Model
            {
                public:
                    enum eTriangleType
                    {
                        kTriangle_Type0,
                        kTriangle_Type1
                    };

                public:
                    Model();
                    ~Model();

                    void        Init(Device* pDevice, eTriangleType type);

                    Vertex*     GetVertexList();
                    size_t      GetVertexListSize();
                    uint32_t    GetVertexCount();

                    void Update();
                    void Draw(Context* pContext);

                private:

                    void BuildGear(eTriangleType type);

                private:
                    
                    ID3D11Buffer*           mpVertexBuffer;

                    ID3D11VertexShader*     mpVertexShader;
                    ID3D11PixelShader*      mpPixelShader;

                    Vertex*                 mpVertexList;
                    uint32_t                mVertexCount;
            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify

#endif // PLASMOGRIFY_SYSTEM_GRAPHICS_MODEL
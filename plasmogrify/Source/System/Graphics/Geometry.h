///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Geometry.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Geometry Definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_SYSTEM_GRAPHICS_GEOMETRY
#define PLASMOGRIFY_SYSTEM_GRAPHICS_GEOMETRY

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

            class VertexList
            {
                public:
                    enum eTriangleType
                    {
                        kTriangle_Type0,
                        kTriangle_Type1
                    };

                public:
                    VertexList();
                    ~VertexList();

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

#endif // PLASMOGRIFY_SYSTEM_GRAPHICS_GEOMETRY
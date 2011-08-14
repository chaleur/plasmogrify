///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Geometry.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Geometry Definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "../../Config.h"
#include <d3d11.h>
#include <xnamath.h>

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {
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

                    void        Init(eTriangleType type);

                    Vertex*     GetVertexList();
                    size_t      GetVertexListSize();
                    uint32_t    GetVertexCount();

                    void Update();

                private:

                    void BuildGear(eTriangleType type);

                private:
                    
                    Vertex*     mpVertexList;
                    uint32_t    mVertexCount;
            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
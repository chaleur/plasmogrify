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
                    VertexList();
                    ~VertexList();

                    Vertex*     GetVertexList();
                    size_t      GetVertexListSize();

                    uint32_t    GetVertexCount();

                    void Update();

                    void BuildGear();

                private:
                    
                    Vertex*     mpVertexList;
                    uint32_t    mVertexCount;
            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
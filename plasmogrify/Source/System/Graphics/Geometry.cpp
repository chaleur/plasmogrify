///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Geometry.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Geometry Definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Geometry.h"

namespace Plasmogrify
{
    namespace System
    {
        namespace Graphics
        {

            VertexList::VertexList()
                : mpVertexList(NULL)
            {
                mpVertexList = new Vertex[3];
                
                mpVertexList[0].Pos = XMFLOAT3(0.0f, 0.5f, 0.0f);
                mpVertexList[0].Colour = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

                mpVertexList[1].Pos = XMFLOAT3(0.45f, -0.5f, 0.0f);
                mpVertexList[1].Colour = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

                mpVertexList[2].Pos = XMFLOAT3(-0.45f, -0.5f, 0.0f);
                mpVertexList[2].Colour = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

            }

            VertexList::~VertexList()
            {
                if (mpVertexList)
                {
                    delete[] mpVertexList;
                }
            }

            Vertex* VertexList::GetVertexList()
            {
                return mpVertexList;
            }

            size_t VertexList::GetVertexListSize()
            {
                size_t test = sizeof(Vertex) * 3;
                return sizeof(Vertex) * 3;
            }
                    
        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify
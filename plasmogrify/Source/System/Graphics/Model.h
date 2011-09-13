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
            class Effect;

            struct Vertex
            {
                XMFLOAT3 Pos;
                XMFLOAT4 Colour;
            };

            class Model
            {
                public:
                    Model();
                    ~Model();

                    void        Cleanup();

                    void        Init(Device* pDevice);
                    
                    bool        CreateVertexList(uint32_t vertexCount);
                    void        SetVertex(uint32_t index, XMFLOAT3& pos, XMFLOAT4& colour);

                    bool        CreateIndexList(uint32_t indexCount);
                    void        SetIndex(uint32_t index, uint32_t value);

                    Vertex*     GetVertexList();
                    size_t      GetVertexListSize();
                    uint32_t    GetVertexCount();

                    void        Update();
                    void        Draw(Context* pContext);

                private:

                    void        CreateVertexBuffer(Device* pDevice);
                    void        CreateIndexBuffer(Device* pDevice);

                    void        InitMaterial(Device* pDevice);
                    void        InitGeometry(Device* pDevice);

                private:
                    
                    bool                    mbInit;

                    ID3D11Buffer*           mpVertexBuffer;
                    Vertex*                 mpVertexList;
                    uint32_t                mVertexCount;
                    
                    ID3D11Buffer*           mpIndexBuffer;
                    uint32_t*               mpIndexList;
                    uint32_t                mIndexCount;

                    Effect*                 mpEffect;        // KAYE TODO: Extract a layer above model to hold an effect!
            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify

#endif // PLASMOGRIFY_SYSTEM_GRAPHICS_MODEL
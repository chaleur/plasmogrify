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
                    enum eTriangleType
                    {
                        kTriangle_Type0,
                        kTriangle_Type1
                    };

                public:
                    Model();
                    ~Model();

                    void        Cleanup();

                    void        Init(Device* pDevice, eTriangleType type);

                    Vertex*     GetVertexList();
                    size_t      GetVertexListSize();
                    uint32_t    GetVertexCount();

                    void Update();
                    void Draw(Context* pContext);

                private:
                    
                    void InitMaterial(Device* pDevice);
                    void InitGeometry(Device* pDevice);

                    void BuildPlaceholderVertexList(eTriangleType type);

                private:
                    
                    ID3D11Buffer*           mpVertexBuffer;

                    Vertex*                 mpVertexList;
                    uint32_t                mVertexCount;

                    Effect*                 mpEffect;        // KAYE TODO: Extract a layer above model to hold an effect!
            };

        } // namespace Graphics
    } // namespace System
} // namespace Plasmogrify

#endif // PLASMOGRIFY_SYSTEM_GRAPHICS_MODEL
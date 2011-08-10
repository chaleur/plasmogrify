///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Gear.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Gear for Gears Sample
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "../../System/Graphics/Geometry.h"

namespace Plasmogrify
{
    namespace World
    {
        namespace Gears
        {
            class Gear
            {
                public:
                    Gear();
                    ~Gear();

                public:
                    void Init();
                    void Update(float dt);
                    void Draw();

                private:
                    bool                              mbInit;
                    System::Graphics::VertexList*     mpVertexList;
            };

        } // namespace Gears
    } // namespace World
} // namespace Plasmogrify
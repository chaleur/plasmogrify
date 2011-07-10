///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        WorldData.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma WorldData
//
//////////////////////////////////////////////////////////////////////////////////////////////////

namespace Plasmogrify
{
    namespace World
    {
        namespace Gears
        {
            class GearBox;
        }

        class WorldData
        {
            public:
                WorldData();
                ~WorldData();

                void Init(void);
                void Update(void);

            private:
                bool                   mbInit;
                Gears::GearBox*        mpGearBox;
                
        };

    } // namespace World
} // namespace Plasmogrify
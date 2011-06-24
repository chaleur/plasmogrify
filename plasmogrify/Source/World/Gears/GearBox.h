///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        GearBox.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Gearbox for Gears Sample
//
//////////////////////////////////////////////////////////////////////////////////////////////////

namespace Plasmogrify
{
    namespace World
    {
        namespace Gears
        {
            class Gear;

            class GearBox
            {
                public:
                    GearBox();
                    ~GearBox();

                    void Init();

                private:
                    bool                mbInit;

                    // \\\ TODO: Make this a set of gears.
                    Gear*               mpGear; 
            };

        } // namespace Gears
    } // namespace World
} // namespace Plasmogrify
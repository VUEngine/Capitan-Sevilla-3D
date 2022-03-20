//---------------------------------------------------------------------------------------------------------
//
//  Level1Stage3Plank
//  • 120×8 pixels
//  • 10 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 15×1 map, not compressed
//  Size: 164 + 30 = 194
//
//---------------------------------------------------------------------------------------------------------

const uint32 Level1Stage3PlankTiles[41] __attribute__((aligned(4))) =
{
    0x00000000,0x55540000,0xAAA4FFE4,0xAAA45954,0x00005554,0x55550000,0xAAAAFFFF,0xAAAA5555,
    0x00005555,0x55550000,0xAAAAFFFF,0xAAAA9555,0x00005555,0x55550000,0xAAAAFFFF,0xAAAA5669,
    0x00005555,0x55550000,0xAAAAFFFF,0xAAAA55A9,0x00005555,0x55550000,0xAAAAFFFF,0xAAA65555,
    0x00005555,0x55550000,0xAAAAFFFF,0x6AAA5555,0x00005555,0x55550000,0xAAAAFFFF,0xAAAA9565,
    0x00005555,0x55550000,0x9AAAFFFF,0xAAAA55AA,0x00005555,0x55550000,0xAAAAFFFF,0xAAAA555A,
    0x00005555,
};

const uint16 Level1Stage3PlankMap[15] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0001,0x0001,0x0002,0x0003,0x0001,0x0001,
    0x0004,0x0005,0x0006,0x0007,0x0008,0x0009,0x2000,
};

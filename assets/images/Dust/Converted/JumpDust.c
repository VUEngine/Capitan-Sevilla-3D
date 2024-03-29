//---------------------------------------------------------------------------------------------------------
//
//  JumpDust
//  • 16×64 pixels
//  • 16 tiles, unreduced, not compressed
//  • 2×8 map, not compressed
//  Size: 260 + 32 = 292
//
//---------------------------------------------------------------------------------------------------------

const uint32 JumpDustTiles[65] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x00000000,0xC0000000,0xFC00F000,0x00000000,0x00000000,0x00030000,
    0x003F000F,0xFF00FC00,0xFFC0FF00,0xFFF0FFC0,0xFFF0FFF0,0x00FF003F,0x03FF00FF,0x0FFF03FF,
    0x0FFF0FFF,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0xF000C000,0xFC00FC00,0xFF00FF00,0xFFC0FFC0,0x000F0003,0x003F003F,0x00FF00FF,
    0x03FF03FF,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0xF000C000,0xFF00FC00,0x00000000,0x00000000,0x000F0003,
    0x00FF003F,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,
};

const uint16 JumpDustMap[16] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
    0x0008,0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x000F,
};

//======================================================================
//
//	Pill, 16x16@2, 
//	+ 4 tiles not compressed
//	+ regular map (flat), not compressed, 2x2 
//	Total size: 64 + 8 = 72
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const uint32 PillTiles[16] __attribute__((aligned(4)))=
{
	0x00000000,0xC0000000,0x7C007000,0x65C0D700,
	0x3D5C0FF0,0x36A936A7,0x36AB36AE,0x03AB0EAA,0x565C5970,0x55575597,0x3D5FD557,0x000003FC,
	0x003500ED,0x0003000D,0x00000000,0x00000000,
};

const uint16 PillMap[4] __attribute__((aligned(4)))=
{
	0x0000,0x0001,0x0002,0x0003,
};
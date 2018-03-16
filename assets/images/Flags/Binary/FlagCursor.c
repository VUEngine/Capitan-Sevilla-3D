
//{{BLOCK(FlagCursor)

//======================================================================
//
//	FlagCursor, 40x32@2, 
//	+ 4 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 5x4 
//	Total size: 64 + 40 = 104
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned int FlagCursorTiles[16] __attribute__((aligned(4)))=
{
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0003FFFF,0x00030003,0x00030003,
	0x00000000,0x0000FFFF,0x00000000,0x00000000,0x00030003,0x00030003,0x00030003,0x00030003,
};

const unsigned short FlagCursorMap[20] __attribute__((aligned(4)))=
{
	0x0001,0x0002,0x0002,0x0002,0x2001,0x0003,0x0000,0x0000,
	0x0000,0x2003,0x0003,0x0000,0x0000,0x0000,0x2003,0x1001,
	0x3002,0x3002,0x3002,0x3001,
};

//}}BLOCK(FlagCursor)

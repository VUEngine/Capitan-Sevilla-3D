
//{{BLOCK(Bench1)

//======================================================================
//
//	Bench1, 64x32@2, 
//	+ 25 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 8x4 
//	Total size: 400 + 64 = 464
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned int Bench1Tiles[100] __attribute__((aligned(4)))=
{
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0200A800,0x42005200,0x48004200,
	0x00000000,0x0000AAAA,0x55555555,0x00005555,0x00000000,0x0000AAAA,0x65959665,0x00009656,
	0x00000000,0x080002AA,0x08660819,0x08000899,0x08000800,0x20002000,0x20002000,0x20002000,
	0x55554000,0x55545554,0x00000000,0x55505554,0x55550000,0x55555555,0x00010000,0x55555555,
	0x95550000,0x95955955,0x00000000,0x55555555,0x20950809,0x21992166,0x80902000,0x19960665,
	0x00000000,0x00000000,0x00020000,0x00020002,0x80002000,0x80008000,0x00008000,0x00000000,
	0x00005550,0x91000040,0x91026400,0x14084002,0x00005555,0x55990010,0x00015556,0x00145551,
	0x00006555,0x55550000,0x50000155,0x00000555,0x00002659,0x55550100,0x55550000,0x02000000,

	0xAAAA0002,0x55550000,0x55550000,0x00000000,0xAAAA0000,0x55550000,0x0855A000,0x02000000,
	0x02AA0000,0x00290080,0x00000001,0x00000000,0x00084008,0x20088008,0x02080808,0x00000088,
	0x00000001,0x080002AA,0x80002000,0x00008000,0x00200080,0x00200020,0x00200020,0x00000020,
	0x02000200,0x02000200,0x82008200,0x00002200,0x80282A80,0x00020002,0x00000000,0x00000000,
	0x02000100,0x02020102,0x02080102,0x00000208,
};

const unsigned short Bench1Map[32] __attribute__((aligned(4)))=
{
	0x0001,0x0002,0x0002,0x0003,0x0004,0x0000,0x0000,0x0000,
	0x0005,0x0006,0x0007,0x0008,0x0009,0x000A,0x0000,0x0000,
	0x000B,0x000C,0x000D,0x000E,0x000F,0x0010,0x0011,0x0012,
	0x0000,0x0013,0x0014,0x0015,0x0016,0x0017,0x0018,0x0000,
};

//}}BLOCK(Bench1)

#include "ffcc/gxfunc.h"

struct GXTevColorInReg {
	_GXTevColorArg a;
	_GXTevColorArg b;
	_GXTevColorArg c;
	_GXTevColorArg d;
};

struct GXTevAlphaInReg {
	_GXTevAlphaArg a;
	_GXTevAlphaArg b;
	_GXTevAlphaArg c;
	_GXTevAlphaArg d;
};

struct GXTevColorOpReg {
	_GXTevOp op;
	_GXTevBias bias;
	_GXTevScale scale;
	unsigned char clamp;
	_GXTevRegID outReg;
};

struct GXTevAlphaOpReg {
	_GXTevOp op;
	_GXTevBias bias;
	_GXTevScale scale;
	unsigned char clamp;
	_GXTevRegID outReg;
};

struct GXTevOrderReg {
	_GXTexCoordID coord;
	_GXTexMapID map;
	_GXChannelID channel;
};

struct GXTevSwapModeReg {
	_GXTevSwapSel rasSel;
	_GXTevSwapSel texSel;
};

struct GXTevSwapModeTableReg {
	_GXTevColorChan red;
	_GXTevColorChan green;
	_GXTevColorChan blue;
	_GXTevColorChan alpha;
};

struct GXAlphaCompareReg {
	_GXCompare comp0;
	_GXAlphaOp alphaOp;
	_GXCompare comp1;
	unsigned short ref0;
	unsigned short ref1;
};

struct GXBlendModeReg {
	_GXBlendMode mode;
	_GXBlendFactor srcFactor;
	_GXBlendFactor dstFactor;
	_GXLogicOp logicOp;
};

static GXTevColorInReg s_GXSetTevColorIn_Reg[16];
static GXTevAlphaInReg s_GXSetTevAlphaIn_Reg[16];
static GXTevColorOpReg s_GXSetTevColorOp_Reg[16];
static GXTevAlphaOpReg s_GXSetTevAlphaOp_Reg[16];
static GXTevSwapModeReg s_GXSetTevSwapMode_Reg[16];
static GXTevOrderReg s_GXSetTevOrder_Reg[16];
static GXTevSwapModeTableReg s_GXSetTevSwapModeTable_Reg[4];
static GXAlphaCompareReg s_GXSetAlphaCompare_Reg;
static unsigned short s_GXSetPixel_Init_Reg;
static GXBlendModeReg s_GXSetBlendMode_Reg;

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTev0_Init(_GXTevStageID)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTev_Init()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010357c
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevOp(_GXTevStageID stage, _GXTevMode mode)
{
	s_GXSetTevColorIn_Reg[stage].a = (_GXTevColorArg)-1;
	s_GXSetTevAlphaIn_Reg[stage].a = (_GXTevAlphaArg)-1;
	s_GXSetTevColorOp_Reg[stage].op = (_GXTevOp)-1;
	s_GXSetTevAlphaOp_Reg[stage].op = (_GXTevOp)-1;
	s_GXSetTevSwapMode_Reg[stage].rasSel = (_GXTevSwapSel)-1;
	GXSetTevOp(stage, mode);
}

/*
 * --INFO--
 * PAL Address: 0x8010350c
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevColorIn(_GXTevStageID stage, _GXTevColorArg a, _GXTevColorArg b, _GXTevColorArg c, _GXTevColorArg d)
{
	if (s_GXSetTevColorIn_Reg[stage].a != a || s_GXSetTevColorIn_Reg[stage].b != b || s_GXSetTevColorIn_Reg[stage].c != c ||
	    s_GXSetTevColorIn_Reg[stage].d != d) {
		s_GXSetTevColorIn_Reg[stage].a = a;
		s_GXSetTevColorIn_Reg[stage].b = b;
		s_GXSetTevColorIn_Reg[stage].c = c;
		s_GXSetTevColorIn_Reg[stage].d = d;
		GXSetTevColorIn(stage, a, b, c, d);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8010349c
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevAlphaIn(_GXTevStageID stage, _GXTevAlphaArg a, _GXTevAlphaArg b, _GXTevAlphaArg c, _GXTevAlphaArg d)
{
	if (s_GXSetTevAlphaIn_Reg[stage].a != a || s_GXSetTevAlphaIn_Reg[stage].b != b || s_GXSetTevAlphaIn_Reg[stage].c != c ||
	    s_GXSetTevAlphaIn_Reg[stage].d != d) {
		s_GXSetTevAlphaIn_Reg[stage].a = a;
		s_GXSetTevAlphaIn_Reg[stage].b = b;
		s_GXSetTevAlphaIn_Reg[stage].c = c;
		s_GXSetTevAlphaIn_Reg[stage].d = d;
		GXSetTevAlphaIn(stage, a, b, c, d);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80103418
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevColorOp(_GXTevStageID stage, _GXTevOp op, _GXTevBias bias, _GXTevScale scale, unsigned char clamp, _GXTevRegID outReg)
{
	if (s_GXSetTevColorOp_Reg[stage].op != op || s_GXSetTevColorOp_Reg[stage].bias != bias || s_GXSetTevColorOp_Reg[stage].scale != scale ||
	    s_GXSetTevColorOp_Reg[stage].clamp != clamp || s_GXSetTevColorOp_Reg[stage].outReg != outReg) {
		s_GXSetTevColorOp_Reg[stage].op = op;
		s_GXSetTevColorOp_Reg[stage].bias = bias;
		s_GXSetTevColorOp_Reg[stage].scale = scale;
		s_GXSetTevColorOp_Reg[stage].clamp = clamp;
		s_GXSetTevColorOp_Reg[stage].outReg = outReg;
		GXSetTevColorOp(stage, op, bias, scale, clamp, outReg);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80103394
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevAlphaOp(_GXTevStageID stage, _GXTevOp op, _GXTevBias bias, _GXTevScale scale, unsigned char clamp, _GXTevRegID outReg)
{
	if (s_GXSetTevAlphaOp_Reg[stage].op != op || s_GXSetTevAlphaOp_Reg[stage].bias != bias || s_GXSetTevAlphaOp_Reg[stage].scale != scale ||
	    s_GXSetTevAlphaOp_Reg[stage].clamp != clamp || s_GXSetTevAlphaOp_Reg[stage].outReg != outReg) {
		s_GXSetTevAlphaOp_Reg[stage].op = op;
		s_GXSetTevAlphaOp_Reg[stage].bias = bias;
		s_GXSetTevAlphaOp_Reg[stage].scale = scale;
		s_GXSetTevAlphaOp_Reg[stage].clamp = clamp;
		s_GXSetTevAlphaOp_Reg[stage].outReg = outReg;
		GXSetTevAlphaOp(stage, op, bias, scale, clamp, outReg);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80103308
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetAlphaCompare(_GXCompare comp0, unsigned char ref0, _GXAlphaOp op, _GXCompare comp1, unsigned char ref1)
{
	if (s_GXSetAlphaCompare_Reg.comp0 != comp0 || s_GXSetAlphaCompare_Reg.alphaOp != op || s_GXSetAlphaCompare_Reg.comp1 != comp1 ||
	    s_GXSetAlphaCompare_Reg.ref0 != ref0 || s_GXSetAlphaCompare_Reg.ref1 != ref1) {
		s_GXSetAlphaCompare_Reg.ref0 = ref0;
		s_GXSetAlphaCompare_Reg.ref1 = ref1;
		s_GXSetAlphaCompare_Reg.comp0 = comp0;
		s_GXSetAlphaCompare_Reg.alphaOp = op;
		s_GXSetAlphaCompare_Reg.comp1 = comp1;
		GXSetAlphaCompare(comp0, ref0, op, comp1, ref1);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801032a8
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevOrder(_GXTevStageID stage, _GXTexCoordID coord, _GXTexMapID map, _GXChannelID channel)
{
	int stageOff = stage * 0xC;
	int* entry = (int*)((char*)s_GXSetTevOrder_Reg + stageOff);

	if (entry[0] != coord || entry[1] != map || entry[2] != channel) {
		entry[0] = coord;
		entry[1] = map;
		entry[2] = channel;
		GXSetTevOrder(stage, coord, map, channel);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80103258
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevSwapMode(_GXTevStageID stage, _GXTevSwapSel rasSel, _GXTevSwapSel texSel)
{
	int stageOff = stage * 8;
	int* entry = (int*)((char*)s_GXSetTevSwapMode_Reg + stageOff);

	if (entry[0] != rasSel || entry[1] != texSel) {
		entry[0] = rasSel;
		entry[1] = texSel;
		GXSetTevSwapMode(stage, rasSel, texSel);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801031e8
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevSwapModeTable(_GXTevSwapSel table, _GXTevColorChan red, _GXTevColorChan green, _GXTevColorChan blue, _GXTevColorChan alpha)
{
	int tableOff = table * 0x10;
	int* entry = (int*)((char*)s_GXSetTevSwapModeTable_Reg + tableOff);
	if (entry[0] != red || entry[1] != green || entry[2] != blue || entry[3] != alpha) {
		entry[0] = red;
		entry[1] = green;
		entry[2] = blue;
		entry[3] = alpha;
		GXSetTevSwapModeTable(table, red, green, blue, alpha);
	}
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetPixel_Init()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80103180
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetBlendMode(_GXBlendMode mode, _GXBlendFactor srcFactor, _GXBlendFactor dstFactor, _GXLogicOp logicOp)
{
	if (s_GXSetBlendMode_Reg.mode != mode || s_GXSetBlendMode_Reg.srcFactor != srcFactor || s_GXSetBlendMode_Reg.dstFactor != dstFactor ||
	    s_GXSetBlendMode_Reg.logicOp != logicOp) {
		s_GXSetBlendMode_Reg.mode = mode;
		s_GXSetBlendMode_Reg.srcFactor = srcFactor;
		s_GXSetBlendMode_Reg.dstFactor = dstFactor;
		s_GXSetBlendMode_Reg.logicOp = logicOp;
		GXSetBlendMode(mode, srcFactor, dstFactor, logicOp);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80102fb4
 * PAL Size: 460b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _InitGxFunc()
{
	int i = 0;
	int tevInOff = 0;
	int tevOpOff = 0;
	int tevSwapOff = 0;
	char* tevOrder = (char*)s_GXSetTevOrder_Reg;
	int count = 2;

	do {
		int i1 = i + 1;
		int i2 = i + 2;
		int i3 = i + 3;
		int i4 = i + 4;
		int i5 = i + 5;
		int i6 = i + 6;
		int i7 = i + 7;

		*(int*)((char*)s_GXSetTevColorOp_Reg + tevOpOff) = -1;
		*(int*)((char*)s_GXSetTevAlphaOp_Reg + tevOpOff) = -1;
		*(int*)((char*)s_GXSetTevSwapMode_Reg + tevSwapOff) = -1;
		*(int*)((char*)s_GXSetTevColorIn_Reg + tevInOff) = -1;
		*(int*)((char*)s_GXSetTevAlphaIn_Reg + tevInOff) = -1;
		*(int*)(tevOrder) = -1;

		*(int*)((char*)s_GXSetTevSwapMode_Reg + i1 * 8) = -1;
		*(int*)((char*)s_GXSetTevColorIn_Reg + i1 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevAlphaIn_Reg + i1 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevColorOp_Reg + i1 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevAlphaOp_Reg + i1 * 0x14) = -1;
		*(int*)(tevOrder + 0xc) = -1;

		*(int*)((char*)s_GXSetTevColorIn_Reg + i2 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevAlphaIn_Reg + i2 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevColorOp_Reg + i2 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevAlphaOp_Reg + i2 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevSwapMode_Reg + i2 * 8) = -1;
		*(int*)(tevOrder + 0x18) = -1;

		*(int*)((char*)s_GXSetTevColorIn_Reg + i3 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevAlphaIn_Reg + i3 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevColorOp_Reg + i3 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevAlphaOp_Reg + i3 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevSwapMode_Reg + i3 * 8) = -1;
		*(int*)(tevOrder + 0x24) = -1;

		*(int*)((char*)s_GXSetTevColorIn_Reg + i4 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevAlphaIn_Reg + i4 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevColorOp_Reg + i4 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevAlphaOp_Reg + i4 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevSwapMode_Reg + i4 * 8) = -1;
		*(int*)(tevOrder + 0x30) = -1;

		*(int*)((char*)s_GXSetTevColorIn_Reg + i5 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevAlphaIn_Reg + i5 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevColorOp_Reg + i5 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevAlphaOp_Reg + i5 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevSwapMode_Reg + i5 * 8) = -1;
		*(int*)(tevOrder + 0x3c) = -1;

		*(int*)((char*)s_GXSetTevColorIn_Reg + i6 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevAlphaIn_Reg + i6 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevColorOp_Reg + i6 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevAlphaOp_Reg + i6 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevSwapMode_Reg + i6 * 8) = -1;
		*(int*)(tevOrder + 0x48) = -1;

		*(int*)(tevOrder + 0x54) = -1;
		*(int*)((char*)s_GXSetTevColorIn_Reg + i7 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevAlphaIn_Reg + i7 * 0x10) = -1;
		*(int*)((char*)s_GXSetTevColorOp_Reg + i7 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevAlphaOp_Reg + i7 * 0x14) = -1;
		*(int*)((char*)s_GXSetTevSwapMode_Reg + i7 * 8) = -1;

		i += 8;
		tevSwapOff += 0x40;
		tevOpOff += 0xA0;
		tevInOff += 0x80;
		tevOrder += 0x60;
		count--;
	} while (count != 0);

	s_GXSetTevSwapModeTable_Reg[0].red = (_GXTevColorChan)-1;
	s_GXSetTevSwapModeTable_Reg[1].red = (_GXTevColorChan)-1;
	s_GXSetTevSwapModeTable_Reg[2].red = (_GXTevColorChan)-1;
	s_GXSetTevSwapModeTable_Reg[3].red = (_GXTevColorChan)-1;
	s_GXSetAlphaCompare_Reg.comp0 = (_GXCompare)-1;
	s_GXSetPixel_Init_Reg = 0xFFFF;
	s_GXSetBlendMode_Reg.mode = (_GXBlendMode)-1;
}

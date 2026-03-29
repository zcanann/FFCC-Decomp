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

GXTevColorInReg s_GXSetTevColorIn_Reg[16];
GXTevAlphaInReg s_GXSetTevAlphaIn_Reg[16];
GXTevColorOpReg s_GXSetTevColorOp_Reg[16];
GXTevAlphaOpReg s_GXSetTevAlphaOp_Reg[16];
GXTevOrderReg s_GXSetTevOrder_Reg[16];
GXTevSwapModeReg s_GXSetTevSwapMode_Reg[16];
GXTevSwapModeTableReg s_GXSetTevSwapModeTable_Reg[4];
GXAlphaCompareReg s_GXSetAlphaCompare_Reg;
unsigned short s_GXSetPixel_Init_Reg;
GXBlendModeReg s_GXSetBlendMode_Reg;

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
	int count = 2;
	int value = -1;
	unsigned char* base = (unsigned char*)s_GXSetTevColorIn_Reg;
	unsigned char* tevColorIn = base;
	unsigned char* tevAlphaIn = base + 0x100;
	unsigned char* tevColorOp = base + 0x200;
	unsigned char* tevAlphaOp = base + 0x340;
	unsigned char* tevOrder = base + 0x480;
	unsigned char* tevSwap = base + 0x540;

	do {
		int i1 = i + 1;
		int i2 = i + 2;
		int i3 = i + 3;
		int i4 = i + 4;
		int i5 = i + 5;
		int i6 = i + 6;
		int i7 = i + 7;

		*(int*)tevColorOp = value;
		*(int*)tevAlphaOp = value;
		*(int*)tevSwap = value;
		*(int*)tevColorIn = value;
		*(int*)tevAlphaIn = value;
		*(int*)tevOrder = value;

		*(int*)(tevSwap + i1 * 8) = value;
		*(int*)(tevColorIn + i1 * 0x10) = value;
		*(int*)(tevAlphaIn + i1 * 0x10) = value;
		*(int*)(tevColorOp + i1 * 0x14) = value;
		*(int*)(tevAlphaOp + i1 * 0x14) = value;
		*(int*)(tevOrder + 0xC) = value;

		*(int*)(tevColorIn + i2 * 0x10) = value;
		*(int*)(tevAlphaIn + i2 * 0x10) = value;
		*(int*)(tevColorOp + i2 * 0x14) = value;
		*(int*)(tevAlphaOp + i2 * 0x14) = value;
		*(int*)(tevSwap + i2 * 8) = value;
		*(int*)(tevOrder + 0x18) = value;

		*(int*)(tevColorIn + i3 * 0x10) = value;
		*(int*)(tevAlphaIn + i3 * 0x10) = value;
		*(int*)(tevColorOp + i3 * 0x14) = value;
		*(int*)(tevAlphaOp + i3 * 0x14) = value;
		*(int*)(tevSwap + i3 * 8) = value;
		*(int*)(tevOrder + 0x24) = value;

		*(int*)(tevColorIn + i4 * 0x10) = value;
		*(int*)(tevAlphaIn + i4 * 0x10) = value;
		*(int*)(tevColorOp + i4 * 0x14) = value;
		*(int*)(tevAlphaOp + i4 * 0x14) = value;
		*(int*)(tevSwap + i4 * 8) = value;
		*(int*)(tevOrder + 0x30) = value;

		*(int*)(tevColorIn + i5 * 0x10) = value;
		*(int*)(tevAlphaIn + i5 * 0x10) = value;
		*(int*)(tevColorOp + i5 * 0x14) = value;
		*(int*)(tevAlphaOp + i5 * 0x14) = value;
		*(int*)(tevSwap + i5 * 8) = value;
		*(int*)(tevOrder + 0x3C) = value;

		*(int*)(tevColorIn + i6 * 0x10) = value;
		*(int*)(tevAlphaIn + i6 * 0x10) = value;
		*(int*)(tevColorOp + i6 * 0x14) = value;
		*(int*)(tevAlphaOp + i6 * 0x14) = value;
		*(int*)(tevSwap + i6 * 8) = value;
		*(int*)(tevOrder + 0x48) = value;

		*(int*)(tevOrder + 0x54) = value;
		*(int*)(tevColorIn + i7 * 0x10) = value;
		*(int*)(tevAlphaIn + i7 * 0x10) = value;
		*(int*)(tevColorOp + i7 * 0x14) = value;
		*(int*)(tevAlphaOp + i7 * 0x14) = value;
		*(int*)(tevSwap + i7 * 8) = value;

		i += 8;
		tevSwap += 0x40;
		tevColorOp += 0xA0;
		tevAlphaOp += 0xA0;
		tevColorIn += 0x80;
		tevAlphaIn += 0x80;
		tevOrder += 0x60;
		count--;
	} while (count != 0);

	*(int*)&s_GXSetTevSwapModeTable_Reg[0] = value;
	*(int*)&s_GXSetTevSwapModeTable_Reg[1] = value;
	*(int*)&s_GXSetTevSwapModeTable_Reg[2] = value;
	*(int*)&s_GXSetTevSwapModeTable_Reg[3] = value;
	*(int*)&s_GXSetAlphaCompare_Reg = value;
	s_GXSetPixel_Init_Reg = 0xFFFF;
	*(int*)&s_GXSetBlendMode_Reg = value;
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
	int stageOff = stage * 0x10;
	int* entry = (int*)((char*)s_GXSetTevColorIn_Reg + stageOff);

	if (entry[0] != a || entry[1] != b || entry[2] != c || entry[3] != d) {
		entry[0] = a;
		entry[1] = b;
		entry[2] = c;
		entry[3] = d;
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
	int stageOff = stage * 0x10;
	int* entry = (int*)((char*)s_GXSetTevAlphaIn_Reg + stageOff);

	if (entry[0] != a || entry[1] != b || entry[2] != c || entry[3] != d) {
		entry[0] = a;
		entry[1] = b;
		entry[2] = c;
		entry[3] = d;
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
	GXTevColorOpReg* entry = &s_GXSetTevColorOp_Reg[stage];

	if (entry->op != op || entry->bias != bias || entry->scale != scale || entry->clamp != clamp || entry->outReg != outReg) {
		entry->op = op;
		entry->bias = bias;
		entry->scale = scale;
		entry->clamp = clamp;
		entry->outReg = outReg;
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
	GXTevAlphaOpReg* entry = &s_GXSetTevAlphaOp_Reg[stage];

	if (entry->op != op || entry->bias != bias || entry->scale != scale || entry->clamp != clamp || entry->outReg != outReg) {
		entry->op = op;
		entry->bias = bias;
		entry->scale = scale;
		entry->clamp = clamp;
		entry->outReg = outReg;
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
		s_GXSetAlphaCompare_Reg.comp0 = comp0;
		s_GXSetAlphaCompare_Reg.alphaOp = op;
		s_GXSetAlphaCompare_Reg.comp1 = comp1;
		s_GXSetAlphaCompare_Reg.ref0 = ref0;
		s_GXSetAlphaCompare_Reg.ref1 = ref1;
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

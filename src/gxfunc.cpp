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
	int* base = (int*)s_GXSetTevColorIn_Reg;
	int* colorIn = base;
	int* alphaIn = base + 0x40;
	int* colorOp = base + 0x80;
	int* alphaOp = base + 0xD0;
	int* tevOrder = base + 0x120;
	int* swapMode = base + 0x150;

	for (int count = 2; count != 0; count--) {
		int i1 = i + 1;
		int i2 = i + 2;
		int i4 = i + 4;
		int value = -1;
		int i3 = i + 3;
		int i5 = i + 5;
		int i6 = i + 6;
		int i7 = i + 7;

		colorOp[0] = value;
		alphaOp[0] = value;
		swapMode[0] = value;
		colorIn[0] = value;
		alphaIn[0] = value;
		tevOrder[0] = value;

		swapMode[i1 * 2] = value;
		colorIn[i1 * 4] = value;
		alphaIn[i1 * 4] = value;
		colorOp[i1 * 5] = value;
		alphaOp[i1 * 5] = value;

		i += 8;
		tevOrder[3] = value;

		colorIn[i2 * 4] = value;
		alphaIn[i2 * 4] = value;
		colorOp[i2 * 5] = value;
		alphaOp[i2 * 5] = value;
		swapMode[i2 * 2] = value;
		tevOrder[6] = value;
		colorIn[i3 * 4] = value;
		alphaIn[i3 * 4] = value;
		colorOp[i3 * 5] = value;
		alphaOp[i3 * 5] = value;
		swapMode[i3 * 2] = value;
		tevOrder[9] = value;
		colorIn[i4 * 4] = value;
		alphaIn[i4 * 4] = value;
		colorOp[i4 * 5] = value;
		alphaOp[i4 * 5] = value;
		swapMode[i4 * 2] = value;
		tevOrder[12] = value;
		colorIn[i5 * 4] = value;
		alphaIn[i5 * 4] = value;
		colorOp[i5 * 5] = value;
		alphaOp[i5 * 5] = value;
		swapMode[i5 * 2] = value;
		tevOrder[15] = value;
		colorIn[i6 * 4] = value;
		alphaIn[i6 * 4] = value;
		colorOp[i6 * 5] = value;
		alphaOp[i6 * 5] = value;
		swapMode[i6 * 2] = value;
		tevOrder[18] = value;
		tevOrder[21] = value;
		colorIn[i7 * 4] = value;
		alphaIn[i7 * 4] = value;
		colorOp[i7 * 5] = value;
		alphaOp[i7 * 5] = value;
		swapMode[i7 * 2] = value;

		colorIn += 0x20;
		alphaIn += 0x20;
		colorOp += 0x28;
		alphaOp += 0x28;
		tevOrder += 0x18;
		swapMode += 0x10;
	}

	*(int*)&s_GXSetTevSwapModeTable_Reg[0] = -1;
	*(int*)&s_GXSetTevSwapModeTable_Reg[1] = -1;
	*(int*)&s_GXSetTevSwapModeTable_Reg[2] = -1;
	*(int*)&s_GXSetTevSwapModeTable_Reg[3] = -1;
	*(int*)&s_GXSetAlphaCompare_Reg = -1;
	s_GXSetPixel_Init_Reg = 0xFFFF;
	*(int*)&s_GXSetBlendMode_Reg = -1;
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

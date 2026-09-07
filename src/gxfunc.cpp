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
GXBlendModeReg s_GXSetBlendMode_Reg;
unsigned short s_GXSetNumTevStages_nStages;

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 68b
 * EN Address: 0x8011FB3C
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void _GXSetTev0_Init(_GXTevStageID stage)
{
	s_GXSetTevColorIn_Reg[stage].a = static_cast<_GXTevColorArg>(-1);
	s_GXSetTevAlphaIn_Reg[stage].a = static_cast<_GXTevAlphaArg>(-1);
	s_GXSetTevColorOp_Reg[stage].op = static_cast<_GXTevOp>(-1);
	s_GXSetTevAlphaOp_Reg[stage].op = static_cast<_GXTevOp>(-1);
	s_GXSetTevSwapMode_Reg[stage].rasSel = static_cast<_GXTevSwapSel>(-1);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 456b
 * EN Address: 0x8011FBB8
 * EN Size: 176b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void _GXSetTev_Init()
{
	for (int i = 0; i < 16; i++) {
		_GXSetTev0_Init(static_cast<_GXTevStageID>(i));
		s_GXSetTevOrder_Reg[i].coord = static_cast<_GXTexCoordID>(-1);
	}
	for (int i = 0; i < 4; i++) {
		s_GXSetTevSwapModeTable_Reg[i].red = static_cast<_GXTevColorChan>(-1);
	}
	s_GXSetAlphaCompare_Reg.comp0 = static_cast<_GXCompare>(-1);
	s_GXSetNumTevStages_nStages = 0xFFFF;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 16b
 * EN Address: 0x801203C8
 * EN Size: 20b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void _GXSetPixel_Init()
{
	s_GXSetBlendMode_Reg.mode = static_cast<_GXBlendMode>(-1);
}

/*
 * --INFO--
 * PAL Address: 0x80102FB4
 * PAL Size: 460b
 * EN Address: 0x801204BC
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
void _InitGxFunc()
{
	_GXSetTev_Init();
	_GXSetPixel_Init();
}

/*
 * --INFO--
 * PAL Address: 0x80103180
 * PAL Size: 104b
 * EN Address: 0x801203DC
 * EN Size: 224b
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
 * EN Address: 0x801202E8
 * EN Size: 224b
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevSwapModeTable(_GXTevSwapSel table, _GXTevColorChan red, _GXTevColorChan green, _GXTevColorChan blue, _GXTevColorChan alpha)
{
	GXTevSwapModeTableReg* entry = &s_GXSetTevSwapModeTable_Reg[table];
	if (entry->red != red || entry->green != green || entry->blue != blue || entry->alpha != alpha) {
		entry->red = red;
		entry->green = green;
		entry->blue = blue;
		entry->alpha = alpha;
		GXSetTevSwapModeTable(table, red, green, blue, alpha);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80103258
 * PAL Size: 80b
 * EN Address: 0x80120238
 * EN Size: 176b
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevSwapMode(_GXTevStageID stage, _GXTevSwapSel rasSel, _GXTevSwapSel texSel)
{
	GXTevSwapModeReg* entry = &s_GXSetTevSwapMode_Reg[stage];

	if (entry->rasSel != rasSel || entry->texSel != texSel) {
		entry->rasSel = rasSel;
		entry->texSel = texSel;
		GXSetTevSwapMode(stage, rasSel, texSel);
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void _GXSetNumTevStages(unsigned char nStages)
{
	if (s_GXSetNumTevStages_nStages != nStages) {
		s_GXSetNumTevStages_nStages = nStages;
		GXSetNumTevStages(nStages);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801032a8
 * PAL Size: 96b
 * EN Address: 0x80120170
 * EN Size: 200b
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevOrder(_GXTevStageID stage, _GXTexCoordID coord, _GXTexMapID map, _GXChannelID channel)
{
	GXTevOrderReg* entry = &s_GXSetTevOrder_Reg[stage];

	if (entry->coord != coord || entry->map != map || entry->channel != channel) {
		entry->coord = coord;
		entry->map = map;
		entry->channel = channel;
		GXSetTevOrder(stage, coord, map, channel);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80103308
 * PAL Size: 140b
 * EN Address: 0x80120068
 * EN Size: 264b
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
 * EN Address: 0x8011FF68
 * EN Size: 256b
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
 * EN Address: 0x8011FE68
 * EN Size: 256b
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
 * EN Address: 0x8011FD88
 * EN Size: 224b
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevAlphaIn(_GXTevStageID stage, _GXTevAlphaArg a, _GXTevAlphaArg b, _GXTevAlphaArg c, _GXTevAlphaArg d)
{
	GXTevAlphaInReg* entry = &s_GXSetTevAlphaIn_Reg[stage];

	if (entry->a != a || entry->b != b || entry->c != c || entry->d != d) {
		entry->a = a;
		entry->b = b;
		entry->c = c;
		entry->d = d;
		GXSetTevAlphaIn(stage, a, b, c, d);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8010350c
 * PAL Size: 112b
 * EN Address: 0x8011FCA8
 * EN Size: 224b
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevColorIn(_GXTevStageID stage, _GXTevColorArg a, _GXTevColorArg b, _GXTevColorArg c, _GXTevColorArg d)
{
	GXTevColorInReg* entry = &s_GXSetTevColorIn_Reg[stage];

	if (entry->a != a || entry->b != b || entry->c != c || entry->d != d) {
		entry->a = a;
		entry->b = b;
		entry->c = c;
		entry->d = d;
		GXSetTevColorIn(stage, a, b, c, d);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8010357c
 * PAL Size: 96b
 * EN Address: 0x8011FC68
 * EN Size: 64b
 * JP Address: TODO
 * JP Size: TODO
 */
void _GXSetTevOp(_GXTevStageID stage, _GXTevMode mode)
{
	_GXSetTev0_Init(stage);
	GXSetTevOp(stage, mode);
}

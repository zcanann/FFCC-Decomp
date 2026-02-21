#include "ffcc/wind.h"

#include <string.h>
#include <math.h>
#include "ffcc/graphic.h"
#include "ffcc/color.h"
#include "ffcc/vector.h"
#include "ffcc/gxfunc.h"
#include "ffcc/math.h"
#include "ffcc/goout.h"
#include "ffcc/p_game.h"
#include "ffcc/system.h"

extern CGraphic Graphic;
extern struct {
    char _0[4];
    Mtx m_cameraMatrix;
} CameraPcs;
extern unsigned char CFlat[];
extern CMath Math;

extern "C" int Rand__5CMathFUl(CMath*, unsigned long);
extern "C" float RandF__5CMathFv(CMath*);

extern float FLOAT_80330ef0;
extern float FLOAT_80330ef4;
extern float FLOAT_80330ef8;
extern float FLOAT_80330f20;
extern float FLOAT_80330f24;
extern float FLOAT_80330f28;
extern float FLOAT_80330f2c;
extern float FLOAT_80330f30;
extern float FLOAT_80330f34;
extern float FLOAT_80330f38;
extern float FLOAT_80330f18;
extern float FLOAT_80330f1c;
extern double DOUBLE_80330f00;
extern double DOUBLE_80330f08;
extern double DOUBLE_80330f10;
extern double DOUBLE_80330f40;
extern double DAT_8032ec20;
extern char DAT_801db528[];
extern char DAT_801db548[];
extern char DAT_801db568[];

/*
 * --INFO--
 * Address:	800da05c
 * Size:	88
 */
void CWind::ClearAll()
{
	memset(this, 0, 0xc80);
	*(u32*)((char*)this + 0xc80) = 1;
	memset((char*)this + 0xc84, 0, 0x7000);
	*(u32*)((char*)this + 0x7c84) = 10000000;
}

/*
 * --INFO--
 * PAL Address: 0x800d9d60
 * PAL Size: 764b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CWind::Frame()
{
    u8* obj;
    int i;
    int rnd;
    float f0;
    float f1;
    float f2;
    double d0;

    obj = (u8*)this;
    i = 0;

    while (true) {
        if ((obj[0] & 0x80) != 0) {
            rnd = Rand__5CMathFUl(&Math, 10);
            if (rnd == 0) {
                rnd = Rand__5CMathFUl(&Math, 3);
                f1 = FLOAT_80330ef0;
                f0 = FLOAT_80330f24;
                if (rnd == 0) {
                    f0 = FLOAT_80330f20;
                }

                *(float*)(obj + 0x54) = *(float*)(obj + 0x4C) * f0 + *(float*)(obj + 0x54);
                f0 = *(float*)(obj + 0x54);
                if ((f1 <= f0) && ((f1 = f0), (*(float*)(obj + 0x4C) < f0))) {
                    f1 = *(float*)(obj + 0x4C);
                }
                *(float*)(obj + 0x54) = f1;
            }

            if ((((*(int*)(obj + 0x1C) == 0) || (*(int*)(obj + 0x1C) == 1)) &&
                 ((rnd = Rand__5CMathFUl(&Math, 0x1E)), rnd == 0)) &&
                (*(float*)(obj + 0x50) < FLOAT_80330f28 * *(float*)(obj + 0x4C))) {
                rnd = Rand__5CMathFUl(&Math, 3);
                f0 = FLOAT_80330f30;
                if (rnd == 0) {
                    f0 = FLOAT_80330f2c;
                }

                *(float*)(obj + 0x48) = *(float*)(obj + 0x40) * f0 + *(float*)(obj + 0x48);
                f0 = *(float*)(obj + 0x48);
                f1 = *(float*)(obj + 0x40);
                if ((f1 <= f0) && ((f2 = FLOAT_80330f34 + f1), (f1 = f0), (f2 < f0))) {
                    f1 = f2;
                }
                *(float*)(obj + 0x48) = f1;
            }

            if (*(int*)(obj + 0x1C) == 2) {
                *(int*)(obj + 0x28) = *(int*)(obj + 0x28) + 1;
                if (*(u32*)(obj + 0x24) <= *(u32*)(obj + 0x28)) {
                    obj[0] = obj[0] & 0x7F;
                    goto next;
                }

                *(float*)(obj + 0x38) = (float)(((double)*(int*)(obj + 0x28) - DOUBLE_80330f40) /
                                                ((double)*(int*)(obj + 0x24) - DOUBLE_80330f40));
                *(float*)(obj + 0x30) = *(float*)(obj + 0x2C) * *(float*)(obj + 0x38);
                *(float*)(obj + 0x34) = *(float*)(obj + 0x30) * *(float*)(obj + 0x30);
                *(float*)(obj + 0x0C) = *(float*)(obj + 4) - *(float*)(obj + 0x30);
                *(float*)(obj + 0x10) = *(float*)(obj + 8) - *(float*)(obj + 0x30);
                *(float*)(obj + 0x14) = *(float*)(obj + 4) + *(float*)(obj + 0x30);
                *(float*)(obj + 0x18) = *(float*)(obj + 8) + *(float*)(obj + 0x30);
            }

            *(float*)(obj + 0x50) = FLOAT_80330f38 * (*(float*)(obj + 0x54) - *(float*)(obj + 0x50)) +
                                    *(float*)(obj + 0x50);
            d0 = (double)RandF__5CMathFv(&Math);
            *(float*)(obj + 0x44) = *(float*)(obj + 0x44) +
                                    (float)((double)FLOAT_80330f2c * d0 +
                                            (double)(FLOAT_80330f38 *
                                                         (*(float*)(obj + 0x48) - *(float*)(obj + 0x44)) -
                                                     FLOAT_80330f28));

            if ((*(int*)(obj + 0x1C) == 0) || (*(int*)(obj + 0x1C) == 1)) {
                d0 = (double)sin((double)*(float*)(obj + 0x44));
                *(float*)(obj + 0x58) = *(float*)(obj + 0x50) * (float)d0;
                d0 = (double)RandF__5CMathFv(&Math);
                *(float*)(obj + 0x5C) =
                    *(float*)(obj + 0x50) * (float)((double)FLOAT_80330f20 * d0 + (double)FLOAT_80330f24);
                d0 = (double)cos((double)*(float*)(obj + 0x44));
                *(float*)(obj + 0x60) = *(float*)(obj + 0x50) * (float)d0;
            }
        }

    next:
        i = i + 1;
        obj = obj + 100;
        if (0x1F < i) {
            return;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d9b2c
 * PAL Size: 564b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CWind::Draw()
{
    u8* obj = (u8*)this;
    Mtx viewMtx;

    PSMTXCopy(CameraPcs.m_cameraMatrix, viewMtx);
    _GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)5, (_GXLogicOp)1);
    GXSetZCompLoc(0);
    _GXSetAlphaCompare((_GXCompare)6, 1, (_GXAlphaOp)0, (_GXCompare)7, 0);
    GXSetZMode(1, (_GXCompare)3, 1);
    GXSetCullMode((_GXCullMode)1);
    GXSetNumTevStages(1);
    _GXSetTevOp((_GXTevStageID)0, (_GXTevMode)4);
    _GXSetTevOrder((_GXTevStageID)0, (_GXTexCoordID)0xff, (_GXTexMapID)0xff, (_GXChannelID)4);
    GXSetNumChans(1);
    GXSetChanCtrl((_GXChannelID)0, 0, (_GXColorSrc)0, (_GXColorSrc)0, 0, (_GXDiffuseFn)2, (_GXAttnFn)1);
    GXSetChanCtrl((_GXChannelID)2, 0, (_GXColorSrc)0, (_GXColorSrc)0, 0, (_GXDiffuseFn)2, (_GXAttnFn)2);
    GXClearVtxDesc();
    GXSetVtxDesc((_GXAttr)9, (_GXAttrType)1);
    GXSetVtxAttrFmt((_GXVtxFmt)0, (_GXAttr)9, (_GXCompCnt)1, (_GXCompType)4, 0);

    if ((*(u32*)(CFlat + 0x129c) & 0x800000) != 0) {
        for (int i = 0; i < 32; i++, obj += 100) {
            if ((s8)obj[0] >= 0) {
                continue;
            }

            if (*(s32*)(obj + 0x1C) == 1) {
                CColor color(0xff, 0xff, 0, 0xff);
                CVector pos(*(float*)(obj + 4), FLOAT_80330ef0, *(float*)(obj + 8));
                Graphic.DrawSphere(viewMtx, (Vec*)&pos, *(float*)(obj + 0x30), &color.color);
            } else {
                int alpha = (int)(FLOAT_80330f1c * (FLOAT_80330ef8 - *(float*)(obj + 0x38)));
                CColor color(0xff, 0xff, 0x80, alpha);
                CVector pos(*(float*)(obj + 4), FLOAT_80330ef0, *(float*)(obj + 8));
                Graphic.DrawSphere(viewMtx, (Vec*)&pos, *(float*)(obj + 0x30), &color.color);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d9840
 * PAL Size: 748b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CWind::Calc(Vec* out, const Vec* pos, int randomize)
{
    u8* obj = (u8*)this;
    Vec tmp;
    double d;
    double inv;
    double nx;
    double nz;
    double yRand;

    out->x = FLOAT_80330ef0;
    out->y = FLOAT_80330ef0;
    out->z = FLOAT_80330ef0;

    if ((*(s32*)((u8*)&MenuPcs + 0x740) == 2) || (Game.game.m_gameWork.m_gamePaused != 0)) {
        return;
    }

    for (int i = 0; i < 32; i++, obj += 100) {
        if ((s8)obj[0] >= 0) {
            continue;
        }

        if (*(s32*)(obj + 0x1C) == 0) {
            if (randomize == 0) {
                PSVECAdd(out, (Vec*)(obj + 0x58), out);
            } else {
                PSVECScale((Vec*)(obj + 0x58), &tmp, (float)RandF__5CMathFv(&Math));
                PSVECAdd(out, &tmp, out);
            }
            continue;
        }

        if ((*(float*)(obj + 0x0C) < pos->x) && (*(float*)(obj + 0x10) < pos->z) &&
            (pos->x < *(float*)(obj + 0x14)) && (pos->z < *(float*)(obj + 0x18))) {
            nz = (double)(pos->z - *(float*)(obj + 8));
            nx = (double)(pos->x - *(float*)(obj + 4));
            d = (double)(float)(nx * nx + (double)(float)(nz * nz));
            if (d < (double)FLOAT_80330ef4) {
                d = (double)FLOAT_80330ef4;
            }

            if (*(s32*)(obj + 0x1C) == 2) {
                if (d < (double)*(float*)(obj + 0x34)) {
                    yRand = (double)(FLOAT_80330ef8 - *(float*)(obj + 0x38) * *(float*)(obj + 0x38));
                    d = (double)sqrtf((float)d);
                    if (d <= DOUBLE_80330f10) {
                        d = DAT_8032ec20;
                    }

                    inv = (double)(float)(yRand / d);
                    out->x = (float)(nx * inv + (double)out->x);
                    yRand = (double)RandF__5CMathFv(&Math);
                    out->y = (float)((double)(float)(FLOAT_80330f18 + yRand) * (double)(float)(FLOAT_80330ef8 - *(float*)(obj + 0x38) * *(float*)(obj + 0x38)) + (double)out->y);
                    out->z = (float)(nz * inv + (double)out->z);
                }
            } else {
                PSVECScale((Vec*)(obj + 0x58), &tmp, FLOAT_80330ef8 - (float)(d / (double)*(float*)(obj + 0x34)));
                PSVECAdd(out, &tmp, out);
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::searchFreeObj()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::getObj(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800d96d8
 * PAL Size: 360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CWind::AddAmbient(float dir, float speed)
{
	u8* freeObj;
	u8* scan;
	int group;

	scan = (u8*)this;
	group = 4;
	do {
		freeObj = scan;
		if (((s8)scan[0] >= 0) ||
		    ((freeObj = scan + 100), (s8)freeObj[0] >= 0) ||
		    ((freeObj = scan + 200), (s8)freeObj[0] >= 0) ||
		    ((freeObj = scan + 300), (s8)freeObj[0] >= 0) ||
		    ((freeObj = scan + 400), (s8)freeObj[0] >= 0) ||
		    ((freeObj = scan + 500), (s8)freeObj[0] >= 0) ||
		    ((freeObj = scan + 600), (s8)freeObj[0] >= 0) ||
		    ((freeObj = scan + 700), (s8)freeObj[0] >= 0)) {
			goto found;
		}

		scan += 800;
		group--;
	} while (group != 0);

	freeObj = 0;
found:
	if (freeObj == 0) {
		System.Printf(DAT_801db568);
		return -1;
	}

	*(s32*)(freeObj + 0x1C) = 0;
	freeObj[0] = (freeObj[0] & 0x7F) | 0x80;

	int id = *(s32*)((u8*)this + 0xC80);
	*(s32*)((u8*)this + 0xC80) = id + 1;
	*(s32*)(freeObj + 0x20) = id;

	*(float*)(freeObj + 0x48) = dir;
	*(float*)(freeObj + 0x44) = dir;
	*(float*)(freeObj + 0x40) = dir;

	*(float*)(freeObj + 0x54) = speed;
	*(float*)(freeObj + 0x50) = speed;
	*(float*)(freeObj + 0x4C) = speed;

	return *(s32*)(freeObj + 0x20);
}

/*
 * --INFO--
 * PAL Address: 0x800d9538
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CWind::AddDiffuse(const Vec* pos, float radius, float dir, float speed)
{
	u8* freeObj;
	u8* scan;
	int freeIdx;
	int group;

	scan = (u8*)this;
	freeIdx = 0;
	group = 4;
	do {
		freeObj = scan;
		if (((((s8)scan[0] >= 0) || ((freeObj = scan + 100), (s8)freeObj[0] >= 0)) ||
		     ((freeObj = scan + 200), (s8)freeObj[0] >= 0)) ||
		    (((freeObj = scan + 300), (s8)freeObj[0] >= 0) ||
		     ((freeObj = scan + 400), (s8)freeObj[0] >= 0)) ||
		   (((freeObj = scan + 500), (s8)freeObj[0] >= 0) ||
		    (((freeObj = scan + 600), (s8)freeObj[0] >= 0) ||
		     ((freeObj = scan + 700), (s8)scan[700] >= 0)))) {
			goto found;
		}

		freeIdx += 7;
		scan += 800;
		group--;
	} while (group != 0);
	freeObj = 0;

found:

	if (freeObj == 0) {
		System.Printf(DAT_801db548, freeIdx);
		return -1;
	}

	const float x = pos->x;
	const float z = pos->z;

	freeObj[0x1C] = 0;
	freeObj[0x1D] = 0;
	freeObj[0x1E] = 0;
	freeObj[0x1F] = 1;
	freeObj[0] = (freeObj[0] & 0x7F) | 0x80;

	int id = *(s32*)((u8*)this + 0xC80);
	*(s32*)((u8*)this + 0xC80) = id + 1;
	*(s32*)(freeObj + 0x20) = id;

	*(float*)(freeObj + 0x48) = dir;
	*(float*)(freeObj + 0x44) = dir;
	*(float*)(freeObj + 0x40) = dir;

	*(float*)(freeObj + 0x54) = speed;
	*(float*)(freeObj + 0x50) = speed;
	*(float*)(freeObj + 0x4C) = speed;

	*(float*)(freeObj + 0x30) = radius;
	*(float*)(freeObj + 0x34) = radius * radius;

	*(float*)(freeObj + 0x04) = x;
	*(float*)(freeObj + 0x08) = z;
	*(float*)(freeObj + 0x0C) = x - radius;
	*(float*)(freeObj + 0x10) = z - radius;
	*(float*)(freeObj + 0x14) = x + radius;
	*(float*)(freeObj + 0x18) = z + radius;

	return *(s32*)(freeObj + 0x20);
}

/*
 * --INFO--
 * PAL Address: 0x800d93bc
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CWind::AddSphere(const Vec* pos, float radius, float speed, int life)
{
	u8* freeObj;
	int freeIdx = 0;
	u8* scan = (u8*)this;
	int group = 4;

	do {
		freeObj = scan;
		if (((((s8)scan[0] >= 0) || ((freeObj = scan + 100), (s8)freeObj[0] >= 0)) ||
		     ((freeObj = scan + 200), (s8)freeObj[0] >= 0)) ||
		    (((freeObj = scan + 300), (s8)freeObj[0] >= 0) ||
		     ((freeObj = scan + 400), (s8)freeObj[0] >= 0)) ||
		   (((freeObj = scan + 500), (s8)freeObj[0] >= 0) ||
		    (((freeObj = scan + 600), (s8)freeObj[0] >= 0) ||
		     ((freeObj = scan + 700), (s8)scan[700] >= 0)))) {
			goto found;
		}
		freeIdx += 7;
		scan += 800;
		group--;
	} while (group != 0);
	freeObj = 0;

found:

	if (freeObj == 0) {
		System.Printf(DAT_801db528, life, freeIdx);
		return -1;
	}

	*(s32*)(freeObj + 0x1C) = 2;
	freeObj[0] = (freeObj[0] & 0x7F) | 0x80;

	int id = *(s32*)((u8*)this + 0xC80);
	*(s32*)((u8*)this + 0xC80) = id + 1;
	*(s32*)(freeObj + 0x20) = id;

	*(float*)(freeObj + 0x54) = speed;
	*(float*)(freeObj + 0x50) = speed;
	*(float*)(freeObj + 0x4C) = speed;

	*(float*)(freeObj + 0x2C) = radius;
	*(s32*)(freeObj + 0x24) = life;
	*(s32*)(freeObj + 0x28) = 0;
	*(float*)(freeObj + 0x04) = pos->x;
	*(float*)(freeObj + 0x08) = pos->z;

	return *(s32*)(freeObj + 0x20);
}

/*
 * --INFO--
 * PAL Address: 0x800d92fc
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CWind::ChangePower(int id, float power)
{
	u8* found;
	u8* scan = (u8*)this;
	int group = 8;

	do {
		found = scan;
		if (((s8)found[0] >= 0) || (id != *(s32*)(found + 0x20))) {
			;
		} else {
			goto found_label;
		}

		found = scan + 100;
		if (((s8)found[0] >= 0) || (id != *(s32*)(found + 0x20))) {
			;
		} else {
			goto found_label;
		}

		found = scan + 200;
		if (((s8)found[0] >= 0) || (id != *(s32*)(found + 0x20))) {
			;
		} else {
			goto found_label;
		}

		found = scan + 300;
		if (((s8)found[0] >= 0) || (id != *(s32*)(found + 0x20))) {
			;
		} else {
			goto found_label;
		}

		scan += 400;
		group--;
	} while (group != 0);
	found = 0;

found_label:
	if (found != 0) {
		*(float*)(found + 0x54) = power;
		*(float*)(found + 0x4C) = power;
	}
}

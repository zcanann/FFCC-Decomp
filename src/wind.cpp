#include "ffcc/wind.h"

#include <string.h>
#include <math.h>
#include "ffcc/graphic.h"
#include "ffcc/color.h"
#include "ffcc/vector.h"
#include "ffcc/p_camera.h"
#include "ffcc/math.h"
#include "ffcc/goout.h"
#include "ffcc/p_game.h"

extern CGraphic Graphic;
extern CCameraPcs CameraPcs;
extern u32 CFlat; // Temporary - needs proper declaration
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
extern double DOUBLE_80330f00;
extern double DOUBLE_80330f08;
extern double DOUBLE_80330f10;
extern double DOUBLE_80330f40;
extern double DAT_8032ec20;

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
 * Address:	800d9d60
 * Size:	764
 */
void CWind::Frame()
{
    u8* obj = (u8*)this;

    for (int i = 0; i < 32; i++, obj += 100) {
        if ((s8)obj[0] >= 0) {
            continue;
        }

        int rnd = Rand__5CMathFUl(&Math, 10);
        if (rnd == 0) {
            float rate = FLOAT_80330f24;
            if (Rand__5CMathFUl(&Math, 3) == 0) {
                rate = FLOAT_80330f20;
            }

            *(float*)(obj + 0x54) = *(float*)(obj + 0x54) + (*(float*)(obj + 0x4C) * rate);

            float clamped = FLOAT_80330ef0;
            float value = *(float*)(obj + 0x54);
            if (clamped <= value) {
                clamped = value;
                if (*(float*)(obj + 0x4C) < value) {
                    clamped = *(float*)(obj + 0x4C);
                }
            }
            *(float*)(obj + 0x54) = clamped;
        }

        int type = *(int*)(obj + 0x1C);
        if (((type == 0) || (type == 1)) &&
            (Rand__5CMathFUl(&Math, 0x1E) == 0) &&
            (*(float*)(obj + 0x50) < (FLOAT_80330f28 * *(float*)(obj + 0x4C)))) {
            float rate = FLOAT_80330f30;
            if (Rand__5CMathFUl(&Math, 3) == 0) {
                rate = FLOAT_80330f2c;
            }

            *(float*)(obj + 0x48) = *(float*)(obj + 0x48) + (*(float*)(obj + 0x40) * rate);

            float value = *(float*)(obj + 0x48);
            float clamped = *(float*)(obj + 0x40);
            if (clamped <= value) {
                float max = FLOAT_80330f34 + clamped;
                clamped = value;
                if (max < value) {
                    clamped = max;
                }
            }
            *(float*)(obj + 0x48) = clamped;
        }

        if (type == 2) {
            *(int*)(obj + 0x28) = *(int*)(obj + 0x28) + 1;
            if (*(u32*)(obj + 0x24) <= *(u32*)(obj + 0x28)) {
                obj[0] = obj[0] & 0x7F;
                continue;
            }

            *(float*)(obj + 0x38) =
                (float)(((double)*(int*)(obj + 0x28) - DOUBLE_80330f40) /
                        ((double)*(int*)(obj + 0x24) - DOUBLE_80330f40));
            *(float*)(obj + 0x30) = *(float*)(obj + 0x2C) * *(float*)(obj + 0x38);
            *(float*)(obj + 0x34) = *(float*)(obj + 0x30) * *(float*)(obj + 0x30);
            *(float*)(obj + 0x0C) = *(float*)(obj + 4) - *(float*)(obj + 0x30);
            *(float*)(obj + 0x10) = *(float*)(obj + 8) - *(float*)(obj + 0x30);
            *(float*)(obj + 0x14) = *(float*)(obj + 4) + *(float*)(obj + 0x30);
            *(float*)(obj + 0x18) = *(float*)(obj + 8) + *(float*)(obj + 0x30);
        }

        *(float*)(obj + 0x50) =
            *(float*)(obj + 0x50) + (FLOAT_80330f38 * (*(float*)(obj + 0x54) - *(float*)(obj + 0x50)));

        *(float*)(obj + 0x44) = *(float*)(obj + 0x44) +
                                ((FLOAT_80330f2c * RandF__5CMathFv(&Math)) +
                                 ((FLOAT_80330f38 * (*(float*)(obj + 0x48) - *(float*)(obj + 0x44))) -
                                  FLOAT_80330f28));

        if ((type == 0) || (type == 1)) {
            *(float*)(obj + 0x58) = *(float*)(obj + 0x50) * (float)sin((double)*(float*)(obj + 0x44));
            *(float*)(obj + 0x5C) = *(float*)(obj + 0x50) *
                                    (FLOAT_80330f20 * RandF__5CMathFv(&Math) + FLOAT_80330f24);
            *(float*)(obj + 0x60) = *(float*)(obj + 0x50) * (float)cos((double)*(float*)(obj + 0x44));
        }
    }
}

/*
 * --INFO--
 * Address:	800d9b2c
 * Size:	564
 */
void CWind::Draw()
{
	// TODO: Implement wind rendering
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
    float f;
    u32 clsMask;
    int cls;

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
                    if (d <= (double)FLOAT_80330ef0) {
                        if (DOUBLE_80330f10 <= d) {
                            f = (float)d;
                            clsMask = (u32)f & 0x7f800000;
                            if (clsMask == 0x7f800000) {
                                cls = (((u32)f & 0x7fffff) == 0) ? 2 : 1;
                            } else if ((clsMask < 0x7f800000) && (clsMask == 0)) {
                                cls = (((u32)f & 0x7fffff) == 0) ? 3 : 5;
                            } else {
                                cls = 4;
                            }
                            if (cls == 1) {
                                d = DAT_8032ec20;
                            }
                        } else {
                            d = DAT_8032ec20;
                        }
                    } else {
                        inv = 1.0 / sqrt(d);
                        inv = DOUBLE_80330f00 * inv * -(d * inv * inv - DOUBLE_80330f08);
                        inv = DOUBLE_80330f00 * inv * -(d * inv * inv - DOUBLE_80330f08);
                        d = (double)(float)(d * DOUBLE_80330f00 * inv * -(d * inv * inv - DOUBLE_80330f08));
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
 * Address:	TODO
 * Size:	TODO
 */
void CWind::AddAmbient(float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::AddDiffuse(const Vec*, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::AddSphere(const Vec*, float, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::ChangePower(int, float)
{
	// TODO
}

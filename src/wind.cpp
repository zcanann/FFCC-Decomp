#include "ffcc/wind.h"

#include <string.h>
#include "ffcc/graphic.h"
#include "ffcc/color.h"
#include "ffcc/vector.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/game.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_camera.h"
#include "ffcc/system.h"

CWind Wind;

extern int __float_nan[];
extern "C" double cos(double);
extern "C" double sin(double);

static inline s8 GetWindActiveFlag(const WindObject* obj)
{
    return static_cast<s8>((((int)(obj->flags & 0xC0)) << 24) >> 31);
}

static inline s8 GetGrassActiveFlag(const WindGrassObject* obj)
{
    return static_cast<s8>((((int)(obj->flags & 0xC0)) << 24) >> 31);
}

const float FLOAT_80330ef0 = 0.0f;
const float FLOAT_80330ef4 = 0.0001f;
const float FLOAT_80330ef8 = 1.0f;
const float FLOAT_80330f20 = 0.5f;
const float FLOAT_80330f24 = -0.25f;
const float FLOAT_80330f28 = 0.1f;
const float FLOAT_80330f2c = 0.2f;
const float FLOAT_80330f30 = -0.1f;
const float FLOAT_80330f34 = 0.25f;
const float FLOAT_80330f38 = 0.05f;
const float FLOAT_80330f18 = -0.5f;
const float FLOAT_80330f1c = 255.0f;
const double DOUBLE_80330f00 = 0.5;
const double DOUBLE_80330f08 = 3.0;
const double DOUBLE_80330f10 = 0.0;
const double DOUBLE_80330f40 = 4503601774854144.0;
extern "C" {
const char DAT_801db528[] = {
    0x95, 0x97, 0x82, 0xF0, 0x92, 0xC7, 0x89, 0xC1, 0x82, 0xC5, 0x82, 0xAB, 0x82, 0xDC, 0x82, 0xB9,
    0x82, 0xF1, 0x81, 0x42, 0x28, 0x73, 0x70, 0x68, 0x65, 0x72, 0x65, 0x29, 0x0A, 0x00, 0x00, 0x00
};
const char DAT_801db548[] = {
    0x95, 0x97, 0x82, 0xF0, 0x92, 0xC7, 0x89, 0xC1, 0x82, 0xC5, 0x82, 0xAB, 0x82, 0xDC, 0x82, 0xB9,
    0x82, 0xF1, 0x81, 0x42, 0x28, 0x64, 0x69, 0x66, 0x66, 0x75, 0x73, 0x65, 0x29, 0x0A, 0x00, 0x00
};
const char DAT_801db568[] = {
    0x95, 0x97, 0x82, 0xF0, 0x92, 0xC7, 0x89, 0xC1, 0x82, 0xC5, 0x82, 0xAB, 0x82, 0xDC, 0x82, 0xB9,
    0x82, 0xF1, 0x81, 0x42, 0x28, 0x61, 0x6D, 0x62, 0x69, 0x65, 0x6E, 0x74, 0x29, 0x0A, 0x00, 0x00
};
}

static inline float WindSqrtf(float x)
{
    union {
        float f;
        unsigned long bits;
    } bits;
    int fpclass;

    if (x > FLOAT_80330ef0) {
        double guess = __frsqrte((double)x);
        guess = DOUBLE_80330f00 * guess * (DOUBLE_80330f08 - guess * guess * x);
        guess = DOUBLE_80330f00 * guess * (DOUBLE_80330f08 - guess * guess * x);
        guess = DOUBLE_80330f00 * guess * (DOUBLE_80330f08 - guess * guess * x);
        return (float)(x * guess);
    }

    if ((double)x < DOUBLE_80330f10) {
        return *(float*)__float_nan;
    }

    bits.f = x;
    switch (bits.bits & 0x7f800000) {
    case 0x7f800000:
        if ((bits.bits & 0x7fffff) != 0) {
            fpclass = 1;
        } else {
            fpclass = 2;
        }
        break;
    case 0:
        if ((bits.bits & 0x7fffff) != 0) {
            fpclass = 5;
        } else {
            fpclass = 3;
        }
        break;
    default:
        fpclass = 4;
        break;
    }

    if (fpclass == 1) {
        return *(float*)__float_nan;
    }

    return x;
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
    WindObject* obj;
    WindObject* scan = m_objects;

    for (int i = 0; i < 32; i++, scan++) {
        if (GetWindActiveFlag(scan) != 0) {
            if (id == scan->id) {
                obj = scan;
                goto found;
            }
        }
    }

    obj = 0;

found:
    if (obj == 0) {
        return;
    }

    obj->targetPower = power;
    obj->basePower = power;
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
	int checked = 0;
	int blocks = 4;
	WindObject* scan = m_objects;
	WindObject* obj;

	do {
		if (GetWindActiveFlag(scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}

		checked += 7;
		scan++;
	} while (--blocks != 0);

	obj = 0;

found:
	if (obj == 0) {
		System.Printf(const_cast<char*>(DAT_801db528), life, checked);
		return -1;
	}

	obj->type = 2;
	float centerZ = pos->z;
	float centerX = pos->x;
	obj->flags = static_cast<u8>(__rlwimi(obj->flags, 1, 7, 24, 24));

	int id = m_nextId;
	m_nextId = id + 1;
	obj->id = id;

	obj->targetPower = speed;
	obj->curPower = speed;
	obj->basePower = speed;

	obj->baseRadius = radius;
	obj->life = life;
	obj->lifeTimer = 0;
	obj->centerX = centerX;
	obj->centerZ = centerZ;

	return obj->id;
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
	int checked = 0;
	WindObject* scan = m_objects;
	WindObject* obj;

	for (int blocks = 4; blocks != 0; blocks--) {
		if (GetWindActiveFlag(scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}

		checked += 7;
		scan++;
	}

	obj = 0;

found:
	if (obj == 0) {
		System.Printf(const_cast<char*>(DAT_801db548), checked);
		return -1;
	}

	int type = 1;
	float centerX = pos->x;
	obj->type = type;
	float radiusSq = radius * radius;
	float centerZ = pos->z;
	float minX = centerX - radius;
	float minZ = centerZ - radius;
	obj->flags = static_cast<u8>(__rlwimi(obj->flags, 1, 7, 24, 24));
	float maxX = centerX + radius;
	float maxZ = centerZ + radius;

	int id = m_nextId;
	m_nextId = id + 1;
	obj->id = id;

	obj->targetDir = dir;
	obj->curDir = dir;
	obj->baseDir = dir;

	obj->targetPower = speed;
	obj->curPower = speed;
	obj->basePower = speed;

	obj->radius = radius;
	obj->radiusSq = radiusSq;

	obj->centerX = centerX;
	obj->centerZ = centerZ;
	obj->minX = minX;
	obj->minZ = minZ;
	obj->maxX = maxX;
	obj->maxZ = maxZ;

	return obj->id;
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
	int blocks = 4;
	WindObject* scan = m_objects;
	WindObject* obj;

	do {
		if (GetWindActiveFlag(scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}
		if (GetWindActiveFlag(++scan) == 0) {
			obj = scan;
			goto found;
		}

		scan++;
	} while (--blocks != 0);

	obj = 0;

found:
	if (obj == 0) {
		System.Printf(const_cast<char*>(DAT_801db568));
		return -1;
	}

	obj->type = 0;
	obj->flags = static_cast<u8>(__rlwimi(obj->flags, 1, 7, 24, 24));

	int id = m_nextId;
	m_nextId = id + 1;
	obj->id = id;

	obj->targetDir = dir;
	obj->curDir = dir;
	obj->baseDir = dir;

	obj->targetPower = speed;
	obj->curPower = speed;
	obj->basePower = speed;

	return obj->id;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 160b
 * EN Address: 0x800f55cc
 * EN Size: 116b
 * JP Address: TODO
 * JP Size: TODO
 */
WindObject* CWind::getObj(int id)
{
    WindObject* obj = m_objects;

    for (int i = 0; i < 32; i++, obj++) {
        if (GetWindActiveFlag(obj) != 0) {
            if (id == obj->id) {
                return obj;
            }
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 192b
 * EN Address: 0x800f5564
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
WindObject* CWind::searchFreeObj()
{
    WindObject* obj = m_objects;

    for (int i = 0; i < 32; i++, obj++) {
        if (GetWindActiveFlag(obj) == 0) {
            return obj;
        }
    }

    return 0;
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
    WindObject* obj;
    int i;
    float zero;
    Vec randTmp;
    Vec tmp;
    Vec tmp2;
    zero = FLOAT_80330ef0;
    out->z = FLOAT_80330ef0;
    out->y = zero;
    out->x = zero;

    if ((MenuPcs.m_mode == 2) || (Game.m_gameWork.m_gamePaused != 0)) {
        return;
    }

    obj = m_objects;
    i = 0;
    do {
        if (GetWindActiveFlag(obj) != 0) {
            if (obj->type == 0) {
                if (randomize == 0) {
                    PSVECAdd(out, &obj->force, out);
                } else {
                    PSVECScale(&obj->force, &randTmp, (float)Math.RandF());
                    PSVECAdd(out, &randTmp, out);
                }
            } else if ((obj->minX < pos->x) && (obj->minZ < pos->z) && (obj->maxX > pos->x) && (obj->maxZ > pos->z)) {
                const float deltaZ = pos->z - obj->centerZ;
                const float deltaX = pos->x - obj->centerX;
                float distanceSq = deltaX * deltaX + deltaZ * deltaZ;
                if (distanceSq < FLOAT_80330ef4) {
                    distanceSq = FLOAT_80330ef4;
                }

                if (obj->type == 2) {
                    if (distanceSq < obj->radiusSq) {
                        const float lifeScale = FLOAT_80330ef8 - obj->lifeRatio * obj->lifeRatio;
                        const float distance = WindSqrtf(distanceSq);
                        const float forceScale = lifeScale / distance;
                        out->x += deltaX * forceScale;
                        out->y += (FLOAT_80330f18 + Math.RandF()) * lifeScale;
                        out->z += deltaZ * forceScale;
                    }
                } else {
                    PSVECScale(&obj->force, &tmp2, FLOAT_80330ef8 - distanceSq / obj->radiusSq);
                    PSVECAdd(out, &tmp2, out);
                }
            }
        }
        i = i + 1;
        obj++;
    } while (i < 32);
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
        WindObject* obj = m_objects;
        int i = 0;
        do {
            if (GetWindActiveFlag(obj) != 0) {
                if (obj->type == 1) {
                    CColor color(0xff, 0xff, 0, 0xff);
                    CVector center(obj->centerX, FLOAT_80330ef0, obj->centerZ);
                    Graphic.DrawSphere(viewMtx, reinterpret_cast<Vec*>(&center), obj->radius, &color.color);
                } else {
                    u8 alpha = (u8)(FLOAT_80330f1c * (FLOAT_80330ef8 - obj->lifeRatio));
                    CColor color(0xff, 0xff, 0x80, alpha);
                    CVector center(obj->centerX, FLOAT_80330ef0, obj->centerZ);
                    Graphic.DrawSphere(viewMtx, reinterpret_cast<Vec*>(&center), obj->radius, &color.color);
                }
            }

            i++;
            obj++;
        } while (i < 0x20);
    }
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
    WindObject* obj;
    int i;
    u32 rnd;
    float f0;
    float f1;
    float f2;

    obj = m_objects;
    i = 0;

    while (true) {
        if (GetWindActiveFlag(obj) != 0) {
            rnd = Math.Rand(10);
            if (rnd == 0) {
                rnd = Math.Rand(3);
                if (rnd == 0) {
                    f2 = FLOAT_80330f20;
                } else {
                    f2 = FLOAT_80330f24;
                }

                obj->targetPower = f2 * obj->basePower + obj->targetPower;
                f0 = obj->targetPower;
                f1 = FLOAT_80330ef0;
                if (!(f0 < f1)) {
                    f1 = obj->basePower;
                    if (!(f1 < f0)) {
                        f1 = f0;
                    }
                }
                obj->targetPower = f1;
            }

            if ((((obj->type == 0) || (obj->type == 1)) && ((rnd = Math.Rand(0x1E)), rnd == 0)) &&
                (obj->curPower < FLOAT_80330f28 * obj->basePower)) {
                rnd = Math.Rand(3);
                if (rnd == 0) {
                    f2 = FLOAT_80330f2c;
                } else {
                    f2 = FLOAT_80330f30;
                }

                obj->targetDir = f2 * obj->baseDir + obj->targetDir;
                f0 = obj->targetDir;
                f1 = obj->baseDir;
                if (!(f0 < f1)) {
                    f2 = FLOAT_80330f34 + f1;
                    f1 = f0;
                    if (f2 < f0) {
                        f1 = f2;
                    }
                }
                obj->targetDir = f1;
            }

            if (obj->type == 2) {
                obj->lifeTimer = obj->lifeTimer + 1;
                if (obj->life <= obj->lifeTimer) {
                    obj->flags = static_cast<u8>(__rlwimi(obj->flags, 0, 7, 24, 24));
                    goto next;
                }

                obj->lifeRatio = (float)obj->lifeTimer / (float)obj->life;
                obj->radius = obj->baseRadius * obj->lifeRatio;
                obj->radiusSq = obj->radius * obj->radius;
                obj->minX = obj->centerX - obj->radius;
                obj->minZ = obj->centerZ - obj->radius;
                obj->maxX = obj->centerX + obj->radius;
                obj->maxZ = obj->centerZ + obj->radius;
            }

            f0 = obj->targetPower;
            f1 = obj->curPower;
            f2 = FLOAT_80330f38;
            obj->curPower = f2 * (f0 - f1) + f1;
            f0 = Math.RandF();
            f1 = obj->targetDir;
            f2 = obj->curDir;
            obj->curDir = f2 + (FLOAT_80330f2c * f0 + (FLOAT_80330f38 * (f1 - f2) - FLOAT_80330f28));

            if ((obj->type == 0) || (obj->type == 1)) {
                obj->force.x = obj->curPower * (float)sin((double)obj->curDir);
                obj->force.y = obj->curPower * (FLOAT_80330f20 * Math.RandF() + FLOAT_80330f24);
                obj->force.z = obj->curPower * (float)cos((double)obj->curDir);
            }
        }

    next:
        i = i + 1;
        obj++;
        if (i >= 0x20) {
            return;
        }
    }
}

/*
 * --INFO--
 * Address:	800da05c
 * Size:	88
 */
void CWind::ClearAll()
{
	memset(m_objects, 0, sizeof(m_objects));
	m_nextId = 1;
	memset(m_grass, 0, sizeof(m_grass));
	m_nextGrassId = 10000000;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 196b
 * EN Address: UNUSED
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
WindGrassObject* CWind::searchFreeGrass()
{
    WindGrassObject* obj = m_grass;

    for (int i = 0; i < 512; i++, obj++) {
        if (GetGrassActiveFlag(obj) == 0) {
            return obj;
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 164b
 * EN Address: UNUSED
 * EN Size: 116b
 * JP Address: TODO
 * JP Size: TODO
 */
WindGrassObject* CWind::getGrass(int id)
{
    WindGrassObject* obj = m_grass;

    for (int i = 0; i < 512; i++, obj++) {
        if (GetGrassActiveFlag(obj) != 0) {
            if (id == obj->id) {
                return obj;
            }
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 668b
 * EN Address: UNUSED
 * EN Size: 412b
 * JP Address: TODO
 * JP Size: TODO
 */
int CWind::AddGrass(const Vec* pos)
{
    WindGrassObject* obj = searchFreeGrass();

    if (obj == 0) {
        return -1;
    }

    obj->flags = static_cast<u8>(__rlwimi(obj->flags, 1, 7, 24, 24));

    int id = m_nextGrassId;
    m_nextGrassId = id + 1;
    obj->id = id;
    obj->pos = *pos;

    return obj->id;
}

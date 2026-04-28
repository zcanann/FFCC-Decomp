#include "ffcc/wind.h"

#include <string.h>
#include "ffcc/graphic.h"
#include "ffcc/color.h"
#include "ffcc/vector.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/goout.h"
#include "ffcc/p_game.h"
#include "ffcc/p_camera.h"
#include "ffcc/system.h"

CWind Wind;

extern int __float_nan[];
double cos(double);
double sin(double);

static inline s8 GetWindActiveFlag(const WindObject* obj)
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
extern char DAT_801db528[];
extern char DAT_801db548[];
extern char DAT_801db568[];

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
    WindObject* obj = m_objects;
    s8 active;

    for (int blocks = 8; blocks != 0; blocks--) {
        active = GetWindActiveFlag(obj);
        if (active != 0 && id == obj->id) {
            goto found;
        }
        obj++;

        active = GetWindActiveFlag(obj);
        if (active != 0 && id == obj->id) {
            goto found;
        }
        obj++;

        active = GetWindActiveFlag(obj);
        if (active != 0 && id == obj->id) {
            goto found;
        }
        obj++;

        active = GetWindActiveFlag(obj);
        if (active != 0 && id == obj->id) {
            goto found;
        }
        obj++;
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
	WindObject* obj = m_objects;
	s8 active;

	do {
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}

		checked += 7;
		obj++;
	} while (--blocks != 0);

	obj = 0;

found:
	if (obj == 0) {
		System.Printf(DAT_801db528, life, checked);
		return -1;
	}

	float centerX = pos->x;
	obj->type = 2;
	float centerZ = pos->z;
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
	WindObject* obj = m_objects;
	s8 active;

	for (int blocks = 4; blocks != 0; blocks--) {
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}

		checked += 7;
		obj++;
	}

	obj = 0;

found:
	if (obj == 0) {
		System.Printf(DAT_801db548, checked);
		return -1;
	}

	float centerX = pos->x;
	obj->type = 1;
	float centerZ = pos->z;
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

	obj->radius = radius;
	obj->radiusSq = radius * radius;

	obj->centerX = centerX;
	obj->centerZ = centerZ;
	obj->minX = centerX - radius;
	obj->minZ = centerZ - radius;
	obj->maxX = centerX + radius;
	obj->maxZ = centerZ + radius;

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
	WindObject* obj = m_objects;
	s8 active;

	for (int blocks = 4; blocks != 0; blocks--) {
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}
		obj++;
		active = GetWindActiveFlag(obj);
		if (active == 0) {
			goto found;
		}

		obj++;
	}

	obj = 0;

found:
	if (obj == 0) {
		System.Printf(DAT_801db568);
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
    Vec tmp;
    zero = FLOAT_80330ef0;
    out->z = FLOAT_80330ef0;
    out->y = zero;
    out->x = zero;

    if ((*(s32*)((u8*)&MenuPcs + 0x740) == 2) || (Game.m_gameWork.m_gamePaused != 0)) {
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
                    PSVECScale(&obj->force, &tmp, (float)Math.RandF());
                    PSVECAdd(out, &tmp, out);
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
                    PSVECScale(&obj->force, &tmp, FLOAT_80330ef8 - distanceSq / obj->radiusSq);
                    PSVECAdd(out, &tmp, out);
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
    int i;
    WindObject* obj;
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
        i = 0;
        obj = m_objects;
        do {
            if (GetWindActiveFlag(obj) != 0) {
                if (obj->type == 1) {
                    CColor color(0xff, 0xff, 0, 0xff);
                    CVector pos(obj->centerX, FLOAT_80330ef0, obj->centerZ);
                    Graphic.DrawSphere(viewMtx, (Vec*)&pos, obj->radius, &color.color);
                } else {
                    int alpha = (int)(FLOAT_80330f1c * (FLOAT_80330ef8 - obj->lifeRatio));
                    CColor color(0xff, 0xff, 0x80, alpha);
                    CVector pos(obj->centerX, FLOAT_80330ef0, obj->centerZ);
                    Graphic.DrawSphere(viewMtx, (Vec*)&pos, obj->radius, &color.color);
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
    double d0;

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

                obj->targetPower = obj->basePower * f2 + obj->targetPower;
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

                obj->targetDir = obj->baseDir * f2 + obj->targetDir;
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

            obj->curPower = FLOAT_80330f38 * (obj->targetPower - obj->curPower) + obj->curPower;
            f0 = Math.RandF();
            obj->curDir = obj->curDir +
                          (FLOAT_80330f2c * f0 +
                           (FLOAT_80330f38 * (obj->targetDir - obj->curDir) - FLOAT_80330f28));

            if ((obj->type == 0) || (obj->type == 1)) {
                d0 = (double)sin((double)obj->curDir);
                obj->force.x = obj->curPower * (float)d0;
                obj->force.y = obj->curPower * (FLOAT_80330f20 * Math.RandF() + FLOAT_80330f24);
                d0 = (double)cos((double)obj->curDir);
                obj->force.z = obj->curPower * (float)d0;
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
	memset(_padC84, 0, sizeof(_padC84));
	m_unk7C84 = 10000000;
}

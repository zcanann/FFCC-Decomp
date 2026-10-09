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
#include <math.h>

CWind Wind;

extern "C" {
const char sWindAddSphereFailedMsg[] = {
    0x95, 0x97, 0x82, 0xF0, 0x92, 0xC7, 0x89, 0xC1, 0x82, 0xC5, 0x82, 0xAB, 0x82, 0xDC, 0x82, 0xB9,
    0x82, 0xF1, 0x81, 0x42, 0x28, 0x73, 0x70, 0x68, 0x65, 0x72, 0x65, 0x29, 0x0A, 0x00
};
const char sWindAddDiffuseFailedMsg[] = {
    0x95, 0x97, 0x82, 0xF0, 0x92, 0xC7, 0x89, 0xC1, 0x82, 0xC5, 0x82, 0xAB, 0x82, 0xDC, 0x82, 0xB9,
    0x82, 0xF1, 0x81, 0x42, 0x28, 0x64, 0x69, 0x66, 0x66, 0x75, 0x73, 0x65, 0x29, 0x0A, 0x00
};
const char sWindAddAmbientFailedMsg[] = {
    0x95, 0x97, 0x82, 0xF0, 0x92, 0xC7, 0x89, 0xC1, 0x82, 0xC5, 0x82, 0xAB, 0x82, 0xDC, 0x82, 0xB9,
    0x82, 0xF1, 0x81, 0x42, 0x28, 0x61, 0x6D, 0x62, 0x69, 0x65, 0x6E, 0x74, 0x29, 0x0A, 0x00
};
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
inline WindObject* CWind::getObj(int id)
{
    WindObject* obj = m_objects;

    for (int i = 0; i < 32; i++, obj++) {
        if ((obj->flagBits.active != 0) && (id == obj->id)) {
            return obj;
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
inline WindObject* CWind::searchFreeObj()
{
    WindObject* obj = m_objects;

    for (int i = 0; i < 32; i++, obj++) {
        if (obj->flagBits.active == 0) {
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
inline WindGrassObject* CWind::getGrass(int id)
{
    WindGrassObject* grass = m_grass;

    for (int i = 0; i < 512; i++, grass++) {
        if ((grass->flagBits.active != 0) && (id == grass->id)) {
            return grass;
        }
    }

    return 0;
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
inline WindGrassObject* CWind::searchFreeGrass()
{
    WindGrassObject* grass = m_grass;

    for (int i = 0; i < 512; i++, grass++) {
        if (grass->flagBits.active == 0) {
            return grass;
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
inline int CWind::AddGrass(const Vec* pos)
{
    WindGrassObject* grass = searchFreeGrass();
    if (grass == 0) {
        return -1;
    }

    grass->flagBits.active = 1;
    grass->pos = *pos;

    int id = m_nextGrassId;
    m_nextGrassId = id + 1;
    grass->id = id;

    return grass->id;
}

/*
 * --INFO--
 * PAL Address: 0x800d92fc
 * PAL Size: 192b
 * EN Address: 0x800D8AC8
 * EN Size: 192b
 * JP Address: 0x800D6740
 * JP Size: 192b
 */
void CWind::ChangePower(int id, float power)
{
    WindObject* obj = getObj(id);

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
 * EN Address: 0x800D8B88
 * EN Size: 380b
 * JP Address: 0x800D6800
 * JP Size: 380b
 */
int CWind::AddSphere(const Vec* pos, float radius, float speed, int life)
{
	WindObject* obj = searchFreeObj();

	if (obj == 0) {
		System.Printf(const_cast<char*>(sWindAddSphereFailedMsg));
		return -1;
	}

	obj->type = 2;
	float centerZ = pos->z;
	float centerX = pos->x;
	obj->flagBits.active = 1;

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
 * EN Address: 0x800D8D04
 * EN Size: 416b
 * JP Address: 0x800D697C
 * JP Size: 416b
 */
int CWind::AddDiffuse(const Vec* pos, float radius, float dir, float speed)
{
	WindObject* obj = searchFreeObj();

	if (obj == 0) {
		System.Printf(const_cast<char*>(sWindAddDiffuseFailedMsg));
		return -1;
	}

	obj->type = 1;
	obj->flagBits.active = 1;

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

	obj->centerX = pos->x;
	obj->centerZ = pos->z;
	obj->minX = pos->x - radius;
	obj->minZ = pos->z - radius;
	obj->maxX = pos->x + radius;
	obj->maxZ = pos->z + radius;

	return obj->id;
}

/*
 * --INFO--
 * PAL Address: 0x800d96d8
 * PAL Size: 360b
 * EN Address: 0x800D8EA4
 * EN Size: 360b
 * JP Address: 0x800D6B1C
 * JP Size: 360b
 */
int CWind::AddAmbient(float dir, float speed)
{
	WindObject* obj = searchFreeObj();

	if (obj == 0) {
		System.Printf(const_cast<char*>(sWindAddAmbientFailedMsg));
		return -1;
	}

	obj->type = 0;
	obj->flagBits.active = 1;

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
 * EN Address: 0x800D900C
 * EN Size: 748b
 * JP Address: 0x800D6C84
 * JP Size: 620b
 */
void CWind::Calc(Vec* out, const Vec* pos, int randomize)
{
    WindObject* obj;
    int i;
    float zero;
    Vec randTmp;
    Vec tmp;
    Vec tmp2;
    zero = 0.0f;
    out->x = out->y = out->z = zero;

    if ((MenuPcs.m_mode == 2) || (Game.m_gameWork.m_gamePaused != 0)) {
        return;
    }

    obj = m_objects;
    i = 0;
    do {
        if (obj->flagBits.active != 0) {
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
                float minDistanceSq = 0.0001f;
                if (distanceSq < minDistanceSq) {
                    distanceSq = minDistanceSq;
                }

                if (obj->type == 2) {
                    if (distanceSq < obj->radiusSq) {
                        const float lifeScale = 1.0f - obj->lifeRatio * obj->lifeRatio;
                        const float distance = sqrtf(distanceSq);
                        const float forceScale = lifeScale / distance;
                        out->x += deltaX * forceScale;
                        out->y += (-0.5f + Math.RandF()) * lifeScale;
                        out->z += deltaZ * forceScale;
                    }
                } else {
                    PSVECScale(&obj->force, &tmp2, 1.0f - distanceSq / obj->radiusSq);
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
 * EN Address: 0x800D92F8
 * EN Size: 564b
 * JP Address: 0x800D6EF0
 * JP Size: 564b
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

    if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_Wind) != 0) {
        WindObject* obj = m_objects;
        int i = 0;
        do {
            if (obj->flagBits.active != 0) {
                if (obj->type == 1) {
                    const CColor& color = CColor(0xff, 0xff, 0, 0xff);
                    Graphic.DrawSphere(viewMtx,
                                       reinterpret_cast<Vec*>(&CVector(obj->centerX, 0.0f, obj->centerZ)),
                                       obj->radius, const_cast<_GXColor*>(&color.color));
                } else {
                    u8 alpha = (u8)(255.0f * (1.0f - obj->lifeRatio));
                    const CColor& color = CColor(0xff, 0xff, 0x80, alpha);
                    Graphic.DrawSphere(viewMtx,
                                       reinterpret_cast<Vec*>(&CVector(obj->centerX, 0.0f, obj->centerZ)),
                                       obj->radius, const_cast<_GXColor*>(&color.color));
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
 * EN Address: 0x800D952C
 * EN Size: 764b
 * JP Address: 0x800D7124
 * JP Size: 764b
 */
void CWind::Frame()
{
    WindObject* obj;
    int i;
    u32 rnd;
    float f0;
    float f1;

    obj = m_objects;
    i = 0;

    while (true) {
        if (obj->flagBits.active != 0) {
            rnd = Math.Rand(10);
            if (rnd == 0) {
                obj->targetPower += obj->basePower * (((rnd = Math.Rand(3)) == 0) ? 0.5f : -0.25f);
                f0 = obj->targetPower;
                f1 = 0.0f;
                f1 = (f0 < f1) ? f1 : ((obj->basePower < f0) ? obj->basePower : f0);
                obj->targetPower = f1;
            }

            if ((((obj->type == 0) || (obj->type == 1)) && ((rnd = Math.Rand(0x1E)), rnd == 0)) &&
                (obj->curPower < 0.1f * obj->basePower)) {
                rnd = Math.Rand(3);
                if (rnd == 0) {
                    f1 = 0.2f;
                } else {
                    f1 = -0.1f;
                }

                f0 = obj->baseDir;
                obj->targetDir = f0 * f1 + obj->targetDir;
                f0 = obj->targetDir;
                f1 = obj->baseDir;
                f1 = (f0 < f1) ? f1 : ((0.25f + f1 < f0) ? 0.25f + f1 : f0);
                obj->targetDir = f1;
            }

            if (obj->type == 2) {
                obj->lifeTimer = obj->lifeTimer + 1;
                if (obj->life <= obj->lifeTimer) {
                    obj->flagBits.active = 0;
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

            obj->curPower += 0.05f * (obj->targetPower - obj->curPower);
            obj->curDir += 0.2f * Math.RandF() +
                (0.05f * (obj->targetDir - obj->curDir) - 0.1f);

            if ((obj->type == 0) || (obj->type == 1)) {
                obj->force.x = obj->curPower * (float)sin((double)obj->curDir);
                obj->force.y = obj->curPower * (0.5f * Math.RandF() + -0.25f);
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
 * PAL Address: 0x800DA05C
 * PAL Size: 88b
 * EN Address: 0x800D9828
 * EN Size: 88b
 * JP Address: 0x800D7420
 * JP Size: 88b
 */
void CWind::ClearAll()
{
	memset(m_objects, 0, sizeof(m_objects));
	m_nextId = 1;
	memset(m_grass, 0, sizeof(m_grass));
	m_nextGrassId = 10000000;
}

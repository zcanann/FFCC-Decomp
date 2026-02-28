#include "ffcc/gobject.h"

#include "ffcc/cflat_runtime.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/quadobj.h"
#include "ffcc/sound.h"

#include <math.h>
#include <string.h>

extern CPartMng PartMng;
extern CMath Math;
extern unsigned char CFlat[];
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, CGBaseObj*, int, int, int, CFlatRuntime::CStack*, CFlatRuntime::CStack*);
extern "C" int SearchNode__Q26CChara6CModelFPc(CChara::CModel*, char*);
extern "C" CGObject* FindGObjNext__13CFlatRuntime2FP8CGObject(void*, CGObject*);
extern "C" CGQuadObj* FindGQuadObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGQuadObj* FindGQuadObjNext__13CFlatRuntime2FP9CGQuadObj(void*, CGQuadObj*);
extern "C" int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, u32);
extern "C" int CalcHitSlide__7CMapObjFP3Vecf(void*, Vec*);
extern "C" void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
extern "C" void GetHitFaceNormal__7CMapObjFP3Vec(void*, Vec*);
extern "C" int PlaySe3D__6CSoundFiP3Vecffi(CSound*, int, Vec*, float, float, int);
extern unsigned char DAT_8032ec90[];
extern float FLOAT_8033033c;
extern float FLOAT_80330340;
extern float FLOAT_80330360;
extern double DOUBLE_80330400;
extern float FLOAT_80330410;
extern float FLOAT_8033041c;
extern float FLOAT_80330420;
extern float FLOAT_80330424;

static inline void CallOnPush(CGBaseObj* self, CGBaseObj* other, int arg)
{
    typedef void (*Fn)(CGBaseObj*, CGBaseObj*, int);
    void** vtable = *reinterpret_cast<void***>(self);
    Fn fn = reinterpret_cast<Fn>(vtable[5]);
    fn(self, other, arg);
}

static inline void CallOnTalk(CGBaseObj* self, CGBaseObj* other, int arg)
{
    typedef void (*Fn)(CGBaseObj*, CGBaseObj*, int);
    void** vtable = *reinterpret_cast<void***>(self);
    Fn fn = reinterpret_cast<Fn>(vtable[6]);
    fn(self, other, arg);
}

static const float sBgDefaultGravityY = 0.0;
static bool sBgCollisionActive;
static const float  sAnimFrameOffset = 1.0f;  // FLOAT_80330338
static const double sLoopBias = 1.2;   // DOUBLE_80330378
static const float  sZeroFloat = 0.0f;  // FLOAT_80330350

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void VECNormalizeZero(Vec*, Vec*)
{
	// TODO
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::onFrame()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80081ea4
 * PAL Size: 980b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::onCreate()
{
    m_worldPosition.x = 0.0f;
    m_worldPosition.y = 0.0f;
    m_worldPosition.z = 0.0f;
    m_groundHitOffset.x = 0.0f;
    m_groundHitOffset.y = 0.0f;
    m_groundHitOffset.z = 0.0f;

    m_rotBaseX = 0.0f;
    m_rotBaseY = 0.0f;
    m_rotBaseZ = 0.0f;
    m_rotTargetX = 0.0f;
    m_rotTargetY = 0.0f;
    m_rotTargetZ = 0.0f;

    m_bodyOffset.x = 0.0f;
    m_bodyOffset.y = 0.5f;
    m_bodyOffset.z = 0.0f;
    m_jumpOffset.x = 0.0f;
    m_jumpOffset.y = 1.0f;
    m_jumpOffset.z = 0.0f;
    m_moveOffset.x = 0.0f;
    m_moveOffset.y = 1.0f;
    m_moveOffset.z = 0.0f;

    m_charaModelHandle = 0;
    m_weaponModelHandle = 0;
    m_shieldModelHandle = 0;

    m_animStateMisc = 0xFF;
    *((u8*)&m_weaponNodeFlags + 1) &= 0x7F;
    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xBF) | 0x40;
    *((u8*)&m_weaponNodeFlags + 1) &= 0xDF;

    m_moveBaseSpeed = 10.0f;
    m_currentAnimSlot = -1;
    m_animSlotSel = -1;

    m_bodyEllipsoidRadius = 2.0f;
    m_bodyEllipsoidOffset = 0.0f;
    m_bodyEllipsoidAspect = 1.0f;
    m_capsuleHalfHeight = 2.0f;

    m_attackColRadius = 3.0f;
    m_bodyColRadius = 3.5f;
    m_nearColRadius = 1.0f;
    m_bgColMask = 0;

    *((u8*)&m_weaponNodeFlags) = (*((u8*)&m_weaponNodeFlags) & 0xEF) | 0x10;
    *((u8*)&m_weaponNodeFlags) &= 0xF7;
    *((u8*)&m_weaponNodeFlags) = (*((u8*)&m_weaponNodeFlags) & 0xFB) | 4;
    *((u8*)&m_weaponNodeFlags) &= 0xFE;
    *((u8*)&m_weaponNodeFlags) = (*((u8*)&m_weaponNodeFlags) & 0xDF) | 0x20;
    *((u8*)&m_weaponNodeFlags) &= 0xBF;
    *((u8*)&m_weaponNodeFlags) &= 0x7F;

    m_objectFlags = 1;
    m_displayFlags = 3;
    m_rotationX = 1.0f;
    m_rotationY = 1.0f;
    m_rotationZ = 1.0f;
    m_attrFlags = 0;
    m_ownerType = -1;
    m_classWorkIndex = 0;
    m_scriptHandle = 0;

    unk_0x184 = 0.0f;
    unk_0x188 = 0.0f;
    m_moveVec.x = NAN;
    m_turnSpeed = 0.0f;
    m_pushParamA = 0;
    m_pushParamB = 0;

    *((u8*)&m_shieldNodeFlags) &= 0xBF;
    *((u8*)&m_shieldNodeFlags) &= 0xDF;
    *((u8*)&m_shieldNodeFlags) &= 0xEF;
    *((u8*)&m_shieldNodeFlags) &= 0x7F;
    *((u8*)&m_shieldNodeFlags) &= 0xF7;
    *((u8*)&m_shieldNodeFlags) &= 0xFB;
    *((u8*)&m_shieldNodeFlags) &= 0xFE;

    m_frontHitAngle = 3.1415927f;
    m_lookAtTarget = 0;
    m_stepSlopeLimit = 1.0f;
    m_lookAtTimer = 1.0f;
    m_animBlend = 1.0f;
    m_bgAttrValue = 1.0f;
    m_bounceFactor = 1.0f;
    m_gravityY = 0.0f;
    m_jumpLandingDampening = 0.0f;

    m_stateFlags0 &= 0xEF;
    m_stateFlags0 &= 0xF7;
    m_stateFlags0 &= 0x7F;

    m_bgCollisionQtrn.x = 0.0f;
    m_bgCollisionQtrn.y = 0.0f;
    m_bgCollisionQtrn.z = 0.0f;
    m_bgCollisionQtrn.w = 1.0f;

    m_dispItemTimer = 0;
    *reinterpret_cast<float*>(m_lastBgAttr) = 1.0f;
    m_collisionPushTimerMax = 0x32;

    m_radiusCtrl.x = 0.0f;
    m_radiusCtrl.y = 0.0f;
    m_radiusCtrl.z = 1.0f;
    m_radiusCtrlVel.x = 0.0f;
    m_radiusCtrlVel.y = m_radiusCtrl.y;
    m_radiusCtrlVel.z = m_radiusCtrl.z;
    m_groundFriction = m_radiusCtrlVel.x;

    m_moveAnimState = 0;
    m_moveAnimSubState = 0;
    m_randSeedLo = 0;
    m_randSeedHi = 0;
    m_ownerSlot = 0;
    m_moveMode = 0;
    m_moveModePrevious = 4;

    m_hitNormal.x = -1.0f;
    m_hitNormal.y = 0.0f;
    m_hitNormal.z = 0.0f;
    m_bgDownDist = 9.0f;
    m_groundSlide = 0.0f;
    m_worldParam = 0.0f;
    m_worldParamA = 0.0f;
    *reinterpret_cast<float*>(m_worldMode) = 0.0f;

    m_lookAtTargetNodeIndex = -1;
    m_lookAtAccumYaw = 0.0f;
    m_lookAtAccumPitch = 0.0f;
    m_weaponAttachNode = -1;
    m_shieldAttachNodeIndex = -1;
    m_lastMapIdHit = 0;
    m_lastMapIdExtra = 0;
    m_extraMoveVec.x = 0.0f;
    m_extraMoveVec.y = 0.0f;
    m_extraMoveVec.z = 0.0f;

    for (int i = 0; i < 4; i++) {
        m_animQueue[i] = -1;
    }
    m_animQueueFlags = 0xFF;
    m_animQueuePos = 0xFF;

    memset(&m_attackColliders[0].m_localStart.y, 0, 0x180);
    memset(&m_damageColliders[0].m_localPosition.y, 0, 0x140);
    memset(m_dropItemCodes, 0, sizeof(m_dropItemCodes));
}

/*
 * --INFO--
 * PAL Address: 0x80081dd8
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::onDestroy()
{
    if (m_charaModelHandle != (CCharaPcs::CHandle*)0) {
        PartMng.pppDeleteCHandle(m_charaModelHandle);
    }

    if (m_weaponModelHandle != (CCharaPcs::CHandle*)0) {
        PartMng.pppDeleteCHandle(m_weaponModelHandle);
    }

    if (m_shieldModelHandle != (CCharaPcs::CHandle*)0) {
        PartMng.pppDeleteCHandle(m_shieldModelHandle);
    }

    if (m_charaModelHandle != (CCharaPcs::CHandle*)0) {
        delete m_charaModelHandle;
        m_charaModelHandle = (CCharaPcs::CHandle*)0;
    }

    if (m_weaponModelHandle != (CCharaPcs::CHandle*)0) {
        delete m_weaponModelHandle;
        m_weaponModelHandle = (CCharaPcs::CHandle*)0;
    }

    if (m_shieldModelHandle != (CCharaPcs::CHandle*)0) {
        delete m_shieldModelHandle;
        m_shieldModelHandle = (CCharaPcs::CHandle*)0;
    }

    m_scriptHandle = (void**)0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::move()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80080d04
 * PAL Size: 1556b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::objectCollision()
{
    bool keepPushTimer = false;
    Vec selfBasePos;
    Vec selfCapsuleOffset;
    Vec selfCapsulePos;

    PSVECAdd(&m_worldPosition, &m_groundHitOffset, &selfBasePos);
    selfCapsuleOffset.x = m_bodyEllipsoidOffset * -sinf(m_rotBaseY);
    selfCapsuleOffset.y = sZeroFloat;
    selfCapsuleOffset.z = m_bodyEllipsoidOffset * -cosf(m_rotBaseY);
    PSVECAdd(&selfBasePos, &selfCapsuleOffset, &selfCapsulePos);

    if ((m_bgColMask & 0x10000) != 0) {
        for (CGQuadObj* quad = FindGQuadObjFirst__13CFlatRuntime2Fv(CFlat); quad != 0;
            quad = FindGQuadObjNext__13CFlatRuntime2FP9CGQuadObj(CFlat, quad)) {
            if (quad->isInner(&selfBasePos)) {
                CallOnPush(quad, this, 0);
            }
        }
    }

    for (CGObject* other = FindGObjNext__13CFlatRuntime2FP8CGObject(CFlat, this); other != 0;
         other = FindGObjNext__13CFlatRuntime2FP8CGObject(CFlat, other)) {
        if (((m_bgColMask & 0xE) == 0) || ((other->m_bgColMask & 0xE) == 0)) {
            continue;
        }

        Vec otherBasePos;
        Vec otherCapsuleOffset;
        Vec otherCapsulePos;
        PSVECAdd(&other->m_worldPosition, &other->m_groundHitOffset, &otherBasePos);
        otherCapsuleOffset.x = other->m_bodyEllipsoidOffset * -sinf(other->m_rotBaseY);
        otherCapsuleOffset.y = sZeroFloat;
        otherCapsuleOffset.z = other->m_bodyEllipsoidOffset * -cosf(other->m_rotBaseY);
        PSVECAdd(&otherBasePos, &otherCapsuleOffset, &otherCapsulePos);

        const double capsuleDistance = PSVECDistance(&selfCapsulePos, &otherCapsulePos);
        if ((capsuleDistance == static_cast<double>(sZeroFloat))
            || (capsuleDistance > static_cast<double>(m_nearColRadius + other->m_nearColRadius))) {
            continue;
        }

        if (((m_bgColMask & 8) != 0) && ((other->m_bgColMask & 8) != 0)) {
            const bool thisAttack = (m_objectFlags & 2) != 0;
            const bool otherDamage = (other->m_objectFlags & 0xC) != 0;
            const bool thisDamage = (m_objectFlags & 0xC) != 0;
            const bool otherAttack = (other->m_objectFlags & 2) != 0;
            const bool allowAttachA = ((m_weaponNodeFlags & 1) == 0) || (m_attachOwner != other);
            const bool allowAttachB = ((other->m_weaponNodeFlags & 1) == 0) || (other->m_attachOwner != this);

            if (((thisAttack && otherDamage) || (thisDamage && otherAttack))
                && allowAttachA
                && allowAttachB
                && (capsuleDistance < static_cast<double>(m_attackColRadius + other->m_attackColRadius))) {
                CGObject* frontObj = thisAttack ? this : other;
                CGObject* hitObj = thisAttack ? other : this;
                Vec dir;
                PSVECSubtract(&hitObj->m_worldPosition, &frontObj->m_worldPosition, &dir);
                const float hitRot = atan2f(dir.x, dir.z);
                const float rotDelta = Math.DstRot(frontObj->m_rotBaseY, hitRot);

                if (fabsf(rotDelta) < frontObj->m_frontHitAngle) {
                    CallOnTalk(frontObj, hitObj, 1);
                    CallOnTalk(hitObj, frontObj, 0);
                }
            }
        }

        if (((m_bgColMask & 4) != 0) && ((other->m_bgColMask & 4) != 0)
            && (capsuleDistance < static_cast<double>(m_bodyColRadius + other->m_bodyColRadius))) {
            CallOnPush(this, other, 1);
            CallOnPush(other, this, 0);
        }

        if (((m_bgColMask & 2) != 0) && ((other->m_bgColMask & 2) != 0)
            && (sZeroFloat < m_bodyEllipsoidRadius)
            && (sZeroFloat < other->m_bodyEllipsoidRadius)) {
            const bool allowAttachA = ((m_weaponNodeFlags & 1) == 0) || (m_attachOwner != other);
            const bool allowAttachB = ((other->m_weaponNodeFlags & 1) == 0) || (other->m_attachOwner != this);

            if (allowAttachA && allowAttachB) {
                const bool usePushTimers = ((m_objectFlags & 0x40) != 0) && ((other->m_objectFlags & 0x40) != 0);
                const double bodyDistanceLimit = static_cast<double>(m_bodyEllipsoidRadius + other->m_bodyEllipsoidRadius);

                if (capsuleDistance < bodyDistanceLimit) {
                    if (usePushTimers
                        && ((m_groundHitOffset.x != sZeroFloat) || (m_groundHitOffset.z != sZeroFloat)
                            || (other->m_groundHitOffset.x != sZeroFloat) || (other->m_groundHitOffset.z != sZeroFloat))) {
                        keepPushTimer = true;
                    }

                    if (!usePushTimers || (m_collisionPushTimerMax != 0) || (other->m_collisionPushTimerMax == 0)) {
                        const float thisPush = static_cast<float>(m_pushParamA + m_pushParamB);
                        const float otherPush = static_cast<float>(other->m_pushParamA + other->m_pushParamB);
                        float split = 0.5f + (thisPush - otherPush) / 510.0f;
                        if (split < sZeroFloat) {
                            split = sZeroFloat;
                        }
                        if (split > sAnimFrameOffset) {
                            split = sAnimFrameOffset;
                        }

                        Vec delta;
                        Vec scaledDelta;
                        PSVECSubtract(&selfCapsulePos, &otherCapsulePos, &delta);
                        PSVECScale(&delta, &delta, static_cast<float>((bodyDistanceLimit - capsuleDistance) / bodyDistanceLimit));
                        PSVECScale(&delta, &scaledDelta, sAnimFrameOffset - split);
                        PSVECAdd(&selfCapsulePos, &scaledDelta, &selfCapsulePos);
                        PSVECScale(&delta, &scaledDelta, -split);
                        PSVECAdd(&otherCapsulePos, &scaledDelta, &otherCapsulePos);
                    }
                }
            }
        }

        PSVECSubtract(&otherCapsulePos, &other->m_worldPosition, &other->m_groundHitOffset);
        PSVECSubtract(&other->m_groundHitOffset, &otherCapsuleOffset, &other->m_groundHitOffset);
    }

    if (keepPushTimer) {
        if (m_collisionPushTimerMax > 0) {
            --m_collisionPushTimerMax;
        }
    } else {
        m_collisionPushTimerMax = 0x32;
    }

    PSVECSubtract(&selfCapsulePos, &m_worldPosition, &m_groundHitOffset);
    PSVECSubtract(&m_groundHitOffset, &selfCapsuleOffset, &m_groundHitOffset);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::bgCollision()
{
    m_stateFlags0 &= ~0x80;
    m_stateFlags0 &= ~0x40;

    m_radiusCtrl.x = 0.0f;
    m_gravityY = sBgDefaultGravityY;

    bgAttribCollision();

    if (m_bgColMask & 0x01)
    {
        sBgCollisionActive = true;

        if (Game.game.m_currentMapId == 0x21)
        {
            bgWorldCollision();
        }
        else
        {
            bgNormalCollision();
        }

        sBgCollisionActive = false;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800806d4
 * PAL Size: 1428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::bgNormalCollision()
{
    if (fabs(static_cast<double>(m_groundHitOffset.x)) < DOUBLE_80330400) {
        m_groundHitOffset.x = sZeroFloat;
    }
    if (fabs(static_cast<double>(m_groundHitOffset.y)) < DOUBLE_80330400) {
        m_groundHitOffset.y = sZeroFloat;
    }
    if (fabs(static_cast<double>(m_groundHitOffset.z)) < DOUBLE_80330400) {
        m_groundHitOffset.z = sZeroFloat;
    }

    if ((m_groundHitOffset.x == sZeroFloat) && (m_groundHitOffset.y == sZeroFloat) && (m_groundHitOffset.z == sZeroFloat)) {
        return;
    }

    Vec move = m_groundHitOffset;
    move.y = sZeroFloat;
    Vec pos = m_worldPosition;
    pos.y += FLOAT_80330360 + m_capsuleHalfHeight;
    const u32 hitMask = *reinterpret_cast<u32*>(&m_moveVec.x);

    int retry = 4;
    while (retry != 0) {
        CMapCylinder bodyCylinder;
        bodyCylinder.m_bottom = pos;
        bodyCylinder.m_direction = move;
        bodyCylinder.m_radius = FLOAT_8033033c;
        bodyCylinder.m_height = FLOAT_8033033c;
        bodyCylinder.m_top = move;
        bodyCylinder.m_direction2.x = FLOAT_80330340;
        bodyCylinder.m_direction2.y = FLOAT_80330340;
        bodyCylinder.m_direction2.z = FLOAT_80330340;
        bodyCylinder.m_radius2 = m_capsuleHalfHeight;
        bodyCylinder.m_height2 = 0.0f;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &bodyCylinder, &move, hitMask) == 0) {
            break;
        }

        m_stateFlags0 = (m_stateFlags0 & 0xBF) | 0x40;
        CalcHitSlide__7CMapObjFP3Vecf(*reinterpret_cast<void**>(reinterpret_cast<u8*>(&MapMng) + 0x22A88), &move);

        if (fabs(static_cast<double>(move.x)) < DOUBLE_80330400) {
            move.x = sZeroFloat;
        }
        if (fabs(static_cast<double>(move.y)) < DOUBLE_80330400) {
            move.y = sZeroFloat;
        }
        if (fabs(static_cast<double>(move.z)) < DOUBLE_80330400) {
            move.z = sZeroFloat;
        }

        --retry;
    }

    if (retry == 0) {
        m_groundHitOffset.x = sZeroFloat;
        m_groundHitOffset.y = sZeroFloat;
        m_groundHitOffset.z = sZeroFloat;
        return;
    }

    PSVECAdd(&pos, &move, &pos);
    move.x = sZeroFloat;
    move.y = m_groundHitOffset.y - FLOAT_80330360;
    move.z = sZeroFloat;

    CMapCylinder stepCylinder;
    stepCylinder.m_bottom = pos;
    stepCylinder.m_direction.x = sZeroFloat;
    stepCylinder.m_direction.y = move.y;
    stepCylinder.m_direction.z = sZeroFloat;
    stepCylinder.m_radius = FLOAT_8033033c;
    stepCylinder.m_height = FLOAT_8033033c;
    stepCylinder.m_top = stepCylinder.m_direction;
    stepCylinder.m_direction2.x = FLOAT_80330340;
    stepCylinder.m_direction2.y = FLOAT_80330340;
    stepCylinder.m_direction2.z = FLOAT_80330340;
    stepCylinder.m_radius2 = m_capsuleHalfHeight;
    stepCylinder.m_height2 = 0.0f;

    if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &stepCylinder, &move, hitMask) == 0) {
        pos.y -= m_capsuleHalfHeight;
        PSVECAdd(&pos, &move, &pos);
        PSVECSubtract(&pos, &m_worldPosition, &m_groundHitOffset);
        return;
    }

    const unsigned char mapGroup = DAT_8032ec90[0x47];
    u8* mapGroupData = reinterpret_cast<u8*>(&MapMng) + 0x214E8 + (mapGroup * 0x14);
    if ((*reinterpret_cast<u32*>(mapGroupData) & 0x20) == 0) {
        m_stateFlags0 = (m_stateFlags0 & 0x7F) | 0x80;
        m_radiusCtrl.x = *reinterpret_cast<float*>(mapGroupData);
        if (mapGroup != 0) {
            m_lastBgGroup = static_cast<short>(mapGroup);
        }
        GetHitFaceNormal__7CMapObjFP3Vec(
            *reinterpret_cast<void**>(reinterpret_cast<u8*>(&MapMng) + 0x22A88),
            reinterpret_cast<Vec*>(&m_hitNormal.y));
    }

    if (CalcHitSlide__7CMapObjFP3Vecf(*reinterpret_cast<void**>(reinterpret_cast<u8*>(&MapMng) + 0x22A88), &move) != 0) {
        CMapCylinder hitCylinder;
        hitCylinder.m_bottom = pos;
        hitCylinder.m_direction = move;
        hitCylinder.m_radius = FLOAT_8033033c;
        hitCylinder.m_height = FLOAT_8033033c;
        hitCylinder.m_top = move;
        hitCylinder.m_direction2.x = FLOAT_80330340;
        hitCylinder.m_direction2.y = FLOAT_80330340;
        hitCylinder.m_direction2.z = FLOAT_80330340;
        hitCylinder.m_radius2 = m_capsuleHalfHeight;
        hitCylinder.m_height2 = 0.0f;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &hitCylinder, &move, hitMask) != 0) {
            Vec hitPos;
            CalcHitPosition__7CMapObjFP3Vec(*reinterpret_cast<void**>(reinterpret_cast<u8*>(&MapMng) + 0x22A88), &hitPos);
            PSVECSubtract(&hitPos, &pos, &move);
        }
    }

    pos.y -= m_capsuleHalfHeight;
    PSVECAdd(&pos, &move, &pos);

    if ((m_jumpLandingDampening <= sZeroFloat) || (FLOAT_8033041c <= m_groundHitOffset.y)) {
        m_groundHitOffset.x = pos.x - m_worldPosition.x;
        m_groundHitOffset.y = pos.y - m_worldPosition.y;
        m_groundHitOffset.z = pos.z - m_worldPosition.z;
        return;
    }

    float oldY = m_groundHitOffset.y;
    if (oldY < FLOAT_80330420) {
        oldY = FLOAT_80330420;
    }

    float clampedY = m_groundHitOffset.y;
    if (clampedY < FLOAT_80330420) {
        clampedY = FLOAT_80330420;
    }

    m_worldPosition.y = pos.y;
    m_groundHitOffset.x = pos.x - m_worldPosition.x;
    m_groundHitOffset.y = sZeroFloat;
    m_groundHitOffset.z = pos.z - m_worldPosition.z;
    m_gravityY = m_jumpLandingDampening * -((clampedY - (oldY - move.y)) + (oldY - move.y));

    if (((m_displayFlags & 1) != 0) && ((m_weaponNodeFlags & 1) == 0)) {
        PlaySe3D__6CSoundFiP3Vecffi(
            &Sound,
            0x26,
            &m_worldPosition,
            FLOAT_80330424 + (FLOAT_80330424 * m_gravityY) / FLOAT_80330360,
            FLOAT_80330410 + (FLOAT_80330410 * m_gravityY) / FLOAT_80330360,
            0);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::bgWorldCollision()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::bgAttribCollision()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::bgShadeCollision()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::hit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::update()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::copy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::onDraw()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8007def8
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::CancelMove(int moveType)
{
    *((u8*)&m_weaponNodeFlags + 1) &= 0xDF;

    CFlatRuntime::CStack arg;
    arg.m_word = static_cast<u32>(moveType);
    SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
        CFlat, this, 2, 7, 1, &arg, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::Move(Vec*, float, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::MoveVector(Vec*, float, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::moveVector(Vec*, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::moveVectorH(Vec*, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::moveVectorRot(float, float, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::moveVectorHRot(float, float, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::CCClass(int, int, float, Vec*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::CCClassRot(int, int, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::Attach(CGObject*, char*, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::Detach()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::DispCharaParts(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetAttackCol(int, char*, float, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetDamageCol(int, char*, float, float, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::boundCheck()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::Turn(float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::HitParticle(int, int, int, int, Vec*, PPPIFPARAM*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetClassWork(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetTexAnim(char*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8007cdb4
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::LookAt(CGObject* target, char* nodeName)
{
    short nodeIndex;

    m_lookAtTarget = target;
    if (nodeName == 0) {
        nodeIndex = -1;
    } else {
        nodeIndex = SearchNode__Q26CChara6CModelFPc(m_charaModelHandle->m_model, nodeName);
    }
    m_lookAtTargetNodeIndex = nodeIndex;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::InitWork(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::LoadModel(int, unsigned long, unsigned long, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::LoadWeapon(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::LoadShield(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::LoadAnim(char*, int, int, int, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8007ca30
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::FreeAnim(int animSlot)
{
    m_charaModelHandle->FreeAnim(animSlot);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CGObject::IsLoopAnim(int mode)
{
    // m_charaModelHandle is treated as an array; element 0x5A holds an animation controller.
    CCharaPcs::CHandle* handles = m_charaModelHandle;

    bool hasAnimCtrl = false;

    if (handles != nullptr) // && handles[0x5A] != nullptr
    {
        hasAnimCtrl = true;
    }

    if (!hasAnimCtrl || m_currentAnimSlot == -1)
    {
        return 1;
    }
	
    if (mode) // handles->m_someFlag == 0 // TODO
    {
        return 1;
    }

    const float span = *(float*)handles; // sAnimFrameOffset + (anim->m_endFrame - anim->m_startFrame); // TODO

    if (span == sAnimFrameOffset)
    {
        return 1;
    }

    float base;
	
    if (mode == 0)
    {
        base = *(float*)handles; // TODO
    }
    else
    {
        base = m_turnSpeed;
    }

    double threshold = static_cast<double>(base);

    // mode == 2 adds the 1.2 bias
    if (mode == 2)
    {
        threshold = static_cast<double>(static_cast<float>(threshold + sLoopBias));
    }

	// TODO: Retype float?
    const float lastAttr = *reinterpret_cast<const float*>(m_lastBgAttr);

    if (static_cast<double>(lastAttr) < static_cast<double>(sZeroFloat))
    {
        return (threshold <= static_cast<double>(sZeroFloat)) ? 1 : 0;
    }
    else
    {
        const double diff = static_cast<double>(span - sAnimFrameOffset);
        return (diff < threshold) ? 1 : 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::IsAnimFinished(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8007c7b8
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::CancelAnim(int keepFacing)
{
	m_currentAnimSlot = -1;

	u8 flags = *((u8*)&m_shieldNodeFlags);
	flags &= 0xbf;
	*((u8*)&m_shieldNodeFlags) = flags;

	m_turnSpeed = sZeroFloat;

	if (keepFacing != 0)
	{
		m_rotTargetY = m_rotBaseY;
	}

	flags = *((u8*)&m_shieldNodeFlags);
	flags &= 0xf7;
	*((u8*)&m_shieldNodeFlags) = flags;

	flags = *((u8*)&m_shieldNodeFlags);
	flags &= 0x7f;
	*((u8*)&m_shieldNodeFlags) = flags;
}

/*
 * --INFO--
 * PAL Address: 0x8007c700
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::PlayAnim(int slot, int param2, int param3, int param4, int param5, signed char* animData)
{
	m_currentAnimSlot = m_animQueue[slot - 0x41];
	
	// Set weapon node flag bit 0
	*((u8*)&m_weaponNodeFlags + 1) = (param2 & 1) | (*((u8*)&m_weaponNodeFlags + 1) & 0xfe);
	
	m_animExtraIndex = param4;
	m_collisionPushTimer = param5;
	
	// Set shield node flag bit 1
	*((u8*)&m_shieldNodeFlags) = ((param3 << 1) & 2) | (*((u8*)&m_shieldNodeFlags) & 0xfd);
	
	if (animData == NULL) {
		*((u8*)&m_shieldNodeFlags) &= 0x7f; // Clear bit 7
	} else {
		*((u8*)&m_shieldNodeFlags) = (*((u8*)&m_shieldNodeFlags) & 0x7f) | 0x80; // Set bit 7
		m_animQueuePos = 0;
		// Copy 4 bytes manually
		*((u32*)m_animQueue) = *((u32*)animData);
	}
	
	*((u8*)&m_shieldNodeFlags) = (*((u8*)&m_shieldNodeFlags) & 0xf7) | 8; // Set bit 3
	m_turnSpeed = sZeroFloat;
}

/*
 * --INFO--
 * PAL Address: 0x8007c6e4
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::SetDispItemName(int showName)
{
    *((u8*)&m_shieldNodeFlags) = (((showName << 4) & 0x10) | (*((u8*)&m_shieldNodeFlags) & 0xEF));
    m_dispItemTimer = 13;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::DrawDebug(CFont*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8007c3bc
 * PAL Size: 672b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::SetPosBG(Vec* position, int useCapsuleOffset)
{
    m_worldPosition = *position;

    if (((m_weaponNodeFlags & 0x10) != 0) && (Game.game.m_currentMapId != 0x21)) {
        CMapCylinder bodyCylinder;
        bodyCylinder.m_bottom = m_worldPosition;
        bodyCylinder.m_bottom.y += useCapsuleOffset != 0 ? m_capsuleHalfHeight : 0.5f;
        bodyCylinder.m_direction.x = sZeroFloat;
        bodyCylinder.m_direction.y = -1.0f;
        bodyCylinder.m_direction.z = sZeroFloat;
        bodyCylinder.m_radius = 0.3f;
        bodyCylinder.m_height = 0.3f;
        bodyCylinder.m_top = bodyCylinder.m_direction;
        bodyCylinder.m_direction2.x = 0.3f;
        bodyCylinder.m_direction2.y = 0.6f;
        bodyCylinder.m_direction2.z = 0.6f;
        bodyCylinder.m_radius2 = 0.6f;
        bodyCylinder.m_height2 = 0.0f;

        u32 hitMask = *reinterpret_cast<u32*>(&m_moveVec.x);
        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &bodyCylinder, &bodyCylinder.m_direction, hitMask) != 0) {
            CalcHitPosition__7CMapObjFP3Vec(*reinterpret_cast<void**>(reinterpret_cast<u8*>(&MapMng) + 0x22A88), &m_worldPosition);
        }

        if ((m_charaModelHandle != 0) && (m_charaModelHandle->m_model != 0)) {
            CMapCylinder attrCylinder;
            attrCylinder.m_bottom.x = m_worldPosition.x;
            attrCylinder.m_bottom.y = m_worldPosition.y + 1.0f;
            attrCylinder.m_bottom.z = m_worldPosition.z;
            attrCylinder.m_direction.x = sZeroFloat;
            attrCylinder.m_direction.y = -0.5f;
            attrCylinder.m_direction.z = sZeroFloat;
            attrCylinder.m_radius = 0.3f;
            attrCylinder.m_height = 0.3f;
            attrCylinder.m_top = attrCylinder.m_direction;
            attrCylinder.m_direction2.x = 0.3f;
            attrCylinder.m_direction2.y = 0.6f;
            attrCylinder.m_direction2.z = 0.6f;
            attrCylinder.m_radius2 = 0.0f;
            attrCylinder.m_height2 = 0.0f;

            if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &attrCylinder, &attrCylinder.m_direction, 0x78000000) == 0) {
                m_bgAttrValue = sAnimFrameOffset;
            } else {
                u8* hitObj = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(&MapMng) + 0x22A88);
                if (hitObj != 0) {
                    switch (hitObj[0x47]) {
                    case 0x28:
                        m_bgAttrValue = 0.5f;
                        break;
                    case 0x29:
                        m_bgAttrValue = 0.75f;
                        break;
                    case 0x2A:
                        m_bgAttrValue = 0.25f;
                        break;
                    case 0x2B:
                        m_bgAttrValue = sZeroFloat;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        m_animBlend = m_bgAttrValue;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007c37c
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::ResetDynamics()
{
    if ((m_charaModelHandle != 0) && (m_charaModelHandle->m_model != 0)) {
        u8* modelBytes = reinterpret_cast<u8*>(m_charaModelHandle->m_model);
        modelBytes[0x10C] = (modelBytes[0x10C] & 0x7F) | 0x80;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007c278
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::CalcSphereNearPos(float scale, float angleOffset, Vec& outPos)
{
    Vec up;
    Vec normal;
    Vec tangent;
    Vec bitangent;
    Vec offset;
    Mtx rotationMtx;

    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;

    PSVECNormalize(&m_worldPosition, &normal);
    PSVECCrossProduct(&normal, &up, &bitangent);
    PSVECNormalize(&bitangent, &bitangent);
    PSVECCrossProduct(&normal, &bitangent, &tangent);
    PSVECNormalize(&tangent, &tangent);
    PSMTXRotAxisRad(rotationMtx, &normal, m_rotBaseY + angleOffset);
    PSMTXMultVec(rotationMtx, &tangent, &tangent);
    PSVECScale(&tangent, &offset, scale);
    PSVECAdd(&m_worldPosition, &offset, &outPos);
}

/*
 * --INFO--
 * PAL Address: 0x8007c230
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::ResetAnimPoint(int slot)
{
    if ((m_charaModelHandle == 0) || (m_charaModelHandle->m_model == 0)) {
        return;
    }

    if (m_charaModelHandle->m_animSlot[slot] == 0) {
        return;
    }

    *reinterpret_cast<u16*>(reinterpret_cast<u8*>(m_charaModelHandle->m_animSlot[slot]) + 0x2C) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8007c1c4
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::AddAnimPoint(int slot, int pointType, int pointFrame)
{
    if ((m_charaModelHandle == 0) || (m_charaModelHandle->m_model == 0)) {
        return;
    }

    CRef* animRef = m_charaModelHandle->m_animSlot[slot];
    if (animRef == 0) {
        return;
    }

    u8* animRefBytes = reinterpret_cast<u8*>(animRef);
    u16 count = *reinterpret_cast<u16*>(animRefBytes + 0x2C);
    *reinterpret_cast<u16*>(animRefBytes + 0x2E + count * 4) = static_cast<u16>(pointFrame);
    *reinterpret_cast<u16*>(animRefBytes + 0x30 + count) = static_cast<u16>(pointType);
    *reinterpret_cast<u16*>(animRefBytes + 0x2C) = static_cast<u16>(count + 1);
}

/*
 * --INFO--
 * PAL Address: 0x8007c1b8
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::SetAnimSlot(int slot, int anim)
{
    m_animQueue[anim - 0x41] = static_cast<char>(slot);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::CalcSafePos(int, CGObject*, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::PutDropItem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CGObject::IsDispRader()
{ 
	return m_displayFlags & 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::onHit(int, CGObject*, int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::onAnimPoint(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::onAlphaUpdate()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::onHitParticle(int, int, int, int, Vec*, PPPIFPARAM*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::onDrawDebug(CFont*, float, float&, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGObject::GetCID()
{
	return 0;
}

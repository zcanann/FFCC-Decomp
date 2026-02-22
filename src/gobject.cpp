#include "ffcc/gobject.h"

#include "ffcc/math.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/quadobj.h"

#include <math.h>

extern CPartMng PartMng;
extern CMath Math;
extern unsigned char CFlat[];
extern "C" CGObject* FindGObjNext__13CFlatRuntime2FP8CGObject(void*, CGObject*);
extern "C" CGQuadObj* FindGQuadObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGQuadObj* FindGQuadObjNext__13CFlatRuntime2FP9CGQuadObj(void*, CGQuadObj*);

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
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::onCreate()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::bgNormalCollision()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::CancelMove(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::LookAt(CGObject*, char*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::FreeAnim(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::CancelAnim(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetDispItemName(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetPosBG(Vec*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::ResetDynamics()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::CalcSphereNearPos(float, float, Vec&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::ResetAnimPoint(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::AddAnimPoint(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetAnimSlot(int, int)
{
	// TODO
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

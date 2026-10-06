#include "ffcc/ptrarray.h"
#include "ffcc/gobject.h"

#include "ffcc/cflat_runtime.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/color.h"
#include "ffcc/charaobj.h"
#include "ffcc/gobjwork.h"
#include "ffcc/game.h"
#include "ffcc/graphic.h"
#include "ffcc/itemobj.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_map.h"
#include "ffcc/p_minigame.h"
#include "ffcc/pad.h"
#include "ffcc/partMng.h"
#include "ffcc/quadobj.h"
#include "ffcc/sound.h"
#include "ffcc/texanim.h"
#include "ffcc/vector.h"
#include "ffcc/wind.h"

#include <dolphin/gx.h>
#include <math.h>
#include <string.h>

extern const Vec DAT_801D9B88;
extern const Vec DAT_801D9B94;

STATIC_ASSERT(offsetof(CCaravanWork, m_genderFlag) == 0x3E2);
STATIC_ASSERT(offsetof(CGObjWork, m_saveSlot) == 0x08);
STATIC_ASSERT(offsetof(CGObjWork, m_ownerObj) == 0x0C);
STATIC_ASSERT(offsetof(CChara::CModel, m_meshVisibleMask) == 0x98);
STATIC_ASSERT(offsetof(CChara::CModel, m_nodes) == 0xA8);
STATIC_ASSERT(offsetof(CChara::CModel, m_texAnimSet) == 0xD4);
STATIC_ASSERT(offsetof(CChara::CModel, m_flags10CBits) == 0x10C);
STATIC_ASSERT(sizeof(CChara::CNode) == 0xC0);
STATIC_ASSERT(offsetof(CChara::CNode, m_mtx) == 0x6C);
STATIC_ASSERT(offsetof(CGCharaObj, m_itemId) == 0x560);
STATIC_ASSERT(offsetof(CCameraPcs, m_yaw) == 0xF8);

STATIC_ASSERT(sizeof(CGObject::AttackCol) == 0x30);
STATIC_ASSERT(sizeof(CGObject::DamageCol) == 0x28);
STATIC_ASSERT(offsetof(CGObject::AttackCol, m_hitMask) == 0x2C);
STATIC_ASSERT(offsetof(CGObject::DamageCol, m_hitMask) == 0x24);
STATIC_ASSERT(offsetof(CGObject, m_turnAnimFrames) == 0x1DC);
STATIC_ASSERT(offsetof(CGObject, m_attackColliders) == 0x1E0);
STATIC_ASSERT(offsetof(CGObject, m_damageColliders) == 0x360);
STATIC_ASSERT(offsetof(CGObject, m_turnSpeed) == 0x4A0);
STATIC_ASSERT(offsetof(CGObject, m_motionMode) == 0x98);
STATIC_ASSERT(offsetof(CGObject, m_lastBgGroup) == 0xE8);
STATIC_ASSERT(offsetof(CGObject, m_bgGroupMask) == 0x4CC);
STATIC_ASSERT(offsetof(CGObject, m_swayTarget) == 0x4D0);
STATIC_ASSERT(offsetof(CGObject, m_swayDirection) == 0x4DC);
STATIC_ASSERT(offsetof(CGObject, m_turnFactor) == 0x4E8);
STATIC_ASSERT(offsetof(CGObject, m_hitFaceNormal) == 0x4EC);
STATIC_ASSERT(offsetof(CGObject, m_twistTarget) == 0x4FC);
STATIC_ASSERT(offsetof(CGObject, m_animSlots) == 0x9D);
STATIC_ASSERT(offsetof(CGObject, m_animQueuePos) == 0xDD);
STATIC_ASSERT(offsetof(CGObject, m_charaModelHandle) == 0xF8);
STATIC_ASSERT(offsetof(CGObject, m_weaponNodeFlags) == 0x9A);
STATIC_ASSERT(offsetof(CGObject, m_weaponNodeFlagBits) == 0x9A);
STATIC_ASSERT(offsetof(CGObject, m_weaponNodeFlagBytes) == 0x9A);
STATIC_ASSERT(sizeof(CGObject::WeaponNodeFlagBits) == 1);
STATIC_ASSERT(sizeof(CGObject::WeaponNodeFlagBytes) == 2);

static inline Mtx& FlatPosMtx()
{
    return Chara.FlatPosMtx();
}

static inline void CallOnPush(CGBaseObj* self, CGBaseObj* other, int arg)
{
    self->onPush(other, arg);
}

static inline void CallOnTalk(CGBaseObj* self, CGBaseObj* other, int arg)
{
    self->onTalk(other, arg);
}

static inline bool HasLoadedModel(CCharaPcs::CHandle* handle)
{
    return handle != 0 && handle->m_model != 0;
}


static inline float GObjSqrtf(float x)
{
    union {
        float f;
        unsigned long bits;
    } bits;
    int fpclass;

    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        x = (float)(x * guess);
        return x;
    }

    if ((double)x < 0.0) {
        x = NAN;
        return x;
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
        x = NAN;
    }

    return x;
}

static inline float ClampFloat(float value, float minValue, float maxValue)
{
    if (value < minValue) {
        return minValue;
    }
    if (maxValue < value) {
        return maxValue;
    }
    return value;
}

static inline float WrapAnimFrame(float value, float span)
{
    if (value < 0.0f) {
        return (span - 1.0f) - fmodf(-value, span);
    }
    return fmodf(value, span);
}

inline void CMapPcs::CalcHitPosition(Vec* hitPosition)
{
    MapMng.m_hitMapObj->CalcHitPosition(hitPosition);
}

inline int CMapPcs::CheckHitCylinderNear(Vec* cylinderBottom, Vec* direction, float radius, unsigned long hitMask)
{
    CMapCylinder cylinder;

    cylinder.m_bottom = *cylinderBottom;
    cylinder.m_axis = *direction;
    cylinder.m_radius = radius;

    return MapMng.CheckHitCylinderNear(&cylinder, direction, hitMask);
}

inline void CMapPcs::GetHitFaceNormal(Vec* normal)
{
    MapMng.m_hitMapObj->GetHitFaceNormal(normal);
}

inline int CMapPcs::CalcHitSlide(Vec* move, float scale)
{
    return MapMng.m_hitMapObj->CalcHitSlide(move, scale);
}

inline int CMapPcs::GetHitGrpNo()
{
    return gMapHitFace->m_groupIndex;
}

inline unsigned long CMapPcs::GetHitGrpBit()
{
    return MapMng.GetMapIdGrpArray()[gMapHitFace->m_groupIndex].m_mask;
}

namespace std {
float atan2(float y, float x);
}

inline float std::atan2(float y, float x)
{
    return (float)::atan2((double)y, (double)x);
}

inline void VECLerp(Vec* a, Vec* b, Vec* out, float t)
{
    Vec scaledA;
    Vec scaledB;

    PSVECScale(a, &scaledA, 1.0f - t);
    PSVECScale(b, &scaledB, t);
    PSVECAdd(&scaledA, &scaledB, out);
}

static const char s_gobject_cpp[] = "gobject.cpp";
static const char s_noTurnMotion[36] =
    "\203\136\201\133\203\223\203\202\201\133\203\126\203\207\203\223"
    "\202\315\202\240\202\350\202\334\202\271\202\361\201\102\012";

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGObject::GetCID()
{
	return 5;
}

/*
 * --INFO--
 * PAL Address: 0x8007be50
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::onAnimPoint(int, int)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x8007BE54
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGObject::onHit(int, CGObject*, int, Vec*)
{
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8007be5c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::onHitParticle(int, int, int, int, Vec*, PPPIFPARAM*)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x8007be60
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::onDrawDebug(CFont*, float, float&, float)
{
    return;
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
unsigned int CGObject::IsDispRader()
{ 
	return m_displayFlags & 1;
}

/*
 * --INFO--
 * PAL Address: 0x8007be74
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::PutDropItem()
{
    s32 dropCount = 0;

    for (int i = 0; i < 4; i++) {
        s16 rawDropCode = m_dropItemCodes[i];
        if (rawDropCode > 0) {
            s32 dropCode = rawDropCode;
            int createMode;
            if ((dropCode & 0xC000) == 0x4000) {
                dropCode &= ~0xC000;
                createMode = 2;
            } else {
                createMode = 0;
            }

            CGItemObj::CreateFromScript(createMode, 4, dropCode, this, 1.5707964f * (float)dropCount, 0);
            dropCount++;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007bf34
 * PAL Size: 644b
 * EN Address: 0x8007B8E8
 * EN Size: 644b
 * JP Address: TODO
 * JP Size: TODO
 */
float CGObject::CalcSafePos(int hitMask, CGObject* other, Vec* outSafePos)
{
    Vec centerPos;
    Vec hitMove;
    float safeDistance = 0.0f;

    centerPos.x = other->m_worldPosition.x;
    if (other->m_worldPosition.y > m_worldPosition.y) {
        centerPos.y = other->m_worldPosition.y;
    } else {
        centerPos.y = m_worldPosition.y;
    }
    centerPos.y += m_capsuleHalfHeight;
    centerPos.z = other->m_worldPosition.z;

    PSVECSubtract(&m_worldPosition, &centerPos, &hitMove);
    hitMove.y = 0.0f;

    const float hitRadius = m_capsuleHalfHeight;
    CMapCylinder hitCylinder;
    hitCylinder.m_bottom = centerPos;
    hitCylinder.m_axis.x = hitMove.x;
    hitCylinder.m_axis.y = 0.0f;
    hitCylinder.m_axis.z = hitMove.z;
    hitCylinder.m_radius = hitRadius;

    if (MapMng.CheckHitCylinderNear(&hitCylinder, &hitMove, hitMask) != 0) {
        MapMng.m_hitMapObj->CalcHitPosition(&centerPos);
        centerPos.y -= m_capsuleHalfHeight;
        *outSafePos = centerPos;
        safeDistance = PSVECDistance(&m_worldPosition, &centerPos);
    } else {
        *outSafePos = m_worldPosition;
        hitMove.x = (m_capsuleHalfHeight + other->m_capsuleHalfHeight) * (float)sin((double)other->m_rotBaseY);
        hitMove.y = 0.0f;
        hitMove.z = (m_capsuleHalfHeight + other->m_capsuleHalfHeight) * (float)cos((double)other->m_rotBaseY);
        const float safeRadius = m_capsuleHalfHeight;

        CMapCylinder safeCylinder;
        safeCylinder.m_bottom = centerPos;
        safeCylinder.m_axis = hitMove;
        safeCylinder.m_radius = safeRadius;

        if (MapMng.CheckHitCylinderNear(&safeCylinder, &hitMove, hitMask) != 0) {
            MapMng.m_hitMapObj->CalcHitPosition(&centerPos);
            safeDistance = (m_capsuleHalfHeight + other->m_capsuleHalfHeight) -
                           PSVECDistance(&m_worldPosition, &centerPos);
        }
    }

    return safeDistance;
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
    m_animSlots[anim] = static_cast<char>(slot);
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
void CGObject::AddAnimPoint(int slot, int pointFrame, int pointType)
{
    bool hasModel = false;
    CCharaPcs::CHandle* handle = m_charaModelHandle;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (!hasModel) {
        return;
    }

    CCharaPcs::CLoadAnim* animRef = handle->m_animSlot[slot];
    if (animRef == 0) {
        return;
    }

    animRef->m_points[animRef->m_pointCount].m_type = pointType;
    animRef->m_points[animRef->m_pointCount].m_frame = pointFrame;
    animRef->m_pointCount++;
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
    bool hasModel = false;
    CCharaPcs::CHandle* handle = m_charaModelHandle;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (!hasModel) {
        return;
    }

    if (handle->m_animSlot[slot] == 0) {
        return;
    }

    handle->m_animSlot[slot]->m_pointCount = 0;
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
    Vec bitangent;
    Vec tangent;
    Vec normal;
    Vec up;
    Vec offset;
    Mtx rotationMtx;

    *reinterpret_cast<int*>(&up.x) = *reinterpret_cast<const int*>(&DAT_801D9B94.x);
    *reinterpret_cast<int*>(&up.y) = *reinterpret_cast<const int*>(&DAT_801D9B94.y);
    *reinterpret_cast<int*>(&up.z) = *reinterpret_cast<const int*>(&DAT_801D9B94.z);

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
 * PAL Address: 0x8007c37c
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::ResetDynamics()
{
    bool hasModel = false;
    CCharaPcs::CHandle* handle = m_charaModelHandle;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (hasModel) {
        handle->m_model->m_flags10CBits.m_flag10C_80 = true;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGObject::bgShadeCollision()
{
    if (!HasLoadedModel(m_charaModelHandle)) {
        return;
    }

    if (MapPcs.CheckHitCylinderNear(CVector(m_worldPosition.x, 5.0f + m_worldPosition.y, m_worldPosition.z),
            CVector(0.0f, -10000.0f, 0.0f), 0.0f, 0x78000000) != 0) {
        switch (MapPcs.GetHitGrpNo() - 0x28) {
        case 0:
            m_bgAttrValue = 0.75f;
            break;
        case 1:
            m_bgAttrValue = 0.5f;
            break;
        case 2:
            m_bgAttrValue = 0.25f;
            break;
        case 3:
            m_bgAttrValue = 0.0f;
            break;
        }
    } else {
        m_bgAttrValue = 1.0f;
    }
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

    if (m_weaponNodeFlagBits.m_unk10 && (Game.m_currentMapId != 0x21)) {
        Vec bottom = m_worldPosition;
        bottom.y = (useCapsuleOffset != 0 ? m_capsuleHalfHeight : 1000.0f) + bottom.y;
        Vec direction = bottom;
        direction.x = 0.0f;
        direction.z = 0.0f;
        direction.y = -2000.0f;

        if (MapPcs.CheckHitCylinderNear(&bottom, &direction, 0.0f, m_bgHitMask) != 0) {
            MapPcs.CalcHitPosition(&m_worldPosition);
        }

        bgShadeCollision();
        m_animBlend = m_bgAttrValue;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007c65c
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::DrawDebug(CFont* font)
{
    if (m_weaponNodeFlagBits.m_unk20 && (0.0f < m_screenDepth)) {
        float invDepth = 1.0f / m_screenDepth;
        float xProd = 224.0f * m_projection.z;
        float yProd = 320.0f * m_projection.y;
        float screenX[2];
        screenX[0] = -(xProd * invDepth - 224.0f);

        onDrawDebug(font,
                    yProd * invDepth + 320.0f,
                    screenX[0],
                    m_projection.w * invDepth);
    }
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
    m_shieldNodeFlagBits.m_bit10 = showName;
    m_dispItemTimer = 13;
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
    m_currentAnimSlot = m_animSlots[slot];

    m_weaponNodeFlagAll.m_bits1.m_bit01 = static_cast<signed char>(param2);

    m_animExtraIndex = static_cast<short>(param4);
    m_collisionPushTimer = static_cast<short>(param5);

    signed char shieldFlag = static_cast<signed char>(param3);
    m_shieldNodeFlagBits.m_bit02 = shieldFlag;

    if (animData != 0) {
        m_shieldNodeFlagBits.m_bit80 = 1;
        m_animQueuePos = '\0';
        memcpy(m_animQueue, animData, 4);
    } else {
        m_shieldNodeFlagBits.m_bit80 = 0;
    }

    m_shieldNodeFlagBits.m_bit08 = 1;
    m_turnSpeed = 0.0f;
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
    m_shieldNodeFlagBits.m_bit40 = 0;
    m_turnSpeed = 0.0f;

    if (keepFacing != 0) {
        m_rotTargetY = m_rotBaseY;
    }

    m_shieldNodeFlagBits.m_bit08 = 0;
    m_shieldNodeFlagBits.m_bit80 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8007C950
 * PAL Size: 224b
 * EN Address: 0x8007C2FC
 * EN Size: 216b
 * JP Address: 0x8007BD28
 * JP Size: 216b
 */
int CGObject::IsLoopAnim(int mode)
{
    CCharaPcs::CHandle* handle = m_charaModelHandle;
    bool hasAnimCtrl = false;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasAnimCtrl = true;
    }

    if ((!hasAnimCtrl) || (m_currentAnimSlot == -1)) {
        return 1;
    }

    CChara::CModel& model = *handle->m_model;
    if (model.m_anim != 0) {
        float span = 1.0f + (model.GetEndFrame() - model.GetStartFrame());

        if (1.0f == span) {
            return 1;
        }

        float frame;
        if (mode != 0) {
            frame = m_turnSpeed;
        } else {
            frame = model.GetNowFrame();
        }

        if (mode == 2) {
#ifdef VERSION_GCCP01
            frame += 1.2;
#else
            frame += 1.0f;
#endif
        }

        if (m_lastBgAttr < 0.0f) {
            return 0.0f >= frame;
        }

#ifdef VERSION_GCCP01
        return span - 1.0f < frame;
#else
        return span <= frame;
#endif
    }

    return 1;
}


/*
 * --INFO--
 * PAL Address: 0x8007c808
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGObject::IsAnimFinished(int mode)
{
    CCharaPcs::CHandle* handle = m_charaModelHandle;
    bool hasModel = false;
    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (!hasModel || m_currentAnimSlot == -1) {
        return 1;
    }

    return !m_shieldNodeFlagBits.m_bit08 && IsLoopAnim(mode);
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
void CGObject::LoadAnim(char* animName, int animIndex, int loopMode, int blendMode, unsigned long modelBase)
{
    m_charaModelHandle->LoadAnim(animName, animIndex, loopMode, blendMode, (int)modelBase, -1, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8007ca80
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::LoadShield(int itemId)
{
    if (m_shieldModelHandle != 0) {
        delete m_shieldModelHandle;
        m_shieldModelHandle = 0;
    }

    if (itemId > 0) {
        m_shieldModelHandle = new (Game.m_mainStage, const_cast<char*>(s_gobject_cpp), 0xA23) CCharaPcs::CHandle;
        m_shieldModelHandle->Add();

        const unsigned long textureVariant = (m_ownerType == 0)
            ? reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_genderFlag
            : 0;

        m_shieldModelHandle->LoadModel(4, static_cast<unsigned long>(itemId), 0, textureVariant, -1, 0, 1);
        m_shieldAttachNodeIndex =
            m_charaModelHandle->m_model->SearchNode("l_item2");
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007cb68
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::LoadWeapon(int itemId, int itemVariant)
{
    if (m_weaponModelHandle != 0) {
        delete m_weaponModelHandle;
        m_weaponModelHandle = 0;
    }

    if (itemId > 0) {
        m_weaponModelHandle = new (Game.m_mainStage, const_cast<char*>(s_gobject_cpp), 0xA11) CCharaPcs::CHandle;
        m_weaponModelHandle->Add();

        const unsigned long textureVariant = (m_ownerType == 0)
            ? reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_genderFlag
            : 0;

        m_weaponModelHandle->LoadModel(
            4, static_cast<unsigned long>(itemId), static_cast<unsigned long>(itemVariant), textureVariant, -1, 0, 1);
        m_weaponAttachNode =
            m_charaModelHandle->m_model->SearchNode("r_item");
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::LoadModel(int kind, unsigned long modelId, unsigned long variant, int arg3)
{
    if (m_charaModelHandle != 0) {
        delete m_charaModelHandle;
        m_charaModelHandle = 0;
    }

    m_charaModelHandle = new (Game.m_mainStage, const_cast<char*>(s_gobject_cpp), 0xA01) CCharaPcs::CHandle;
    m_charaModelHandle->Add();
    m_charaModelHandle->LoadModel(kind, modelId, variant, 0, -1, 0, arg3);
}

/*
 * --INFO--
 * PAL Address: 0x8007CD14
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::InitWork(int index)
{
    char ownerType;

    ownerType = m_ownerType;
    switch (ownerType) {
    case 0: {
        reinterpret_cast<CGObjWork*>(m_scriptHandle)->Init(
            index, &reinterpret_cast<CRomWork*>(Game.unkCFlatData0[0])[index], 0);
        break;
    }
    case 1: {
        reinterpret_cast<CGObjWork*>(m_scriptHandle)->Init(
            index, &reinterpret_cast<CRomWork*>(Game.unkCFlatData0[1])[index], 0);
        break;
    }
    }
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
    int nodeIndex;

    m_lookAtTarget = target;
    if (nodeName == 0) {
        nodeIndex = -1;
    } else {
        nodeIndex = m_charaModelHandle->m_model->SearchNode(nodeName);
    }
    m_lookAtTargetNodeIndex = nodeIndex;
}

/*
 * --INFO--
 * PAL Address: 0x8007CE04
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::SetTexAnim(char* name)
{
    CCharaPcs::CHandle* handle;
    bool hasModel;
    CTexAnimSet* texAnimSet;

    handle = m_charaModelHandle;
    hasModel = false;
    if ((handle != (CCharaPcs::CHandle*)0) && (handle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }

    if (hasModel) {
        texAnimSet = handle->m_model->m_texAnimSet;
        if (texAnimSet != (CTexAnimSet*)0) {
            texAnimSet->Change(name, 0.0f, (CTexAnimSet::ANIM_TYPE)-2);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007CE64
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::SetClassWork(int ownerType, int workIndex)
{
    m_ownerType = (char)ownerType;
    m_classWorkIndex = (unsigned char)workIndex;

    switch (ownerType) {
    case 0: {
        m_scriptHandle = reinterpret_cast<void**>(&Game.m_caravanWorkArr[Game.m_gameWork.m_wmBackupParams[workIndex]]);
        reinterpret_cast<CGObjWork*>(m_scriptHandle)->m_saveSlot = Game.m_gameWork.m_wmBackupParams[workIndex];
        reinterpret_cast<CGObjWork*>(m_scriptHandle)->m_ownerObj = this;
        Game.m_scriptFoodBase[workIndex] = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
        return;
    }

    case 1:
        m_scriptHandle = reinterpret_cast<void**>(&Game.m_monWorkArr[workIndex]);
        reinterpret_cast<CGObjWork*>(m_scriptHandle)->m_ownerObj = this;
        reinterpret_cast<CGObjWork*>(m_scriptHandle)->m_saveSlot = workIndex;
        Game.m_monObjects[workIndex] = this;
        Game.m_monWorkRefs[workIndex] = reinterpret_cast<CMonWork*>(m_scriptHandle);
        return;

    default:
        m_scriptHandle = 0;
        return;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::HitParticle(int effectIndex, int kind, int nodeIndex, int colliderIndex, Vec* pos, PPPIFPARAM* hitParam)
{
    CFlatRuntime::CStack stack[9];
    stack[0].m_word = effectIndex;
    stack[1].m_word = kind;
    stack[2].m_word = nodeIndex;
    stack[3].m_word = colliderIndex;
    *reinterpret_cast<float*>(&stack[4].m_word) = pos->x;
    *reinterpret_cast<float*>(&stack[5].m_word) = pos->y;
    *reinterpret_cast<float*>(&stack[6].m_word) = pos->z;
    stack[7].m_word = hitParam->m_particleIndex;
    stack[8].m_word = static_cast<int>(hitParam->m_classId);

    gCFlatRuntime().SystemCall(this, 2, 0xB, 9, stack, 0);

    onHitParticle(effectIndex, kind, nodeIndex, colliderIndex, pos, hitParam);
}

/*
 * --INFO--
 * PAL Address: 0x8007cfec
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::Turn(float targetRot, int turnFrames)
{
    m_shieldNodeFlagBits.m_bit40 = 1;
    m_rotTargetY = targetRot;
    m_turnBaseSpeed =
        Math.DstRot(m_rotBaseY, m_rotTargetY) / static_cast<float>(turnFrames);
    m_turnAnimFrames = turnFrames;

    PlayAnim((m_turnBaseSpeed < 0.0f) ? 2 : 3, 0, 0, -1, -1, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8007d0e4
 * PAL Size: 556b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::boundCheck()
{
    Vec4d clipPos;
    Vec clipCorner;
    Mtx cameraMtx;
    Mtx44 clipMtx;
    Mtx44 screenMtx;
    int clipMask;

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTXCopy(cameraMtx, clipMtx);
    clipMtx[3][2] = 0.0f;
    clipMtx[3][1] = 0.0f;
    clipMtx[3][0] = 0.0f;
    clipMtx[3][3] = 1.0f;

    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    PSMTX44Concat(screenMtx, clipMtx, screenMtx);

    if ((m_charaModelHandle != 0) && (m_charaModelHandle->m_model != 0)) {
        float clipLimit;
        float oneF;
        float zero;
        zero = 0.0f;
        oneF = 1.0f;
        clipLimit = -1.0f;

        clipMask = 0x1F;
        s32 i = 0;
        do {
            clipCorner.x = m_worldPosition.x + (((i & 1) != 0) ? -m_nearColRadius : m_nearColRadius);
            clipCorner.y = m_worldPosition.y + (((i & 4) != 0) ? -m_nearColRadius : m_nearColRadius);
            clipCorner.z = m_worldPosition.z + (((i & 2) != 0) ? -m_nearColRadius : m_nearColRadius);

            Math.MTX44MultVec4(screenMtx, &clipCorner, &clipPos);
            if (clipPos.w > zero) {
                clipMask &= 0xFFFFFFEF;
            }
            if (clipMask == 0) {
                break;
            }

            const float invW = oneF / clipPos.w;
            clipPos.x *= invW;
            clipPos.y *= invW;

            if (clipPos.x > clipLimit) {
                clipMask &= 0xFFFFFFFE;
            }
            if (clipPos.y > clipLimit) {
                clipMask &= 0xFFFFFFFD;
            }
            if (clipPos.x < oneF) {
                clipMask &= 0xFFFFFFFB;
            }
            if (clipPos.y < oneF) {
                clipMask &= 0xFFFFFFF7;
            }
        } while ((clipMask != 0) && (++i < 8));

        m_weaponNodeFlagBits.m_unk20 = clipMask == 0;
    }

    Math.MTX44MultVec4(screenMtx, &m_worldPosition, reinterpret_cast<Vec4d*>(&m_projection.y));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetDamageCol(int colliderIndex, char* nodeName, float horizontalRadius, float verticalRadius, Vec* position)
{
    CCharaPcs::CHandle* handle = m_charaModelHandle;
    bool hasModel = false;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (hasModel) {
        int nodeIndex = handle->m_model->SearchNode(nodeName);

        m_damageColliders[colliderIndex].m_nodeIndex = nodeIndex;
        m_damageColliders[colliderIndex].m_horizontalRadius = horizontalRadius;
        m_damageColliders[colliderIndex].m_verticalRadius = verticalRadius;
        m_damageColliders[colliderIndex].m_localPosition.x = position->x;
        m_damageColliders[colliderIndex].m_localPosition.y = position->y;
        m_damageColliders[colliderIndex].m_localPosition.z = position->z;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetAttackCol(int hitIndex, char* nodeName, float radius, Vec* position)
{
    CCharaPcs::CHandle* handle = m_charaModelHandle;
    bool hasModel = false;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (hasModel) {
        int nodeIndex = handle->m_model->SearchNode(nodeName);

        m_attackColliders[hitIndex].m_nodeIndex = nodeIndex;
        m_attackColliders[hitIndex].m_radius = radius;
        m_attackColliders[hitIndex].m_localPosition.x = position->x;
        m_attackColliders[hitIndex].m_localPosition.y = position->y;
        m_attackColliders[hitIndex].m_localPosition.z = position->z;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007D488
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::DispCharaParts(int showParts)
{
    CCharaPcs::CHandle* handle = m_charaModelHandle;
    bool hasModel = false;
    if (handle != 0 && handle->m_model != 0) {
        hasModel = true;
    }
    if (!hasModel) {
        return;
    }
    handle->m_model->m_meshVisibleMask = showParts;
}

/*
 * --INFO--
 * PAL Address: 0x8007d4bc
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::Detach()
{
    if (m_weaponNodeFlagBits.m_attached != 0) {
        CChara::CNode* node = &m_attachOwner->m_charaModelHandle->m_model->m_nodes[m_attachNode];

        m_worldPosition.x = node->m_mtx[0][3];
        m_worldPosition.y = node->m_mtx[1][3];
        m_worldPosition.z = node->m_mtx[2][3];
        PSVECAdd(&m_worldPosition, &m_attachOwner->m_worldPosition, &m_worldPosition);

        float rotY = m_rotBaseY + m_attachOwner->m_rotBaseY;
        m_rotTargetY = rotY;
        m_rotBaseY = rotY;
    }

    m_weaponNodeFlagBits.m_attached = false;
}

/*
 * --INFO--
 * PAL Address: 0x8007d568
 * PAL Size: 224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::Attach(CGObject* owner, char* nodeName, Vec* attachLocal)
{
    bool hasModel = false;
    CCharaPcs::CHandle* handle = owner->m_charaModelHandle;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (hasModel) {
        int nodeIndex = handle->m_model->SearchNode(nodeName);
        if (nodeIndex >= 0) {
            m_weaponNodeFlagBits.m_attached = true;

            m_attachOwner = owner;
            m_attachNode = nodeIndex;
            m_attachLocal.x = attachLocal->x;
            m_attachLocal.y = attachLocal->y;
            m_attachLocal.z = attachLocal->z;

            if ((m_worldParamA != 0x24) && (m_worldParamB != 0x125)) {
                float rotY = m_rotBaseY - owner->m_rotBaseY;
                m_rotTargetY = rotY;
                m_rotBaseY = rotY;
            }

            m_moveMode = m_moveModePrevious;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007d648
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGObject* CGObject::CCClassRot(int useBodyRadius, int classMask, float yOffset, float rotY, float distance, float radius)
{
    Vec targetPos;

    targetPos.x = distance * static_cast<float>(sin(rotY)) + m_worldPosition.x;
    targetPos.y = m_worldPosition.y + yOffset;
    targetPos.z = distance * static_cast<float>(cos(rotY)) + m_worldPosition.z;
    return CCClass(useBodyRadius, classMask, yOffset, &targetPos, radius);
}

/*
 * --INFO--
 * PAL Address: 0x8007d730
 * PAL Size: 636b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGObject* CGObject::CCClass(int useBodyRadius, int classMask, float yOffset, Vec* targetPos, float radius)
{
    Vec origin;
    Vec toTarget;
    Vec targetDir;
    Vec toOther;
    CGObject* best;

    origin.x = m_worldPosition.x;
    origin.y = m_worldPosition.y + yOffset;
    origin.z = m_worldPosition.z;

    PSVECSubtract(targetPos, &origin, &toTarget);
    const float maxDist = PSVECMag(&toTarget);
    if (0.0f == maxDist) {
        return 0;
    }

    PSVECNormalize(&toTarget, &targetDir);
    const float maxAngle = std::atan2(radius, maxDist);
    float bestDist = 10000000.0f;
    best = 0;

    for (CGObject* other = CFlat.FindGObjFirst(); other != 0;
         other = CFlat.FindGObjNext(other)) {
        if (this == other) {
            continue;
        }
        if ((other->m_attrFlags & static_cast<unsigned int>(classMask)) == 0) {
            continue;
        }
        const float otherX = other->m_worldPosition.x;
        const float otherY = other->m_worldPosition.y;
        const float otherZ = other->m_worldPosition.z;
        if (!(otherX - maxDist <= origin.x) || !(otherY - maxDist <= origin.y)
            || !(otherZ - maxDist <= origin.z) || !(otherX + maxDist >= origin.x)
            || !(otherY + maxDist >= origin.y) || !(otherZ + maxDist >= origin.z)) {
            continue;
        }

        PSVECSubtract(&other->m_worldPosition, &origin, &toOther);
        float extraAngle;
        const float dist = PSVECMag(&toOther);
        extraAngle = 0.0f;
        if ((extraAngle < dist) && (dist < maxDist)) {
            if (useBodyRadius != 0) {
                extraAngle = static_cast<float>(atan(static_cast<double>((other->m_bodyEllipsoidRadius * dist / maxDist) / dist)));
            }
            PSVECScale(&toOther, &toOther, 1.0f / dist);
            const float angle = static_cast<float>(acos(static_cast<double>(PSVECDotProduct(&toOther, &targetDir))));
            if ((static_cast<double>(angle) < static_cast<double>(maxAngle + extraAngle)) && (dist < bestDist)) {
                bestDist = dist;
                best = other;
            }
        }
    }

    CFlat.AddDebugDrawCC(&origin, &toTarget, radius, 0, 0);
    return best;
}

/*
 * --INFO--
 * PAL Address: 0x8007d9ac
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::moveVectorHRot(float rotX, float rotY, float moveTimer, int turnFrames)
{
    const float cosY0 = static_cast<float>(cos(rotY));
    const float sinX = static_cast<float>(sin(rotX));
    const float sinY = static_cast<float>(sin(rotY));
    const float cosY1 = static_cast<float>(cos(rotY));
    const float cosX = static_cast<float>(cos(rotX));

    m_weaponNodeFlagAll.m_bits1.m_bit20 = 1;
    m_weaponNodeFlagAll.m_bits1.m_bit10 = 1;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveTarget.x = sinX * cosY0;
    m_moveTarget.y = sinY;
    m_moveTarget.z = cosX * cosY1;
    m_moveTimer = moveTimer;
    m_weaponNodeFlagAll.m_bits1.m_bit08 = 0;
    m_weaponNodeFlagAll.m_bits1.m_bit02 = 0;
    m_weaponNodeFlagAll.m_bits1.m_bit04 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8007dae8
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::moveVectorRot(float rotX, float rotY, float moveTimer, int turnFrames)
{
    const float cosY0 = static_cast<float>(cos(rotY));
    const float sinX = static_cast<float>(sin(rotX));
    const float sinY = static_cast<float>(sin(rotY));
    const float cosY1 = static_cast<float>(cos(rotY));
    const float cosX = static_cast<float>(cos(rotX));

    m_weaponNodeFlagAll.m_bits1.m_bit20 = 1;
    m_weaponNodeFlagAll.m_bits1.m_bit10 = 1;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveTarget.x = sinX * cosY0;
    m_moveTarget.y = sinY;
    m_moveTarget.z = cosX * cosY1;
    m_moveTimer = moveTimer;
    m_weaponNodeFlagAll.m_bits1.m_bit08 = 1;
    m_weaponNodeFlagAll.m_bits1.m_bit02 = 0;
    m_weaponNodeFlagAll.m_bits1.m_bit04 = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8007dc24
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::moveVectorH(Vec* moveVec, float moveTimer, int turnFrames)
{
    Vec unitVec;
    const float mag = PSVECMag(moveVec);
    if (0.0f == mag) {
        unitVec.x = 0.0f;
        unitVec.y = 0.0f;
        unitVec.z = 0.0f;
    } else {
        PSVECScale(moveVec, &unitVec, 1.0f / mag);
    }

    m_weaponNodeFlagAll.m_bits1.m_bit20 = 1;
    m_weaponNodeFlagAll.m_bits1.m_bit10 = 1;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveTarget = unitVec;
    m_moveTimer = moveTimer;
    m_weaponNodeFlagAll.m_bits1.m_bit08 = 0;
    m_weaponNodeFlagAll.m_bits1.m_bit02 = 0;
    m_weaponNodeFlagAll.m_bits1.m_bit04 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8007dd14
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::moveVector(Vec* moveVec, float moveTimer, int turnFrames)
{
    Vec unitVec;
    const float mag = PSVECMag(moveVec);
    if (0.0f == mag) {
        unitVec.x = 0.0f;
        unitVec.y = 0.0f;
        unitVec.z = 0.0f;
    } else {
        PSVECScale(moveVec, &unitVec, 1.0f / mag);
    }

    m_weaponNodeFlagAll.m_bits1.m_bit20 = 1;
    m_weaponNodeFlagAll.m_bits1.m_bit10 = 1;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveTarget = unitVec;
    m_moveTimer = moveTimer;
    m_weaponNodeFlagAll.m_bits1.m_bit08 = 1;
    m_weaponNodeFlagAll.m_bits1.m_bit02 = 0;
    m_weaponNodeFlagAll.m_bits1.m_bit04 = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8007de04
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::MoveVector(Vec* moveVec, float moveTimer, int turnFrames, int useFacing, int flagA, int flagB)
{
    const signed char useFacingFlag = static_cast<signed char>(useFacing);
    const signed char flagAValue = static_cast<signed char>(flagA);
    const signed char flagBValue = static_cast<signed char>(flagB);

    m_weaponNodeFlagAll.m_bits1.m_bit20 = 1;
    m_weaponNodeFlagAll.m_bits1.m_bit10 = 1;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveTarget = *moveVec;
    m_moveTimer = moveTimer;
    m_weaponNodeFlagAll.m_bits1.m_bit08 = useFacingFlag;
    m_weaponNodeFlagAll.m_bits1.m_bit02 = flagAValue;
    m_weaponNodeFlagAll.m_bits1.m_bit04 = flagBValue;
}

/*
 * --INFO--
 * PAL Address: 0x8007de74
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::Move(Vec* moveVec, float moveTimer, int turnFrames, int moveMode, int useFacing, int flagA, int flagB)
{
    const signed char moveModeFlag = static_cast<signed char>(moveMode);
    const signed char useFacingFlag = static_cast<signed char>(useFacing);
    const signed char flagAValue = static_cast<signed char>(flagA);
    const signed char flagBValue = static_cast<signed char>(flagB);

    m_weaponNodeFlagAll.m_bits1.m_bit20 = 1;
    m_weaponNodeFlagAll.m_bits1.m_bit10 = 0;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveTarget = *moveVec;
    m_moveTimer = moveTimer;
    m_weaponNodeFlagBits.m_unk02 = moveModeFlag;
    m_weaponNodeFlagAll.m_bits1.m_bit08 = useFacingFlag;
    m_weaponNodeFlagAll.m_bits1.m_bit02 = flagAValue;
    m_weaponNodeFlagAll.m_bits1.m_bit04 = flagBValue;
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
    m_weaponNodeFlagAll.m_bits1.m_bit20 = 0;

    CFlatRuntime::CStack arg;
    arg.m_word = static_cast<u32>(moveType);
    gCFlatRuntime().SystemCall(this, 2, 7, 1, &arg, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8007df50
 * PAL Size: 1180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::onDraw()
{
    if (!m_weaponNodeFlagBits.m_unk20) {
        return;
    }

    if (!HasLoadedModel(m_charaModelHandle)) {
        return;
    }

    Mtx& posMtx = CameraPcs.CurrentCameraState().m_cameraMatrix;

    if (((CFlat.m_debugFlags & 0x1) != 0) && ((m_bgColMask & 0x1) != 0)) {
        Graphic.DrawSphere(posMtx,
                           CVector(m_worldPosition.x, m_worldPosition.y + m_capsuleHalfHeight, m_worldPosition.z),
                           m_capsuleHalfHeight, CColor(0xFF, 0x00, 0x00, 0xFF));
    }

    if (((CFlat.m_debugFlags & 0x2) != 0) && ((m_bgColMask & 0x2) != 0)) {
        CVector capsuleOffset;
        if (0.0f != m_bodyEllipsoidOffset) {
            capsuleOffset.x = m_bodyEllipsoidOffset * -sinf(m_rotBaseY);
            capsuleOffset.y = 0.0f;
            capsuleOffset.z = m_bodyEllipsoidOffset * -cosf(m_rotBaseY);
        } else {
            capsuleOffset.z = 0.0f;
            capsuleOffset.y = 0.0f;
            capsuleOffset.x = 0.0f;
        }

        Mtx scaleMtx;
        Mtx rotMtx;
        const float r = m_bodyEllipsoidRadius;
        PSMTXScale(scaleMtx, r * m_bodyEllipsoidAspect, r, r);
        PSMTXRotRad(rotMtx, 'y', m_rotBaseY);
        PSMTXConcat(rotMtx, scaleMtx, scaleMtx);

        PSVECAdd(CVector(m_worldPosition.x, m_worldPosition.y + m_bodyEllipsoidRadius, m_worldPosition.z),
                 capsuleOffset, capsuleOffset);

        scaleMtx[0][3] = capsuleOffset.x;
        scaleMtx[1][3] = capsuleOffset.y;
        scaleMtx[2][3] = capsuleOffset.z;
        PSMTXConcat(posMtx, scaleMtx, scaleMtx);
        GXLoadPosMtxImm(scaleMtx, GX_PNMTX0);

        GXSetChanMatColor(GX_COLOR0A0, CColor(0x00, 0xFF, 0x00, 0xFF).color);
        Graphic.DrawSphere();
    }

    if (((CFlat.m_debugFlags & 0x4) != 0) && ((m_bgColMask & 0x4) != 0)) {
        Graphic.DrawSphere(posMtx,
                           CVector(m_worldPosition.x, m_worldPosition.y + m_bodyColRadius, m_worldPosition.z),
                           m_bodyColRadius, CColor(0x00, 0x00, 0xFF, 0xFF));
    }

    if (((CFlat.m_debugFlags & 0x8) != 0) && ((m_bgColMask & 0x8) != 0)) {
        Graphic.DrawSphere(posMtx,
                           CVector(m_worldPosition.x, m_worldPosition.y + m_attackColRadius, m_worldPosition.z),
                           m_attackColRadius, CColor(0xFF, 0xFF, 0x00, 0xFF));
    }

    if (((CFlat.m_debugFlags & 0x10) != 0) && ((m_bgColMask & 0x10) != 0)) {
        Graphic.DrawSphere(posMtx, &m_worldPosition, m_nearColRadius, CColor(0x40, 0xFF, 0x40, 0xFF));
    }

    if (((CFlat.m_debugFlags & 0x40000) != 0) && ((m_bgColMask & 0x40000) != 0)) {
        for (int i = 0; i < 8; i++) {
            AttackCol* collider = &m_attackColliders[i];
            if (collider->m_hitMask == 0) {
                continue;
            }

            Graphic.DrawSphere(posMtx, &collider->m_worldPosition,
                               collider->m_radius,
                               CColor(0xFF, 0x80, 0x80, 0xFF));

            GXLoadPosMtxImm(posMtx, GX_PNMTX0);
            GXBegin(GX_LINES, GX_VTXFMT0, 2);
            GXPosition3f32(collider->m_previousWorldPosition.x, collider->m_previousWorldPosition.y, collider->m_previousWorldPosition.z);
            GXPosition3f32(collider->m_worldPosition.x, collider->m_worldPosition.y, collider->m_worldPosition.z);
        }
    }

    if (((CFlat.m_debugFlags & 0x80000) != 0) && ((m_bgColMask & 0x80000) != 0)) {
        for (int i = 0; i < 8; i++) {
            DamageCol* collider = &m_damageColliders[i];
            if (collider->m_hitMask == 0) {
                continue;
            }

            Graphic.DrawSphere(posMtx, &collider->m_worldPosition,
                               CVector(collider->m_horizontalRadius, collider->m_verticalRadius, collider->m_horizontalRadius),
                               CColor(0x80, 0x80, 0xFF, 0xFF));
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007e3ec
 * PAL Size: 684b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::copy()
{
    bool hasModel = false;

    if ((m_charaModelHandle != (CCharaPcs::CHandle*)0) && (m_charaModelHandle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }
    if (!hasModel) {
        return;
    }

    m_charaModelHandle->m_flags = m_displayFlags;
    m_charaModelHandle->m_colorPhase = m_animBlend;
    m_charaModelHandle->m_sortZ = m_screenDepth;
    m_charaModelHandle->m_fogBlend = m_worldParam;
    hasModel = false;

    if ((m_weaponModelHandle != (CCharaPcs::CHandle*)0) && (m_weaponModelHandle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }
    if (hasModel) {
        m_weaponModelHandle->m_flags = m_displayFlags;
        m_weaponModelHandle->m_colorPhase = m_animBlend;
        m_weaponModelHandle->m_sortZ = m_screenDepth;
        m_weaponModelHandle->m_fogBlend = m_worldParam;
    }

    hasModel = false;
    if ((m_shieldModelHandle != (CCharaPcs::CHandle*)0) && (m_shieldModelHandle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }
    if (hasModel) {
        m_shieldModelHandle->m_flags = m_displayFlags;
        m_shieldModelHandle->m_colorPhase = m_animBlend;
        m_shieldModelHandle->m_sortZ = m_screenDepth;
        m_shieldModelHandle->m_fogBlend = m_worldParam;
    }

    if (m_weaponNodeFlagBits.m_unk20 == 0) {
        m_charaModelHandle->m_flags &= 0xFFFFFFFE;
        hasModel = false;

        if ((m_weaponModelHandle != (CCharaPcs::CHandle*)0) && (m_weaponModelHandle->m_model != (CChara::CModel*)0)) {
            hasModel = true;
        }
        if (hasModel) {
            m_weaponModelHandle->m_flags &= 0xFFFFFFFE;
        }

        hasModel = false;
        if ((m_shieldModelHandle != (CCharaPcs::CHandle*)0) && (m_shieldModelHandle->m_model != (CChara::CModel*)0)) {
            hasModel = true;
        }
        if (hasModel) {
            m_shieldModelHandle->m_flags &= 0xFFFFFFFE;
        }
    }

    if (m_shieldNodeFlagBits.m_bit20 == 0) {
        m_charaModelHandle->m_flags &= 0xFFFFFFFB;
        hasModel = false;

        if ((m_weaponModelHandle != (CCharaPcs::CHandle*)0) && (m_weaponModelHandle->m_model != (CChara::CModel*)0)) {
            hasModel = true;
        }
        if (hasModel) {
            m_weaponModelHandle->m_flags &= 0xFFFFFFFB;
        }

        hasModel = false;
        if ((m_shieldModelHandle != (CCharaPcs::CHandle*)0) && (m_shieldModelHandle->m_model != (CChara::CModel*)0)) {
            hasModel = true;
        }
        if (!hasModel) {
            return;
        }

        m_shieldModelHandle->m_flags &= 0xFFFFFFFB;
        return;
    }

    m_charaModelHandle->m_bgCharmPlaneY = m_bgCharmFactor;
    m_charaModelHandle->m_worldPosY = m_worldPosition.y;
    hasModel = false;

    if ((m_weaponModelHandle != (CCharaPcs::CHandle*)0) && (m_weaponModelHandle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }
    if (hasModel) {
        m_weaponModelHandle->m_bgCharmPlaneY = m_bgCharmFactor;
        m_weaponModelHandle->m_worldPosY = m_worldPosition.y;
    }

    hasModel = false;
    if ((m_shieldModelHandle != (CCharaPcs::CHandle*)0) && (m_shieldModelHandle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }
    if (!hasModel) {
        return;
    }

    m_shieldModelHandle->m_bgCharmPlaneY = m_bgCharmFactor;
    m_shieldModelHandle->m_worldPosY = m_worldPosition.y;
}

/*
 * --INFO--
 * PAL Address: 0x8007E698
 * PAL Size: 6216b
 * EN Address: 0x8008EB64
 * EN Size: 6668b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::update()
{
    const unsigned int dbgFlags = DbgMenuPcs.GetDbgFlagsRaw();
    const int miniGameModelPass = !(dbgFlags & 0x8000);

    m_dispItemTimer = (m_dispItemTimer - 1 < 0) ? 0 : m_dispItemTimer - 1;

    if (HasLoadedModel(m_charaModelHandle)) {
        for (int i = 0; i < 8; i++) {
            AttackCol* attack = &m_attackColliders[i];
            attack->m_previousWorldPosition.x = attack->m_worldPosition.x;
            attack->m_previousWorldPosition.y = attack->m_worldPosition.y;
            attack->m_previousWorldPosition.z = attack->m_worldPosition.z;
        }
    }

    if (HasLoadedModel(m_charaModelHandle) && (m_displayFlags & 2) != 0) {
        const int forceSet = m_shieldNodeFlagBits.m_bit08 ? 1 : 0;
        const int blendMode = m_shieldNodeFlagBits.m_bit02 ? 0 : -1;
        const int endFrame = m_currentAnimSlot != -1 ? m_collisionPushTimer : -1;
        const int startFrame = m_currentAnimSlot != -1 ? m_animExtraIndex : -1;
        const int animIndex = m_currentAnimSlot != -1 ? m_currentAnimSlot : m_animSlotSel;

        if (m_charaModelHandle->SetAnim(animIndex, startFrame, endFrame, blendMode, forceSet) != 0 &&
            m_currentAnimSlot != -1) {
            m_turnSpeed = (m_lastBgAttr < 0.0f)
                ? m_charaModelHandle->m_model->GetEndFrame() - m_charaModelHandle->m_model->GetStartFrame()
                : 0.0f;
            m_charaModelHandle->m_model->SetFrame(m_turnSpeed);
        }

        m_shieldNodeFlagBits.m_bit08 = 0;
    }

    PSVECAdd(&m_worldPosition, &m_groundHitOffset, &m_worldPosition);

    float turnDelta = Math.DstRot(m_rotTargetY, m_rotBaseY);
    float turnFactor;
    if (m_animSlotSel != -1 && m_shieldNodeFlagBits.m_bit40) {
        turnDelta = (turnDelta < -fabs(m_turnBaseSpeed))
            ? -fabs(m_turnBaseSpeed)
            : ((fabs(m_turnBaseSpeed) < turnDelta) ? fabs(m_turnBaseSpeed) : turnDelta);
        turnFactor = 1.0f;
    } else {
        turnFactor = m_turnFactor;
    }
    m_rotBaseY += turnDelta * turnFactor;

    Mtx modelMtx;
    Mtx ecScratch;
    if (Game.m_currentMapId == 0x21) {
        Mtx tempMtx;

        PSMTXRotRad(modelMtx, 'y', atan2f(m_worldPosition.x, m_worldPosition.z));
        Vec mapUp = DAT_801D9B88;
        Vec worldNorm;
        PSVECNormalize(&m_worldPosition, &worldNorm);
        PSMTXRotRad(tempMtx, 'x', acosf(PSVECDotProduct(&mapUp, &worldNorm)));
        PSMTXConcat(modelMtx, tempMtx, modelMtx);

        PSMTXRotRad(tempMtx, 'y', m_rotBaseY);
        PSMTXConcat(modelMtx, tempMtx, modelMtx);
        PSMTXScaleApply(modelMtx, modelMtx, m_rotationX, m_rotationY, m_rotationZ);
        modelMtx[0][3] = m_worldPosition.x;
        modelMtx[1][3] = m_worldPosition.y;
        modelMtx[2][3] = m_worldPosition.z;
    } else {
        SRT srt;
        const float scaleInit = 1.0f;
        srt.m_position.x = srt.m_position.y = srt.m_position.z = 0.0f;
        srt.m_rotation.x = srt.m_rotation.y = srt.m_rotation.z = 0.0f;
        srt.m_scale.x = srt.m_scale.y = srt.m_scale.z = scaleInit;
        srt.m_position = m_worldPosition;
        PSVECAdd(&srt.m_position, &m_extraMoveVec, &srt.m_position);

        srt.m_rotation.x = m_rotBaseX;
        srt.m_rotation.y = m_rotBaseY;
        srt.m_rotation.z = m_rotBaseZ;
        srt.m_scale.x = m_rotationX;
        srt.m_scale.y = m_rotationY;
        srt.m_scale.z = m_rotationZ;

        if (m_worldParamA == 0x20 || m_worldParamA == 0x13 || m_worldParamA == 0x15 ||
            m_worldParamA == 0x16 || m_worldParamA == 0x17 || m_worldParamA == 0x14) {
            const float wobbleBias = m_worldParamA == 0x20 ? 0.3f : 0.05f;
            m_swayTarget.y += 0.8f * m_swayTarget.x + wobbleBias;
            m_swayTarget.x *= 0.95f;
            srt.m_rotation.y += m_swayTarget.y;
        } else if (m_worldParamA == 0x24 || m_worldParamB == 0x125) {
            const float cameraYaw = CameraPcs.m_yaw;
            srt.m_rotation.y = 3.1415927f - cameraYaw;
            srt.m_rotation.y += 0.5f * cosf(0.5f * m_swayTarget.x);
            srt.m_position.y += 1.0f + sinf(m_swayTarget.x);
            m_swayTarget.x += 0.1f;
        }

        Math.SRTToMatrix(modelMtx, &srt);

        Mtx rotScratch;
        if (m_stateFlags0Bits.unk3) {
            Mtx tiltMtx;
            if (m_groundHitOffset.x || m_groundHitOffset.z) {
                Vec axis;
                const float slideMagSq =
                    m_groundHitOffset.x * m_groundHitOffset.x + m_groundHitOffset.z * m_groundHitOffset.z;
                const float slideMag = GObjSqrtf(slideMagSq);
                PSVECCrossProduct(&m_groundHitOffset, CVector(0.0f, 1.0f, 0.0f), &axis);
                PSMTXRotAxisRad(rotScratch, &axis, -slideMag / 3.0f);
                PSMTXQuat(tiltMtx, &m_bgCollisionQtrn);
                PSMTXConcat(rotScratch, tiltMtx, tiltMtx);
                C_QUATMtx(&m_bgCollisionQtrn, tiltMtx);
            } else {
                PSMTXQuat(tiltMtx, &m_bgCollisionQtrn);
            }

            const float tx = modelMtx[0][3];
            const float ty = modelMtx[1][3];
            const float tz = modelMtx[2][3];
            modelMtx[0][3] = CVector(0.0f, 0.0f, 0.0f).x;
            modelMtx[1][3] = CVector(0.0f, 0.0f, 0.0f).y;
            modelMtx[2][3] = CVector(0.0f, 0.0f, 0.0f).z;
            PSMTXConcat(tiltMtx, modelMtx, modelMtx);
            modelMtx[0][3] = tx;
            modelMtx[1][3] = ty;
            modelMtx[2][3] = tz;
        } else if ((m_objectFlags & 0x90) != 0 && m_stateFlags0Bits.unk0) {
            if (m_groundHitOffset.x || m_groundHitOffset.z) {
                m_swayTarget.x += 0.2f * m_groundHitOffset.x;
                m_swayTarget.z += 0.2f * m_groundHitOffset.z;
            }

            const float swayDx = m_swayTarget.z - m_swayDirection.z;
            const float swayDz = m_swayTarget.x - m_swayDirection.x;
            const float swayMag = GObjSqrtf(swayDz * swayDz + swayDx * swayDx);
            m_swayDirection.x += 0.5f * swayDz;
            m_swayDirection.z += 0.5f * swayDx;

            float mtx0;
            float mtx1;
            float mtx2;
            Vec swayDir;
            PSVECNormalize(&m_swayDirection, &swayDir);
            const float swayDot = PSVECDotProduct(&swayDir, CVector(0.0f, 1.0f, 0.0f));
            if (swayDot < 0.9999f) {
                const float negSwayAngle = -acosf(swayDot);
                Vec swayAxis;
                PSVECCrossProduct(&swayDir, CVector(0.0f, 1.0f, 0.0f), &swayAxis);
                PSMTXRotAxisRad(rotScratch, &swayAxis, negSwayAngle);

                mtx0 = modelMtx[0][3];
                mtx1 = modelMtx[1][3];
                mtx2 = modelMtx[2][3];
                modelMtx[0][3] = CVector(0.0f, 0.0f, 0.0f).x;
                modelMtx[1][3] = CVector(0.0f, 0.0f, 0.0f).y;
                modelMtx[2][3] = CVector(0.0f, 0.0f, 0.0f).z;
                PSMTXConcat(rotScratch, modelMtx, modelMtx);
                const float swayTan = tan(negSwayAngle);
                const float swayTanScaled = 2.0f * swayTan;
                modelMtx[0][3] = mtx0;
                modelMtx[2][3] = mtx2;
                mtx1 -= swayTanScaled;
                modelMtx[1][3] = mtx1;
            }

            const float swayRy = m_swayTarget.x;
            const float swayRx = m_swayTarget.z;
            float swayClamp = swayDot < 1.0f ? swayDot : 1.0f;
            swayClamp = swayClamp < 0.0f ? 0.0f : swayClamp;
            const float swaySin = sinf(swayClamp);
            const float swayCos = cosf(swayClamp);
            m_swayTarget.x = swayCos * swayRy - swaySin * swayRx;
            m_swayTarget.z = swaySin * swayRy + swayCos * swayRx;
            m_swayTarget.x *= 0.9f;
            m_swayTarget.z *= 0.9f;
        }
    }

    if (m_weaponNodeFlagBits.m_attached) {
        CChara::CModel* ownerModel = m_attachOwner->m_charaModelHandle->m_model;
        PSMTXCopy(ownerModel->m_nodes[m_attachNode].m_mtx, modelMtx);

        if (m_worldParamA == 0x24 || m_worldParamB == 0x125) {
            PSMTXRotRad(ecScratch, 'y', -m_attachOwner->m_rotBaseY);
            PSMTXConcat(modelMtx, ecScratch, modelMtx);
        }
        if (m_worldParamA != 0x24 || m_worldParamB == 0x125) {
            PSMTXRotRad(ecScratch, 'y', m_rotBaseY);
            PSMTXConcat(modelMtx, ecScratch, modelMtx);
        }

        Vec ownerPos = m_attachOwner->m_worldPosition;
        PSVECAdd(&ownerPos, &m_attachOwner->m_extraMoveVec, &ownerPos);
        PSMTXTransApply(modelMtx, modelMtx, ownerPos.x, ownerPos.y, ownerPos.z);

        Vec attachPos;
        attachPos.x = modelMtx[0][3];
        attachPos.y = modelMtx[1][3];
        attachPos.z = modelMtx[2][3];

        if (m_moveMode == 0 || m_moveModePrevious == 0) {
            m_worldPosition = attachPos;
        } else {
            VECLerp(&attachPos, &m_worldPosition, &m_worldPosition,
                    static_cast<float>(m_moveMode) / static_cast<float>(m_moveModePrevious));
            m_moveMode--;
        }

        modelMtx[0][3] = m_worldPosition.x;
        modelMtx[1][3] = m_worldPosition.y;
        modelMtx[2][3] = m_worldPosition.z;
    }

    if (HasLoadedModel(m_charaModelHandle)) {
        m_animBlend += ClampFloat(m_bgAttrValue - m_animBlend, -0.05f, 0.05f);

        float lookYaw = m_lookAtAccumYaw;
        float lookPitch = m_lookAtAccumPitch;
        if (m_lookAtTarget != 0) {
            Vec lookDelta;
            PSVECSubtract(&m_worldPosition, &m_lookAtTarget->m_worldPosition, &lookDelta);

            float targetNodeY;
            if (m_lookAtTargetNodeIndex == -1) {
                targetNodeY = m_lookAtTarget->unk_0x184;
            } else {
                targetNodeY = m_lookAtTarget->m_charaModelHandle->m_model->GetNode(m_lookAtTargetNodeIndex)->GetWorldMatrix()[1][3];
            }
            lookDelta.y += unk_0x184 - targetNodeY;

            const float lookDistance = PSVECMag(&lookDelta);
            if (0.0f != lookDistance) {
                const float targetYaw = atan2f(-lookDelta.x, -lookDelta.z);
                const float yawDelta = Math.DstRot(targetYaw, m_rotBaseY);
                if (fabs(yawDelta) < 1.5707964f) {
                    const float pitchDelta = (float)atan2(lookDelta.y, lookDistance);
                    if (fabs(pitchDelta) < 0.7853982f) {
                        lookYaw += yawDelta;
                        lookPitch += pitchDelta;
                    }
                }
            }
        }

        const unsigned char lookBlendByte = m_field_0x56;
        CChara::CModel* chestModel = m_charaModelHandle->m_model;
        float lookBlend = 0.001f * static_cast<float>(lookBlendByte);
        float currentYaw = chestModel->m_chestTilt;
        float currentPitch = chestModel->m_chestAmp;
        currentYaw = lookBlend * (lookYaw - currentYaw) + currentYaw;
        currentPitch = lookBlend * (lookPitch - currentPitch) + currentPitch;
        chestModel->m_chestTilt = currentYaw;
        chestModel->m_chestAmp = currentPitch;
        CChara::CModel* twistModel = m_charaModelHandle->m_model;
        const float twistAngle = twistModel->m_twistAngle;
        twistModel->m_twistAngle = 0.25f * (m_twistTarget - twistAngle) + twistAngle;

        m_charaModelHandle->m_model->SetMatrix(modelMtx);

        Vec windVec;
        Wind.Calc(&windVec, &m_worldPosition, 0);
        windVec.x = -(m_groundHitOffset.x * Math.RandF() - windVec.x);
        windVec.z = -(m_groundHitOffset.z * Math.RandF() - windVec.z);
        m_charaModelHandle->m_model->SetDynaVector(&windVec);

        boundCheck();

        float visibleScale = 1.0f;
        if (Game.m_currentMapId == 0x21) {
            visibleScale = m_screenDepth > 10000.0f ? 0.0f : 1.0f;
        } else {
            visibleScale = m_screenDepth > 750.0f ? 0.0f : 1.0f;
        }

        const float alphaTarget = m_alphaTarget * onAlphaUpdate();
        const float alphaDelta = alphaTarget * visibleScale - m_currentAlpha;
        m_currentAlpha += (alphaDelta < -m_alphaStep) ? -m_alphaStep : ((m_alphaStep < alphaDelta) ? m_alphaStep : alphaDelta);
        m_currentAlpha = (m_currentAlpha < 0.0f) ? 0.0f : ((1.0f < m_currentAlpha) ? 1.0f : m_currentAlpha);
        m_worldParam = (m_worldParam - 0.05f < 0.0f) ? 0.0f : m_worldParam - 0.05f;
        if ((m_displayFlags & 0x1000) != 0) {
            m_currentAlpha = alphaTarget;
        }

        if (0.0f == m_currentAlpha) {
            m_weaponNodeFlagBits.m_unk20 = 0;
        }
        m_weaponNodeFlagBits.m_unk40 |= m_weaponNodeFlagBits.m_unk20;

        if ((m_displayFlags & 1) != 0) {
            if ((m_weaponNodeFlagBits.m_unk20 &&
                 miniGameModelPass == 0) ||
                m_currentAnimSlot != -1 || m_animSlotSel != m_animSlots[0]) {
                m_charaModelHandle->m_model->CalcMatrix();
            }
            if (m_weaponNodeFlagBits.m_unk20 &&
                miniGameModelPass == 0) {
                m_charaModelHandle->m_model->CalcSkin();
            }

            m_charaModelHandle->m_model->m_lightAlpha = m_currentAlpha;
            m_charaModelHandle->m_model->m_flagsA0Bits.m_flagA0_20 =
                m_weaponNodeFlagBits.m_unk20;
            m_charaModelHandle->m_model->m_flagsA0Bits.m_flagA0_80 = (m_displayFlags & 0x20) != 0;
        }

        m_charaModelHandle->m_model->CalcFurColor();

        if ((m_displayFlags & 2) != 0) {
            float frameStep;
            if (m_animSlotSel != -1 && m_shieldNodeFlagBits.m_bit40) {
                float turnRate;
                if (m_charaModelHandle->m_model->m_anim != 0) {
                    const unsigned short frameCount = m_charaModelHandle->m_model->m_anim->m_frameCount;
                    turnRate = static_cast<float>(frameCount) / static_cast<float>(m_turnAnimFrames);
                } else {
                    if (static_cast<unsigned int>(System.m_execParam) >= 2) {
                        System.Printf(const_cast<char*>(s_noTurnMotion));
                    }
                    turnRate = 1.0f;
                }
                frameStep = m_turnSpeed + turnRate;
            } else {
                float frameDelta = m_lastBgAttr;
                const int activeAnimIndex = m_charaModelHandle->m_currentAnimIndex;
                if (activeAnimIndex >= 0 &&
                    (m_charaModelHandle->m_animSlot[activeAnimIndex]->m_playbackFlags &
                     0x4) != 0) {
                    frameDelta = frameDelta < 0.0f ? -1.0f : 1.0f;
                }
                frameDelta *= 1.2f;
                frameStep = m_turnSpeed + frameDelta;
            }

            const float prevTime = m_charaModelHandle->m_model->GetNowFrame();
            m_charaModelHandle->m_model->SetFrame(frameStep);

            const int activeAnimIndex = m_charaModelHandle->m_currentAnimIndex;
            if (activeAnimIndex >= 0 && m_charaModelHandle->m_animSlot[activeAnimIndex] != 0) {
                CCharaPcs::CLoadAnim* animRef = m_charaModelHandle->m_animSlot[activeAnimIndex];
                const unsigned short pointCount = animRef->m_pointCount;
                if (pointCount > 0) {
                    const float animSpan =
                        1.0f + (m_charaModelHandle->m_model->GetEndFrame() - m_charaModelHandle->m_model->GetStartFrame());
                    float prevWrapped = WrapAnimFrame(prevTime, animSpan);
                    float nextWrapped = WrapAnimFrame(frameStep, animSpan);
                    if (frameStep < prevTime) {
                        prevWrapped = (animSpan - 1.0f) - prevWrapped;
                        nextWrapped = (animSpan - 1.0f) - nextWrapped;
                    }

                    for (int i = 0; i < animRef->m_pointCount; i++) {
                        const unsigned short pointFrame = animRef->m_points[i].m_frame;
                        const float eventFrame = static_cast<float>(pointFrame) + m_charaModelHandle->m_model->m_animStart;
                        if (prevWrapped < eventFrame && (eventFrame <= nextWrapped || nextWrapped < prevWrapped)) {
                            CFlatRuntime::CStack stackIn[2];
                            stackIn[0].m_word = static_cast<unsigned int>(m_animSlotSel);
                            stackIn[1].m_word = static_cast<unsigned int>(animRef->m_points[i].m_type);
                            gCFlatRuntime().SystemCall(this, 2, 9, 2, stackIn, 0);
                            onAnimPoint(m_animSlotSel, animRef->m_points[i].m_type);
                        }
                    }
                }
            }

            m_turnSpeed = frameStep;
        }

        if (m_currentAnimSlot != -1 && !m_weaponNodeFlagAll.m_bits1.m_bit01) {
            if (IsLoopAnim(0)) {
                if (m_shieldNodeFlagBits.m_bit80) {
                    const char queuedAnim = m_animQueue[m_animQueuePos++];
                    if (queuedAnim != -1) {
                        m_currentAnimSlot = m_animSlots[queuedAnim];
                        m_weaponNodeFlagAll.m_bits1.m_bit01 = 0;
                        m_animExtraIndex = -1;
                        m_collisionPushTimer = -1;
                        m_shieldNodeFlagBits.m_bit02 = 0;
                        m_shieldNodeFlagBits.m_bit80 = 0;
                        m_shieldNodeFlagBits.m_bit08 = 1;
                        m_turnSpeed = 0.0f;
                    } else {
                        m_currentAnimSlot = -1;
                        m_shieldNodeFlagBits.m_bit40 = 0;
                        m_turnSpeed = 0.0f;
                        m_rotTargetY = m_rotBaseY;
                        m_shieldNodeFlagBits.m_bit08 = 0;
                        m_shieldNodeFlagBits.m_bit80 = 0;
                        gCFlatRuntime().SystemCall(this, 2, 10, 0, 0, 0);
                    }
                } else {
                    m_currentAnimSlot = -1;
                    m_shieldNodeFlagBits.m_bit40 = 0;
                    m_turnSpeed = 0.0f;
                    m_rotTargetY = m_rotBaseY;
                    m_shieldNodeFlagBits.m_bit08 = 0;
                    m_shieldNodeFlagBits.m_bit80 = 0;
                    gCFlatRuntime().SystemCall(this, 2, 10, 0, 0, 0);
                }
            }
        }

        if (HasLoadedModel(m_weaponModelHandle) && (m_displayFlags & 1) != 0 && m_weaponAttachNode >= 0) {
            PSMTXCopy(m_charaModelHandle->m_model->m_nodes[m_weaponAttachNode].m_mtx, modelMtx);
            PSMTXTransApply(modelMtx, ecScratch, m_worldPosition.x, m_worldPosition.y, m_worldPosition.z);
            m_weaponModelHandle->m_model->SetMatrix(ecScratch);
            m_weaponModelHandle->m_model->CalcMatrix();
            if (m_weaponNodeFlagBits.m_unk20) {
                m_weaponModelHandle->m_model->CalcSkin();
            }

            m_weaponModelHandle->m_model->m_lightAlpha = m_currentAlpha;
            m_weaponModelHandle->m_model->m_flagsA0Bits.m_flagA0_20 =
                m_weaponNodeFlagBits.m_unk20;
            m_weaponModelHandle->m_model->m_flagsA0Bits.m_flagA0_80 = (m_displayFlags & 0x20) != 0;
        }

        if (HasLoadedModel(m_shieldModelHandle) && (m_displayFlags & 1) != 0 && m_shieldAttachNodeIndex >= 0) {
            PSMTXCopy(m_charaModelHandle->m_model->m_nodes[m_shieldAttachNodeIndex].m_mtx, modelMtx);
            PSMTXTransApply(modelMtx, ecScratch, m_worldPosition.x, m_worldPosition.y, m_worldPosition.z);
            m_shieldModelHandle->m_model->SetMatrix(ecScratch);
            m_shieldModelHandle->m_model->CalcMatrix();

            m_shieldModelHandle->m_model->m_lightAlpha = m_currentAlpha;
            m_shieldModelHandle->m_model->m_flagsA0Bits.m_flagA0_20 =
                m_weaponNodeFlagBits.m_unk20;
            m_shieldModelHandle->m_model->m_flagsA0Bits.m_flagA0_80 = (m_displayFlags & 0x20) != 0;
            if (m_weaponNodeFlagBits.m_unk20) {
                m_shieldModelHandle->m_model->CalcSkin();
            }
        }
    }
    m_groundHitOffset.x *= m_moveOffset.x;
    m_groundHitOffset.y *= m_moveOffset.y;
    m_groundHitOffset.z *= m_moveOffset.z;
    if (fabs(m_groundHitOffset.x) < 0.001f) {
        m_groundHitOffset.x = 0.0f;
    }
    if (fabs(m_groundHitOffset.y) < 0.001f) {
        m_groundHitOffset.y = 0.0f;
    }
    if (fabs(m_groundHitOffset.z) < 0.001f) {
        m_groundHitOffset.z = 0.0f;
    }

    if (m_stateFlags0Bits.unk0) {
        m_groundHitOffset.x *= m_bounceFactor;
        m_groundHitOffset.z *= m_bounceFactor;
    }

    if (HasLoadedModel(m_charaModelHandle) && CFlat.m_gameFlagBits.m_flagBit1
        && m_charaModelHandle->m_model->m_flagsA0Bits.m_flagA0_40) {
        m_charaModelHandle->m_model->MogFurFrame(this);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007fee0
 * PAL Size: 740b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::hit()
{
    const bool hasModel =
        (m_charaModelHandle != (CCharaPcs::CHandle*)0) &&
        (m_charaModelHandle->m_model != (CChara::CModel*)0);
    if (!hasModel) {
        return;
    }
    for (int i = 0; i < 8; i++) {
        const int node = m_attackColliders[i].m_nodeIndex;
        CChara::CNode* const modelNodes = m_charaModelHandle->m_model->m_nodes;
        PSMTXMultVec(modelNodes[node].m_mtx,
                     &m_attackColliders[i].m_localPosition,
                     &m_attackColliders[i].m_worldPosition);
        PSVECAdd(&m_attackColliders[i].m_worldPosition, &m_worldPosition,
                 &m_attackColliders[i].m_worldPosition);
    }

    for (int i = 0; i < 8; i++) {
        const int node = m_damageColliders[i].m_nodeIndex;
        CChara::CNode* const modelNodes = m_charaModelHandle->m_model->m_nodes;
        PSMTXMultVec(modelNodes[node].m_mtx,
                     &m_damageColliders[i].m_localPosition,
                     &m_damageColliders[i].m_worldPosition);
        PSVECAdd(&m_damageColliders[i].m_worldPosition, &m_worldPosition,
                 &m_damageColliders[i].m_worldPosition);
    }

    if ((m_bgColMask & 0x40000) == 0) {
        return;
    }

    for (CGObject* other = CFlat.FindGObjFirst(); other != 0;
         other = CFlat.FindGObjNext(other)) {
        if (((other->m_bgColMask & 0x80000) == 0) || (this == other)) {
            continue;
        }

        Vec delta;
        PSVECSubtract(&m_worldPosition, &other->m_worldPosition, &delta);
        const float distSq = PSVECDotProduct(&delta, &delta);
        const float nearRadius = m_nearColRadius + other->m_nearColRadius;
        if ((nearRadius * nearRadius) < distSq) {
            continue;
        }

        const float zero = 0.0f;

        AttackCol* attackCur = m_attackColliders;
        for (int attackIndex = 0; attackIndex < 8; attackIndex++, attackCur++) {
            if (zero == attackCur->m_radius) {
                continue;
            }

            DamageCol* damageCur = other->m_damageColliders;
            for (int damageIndex = 0; damageIndex < 8; damageIndex++, damageCur++) {
                if (((attackCur->m_hitMask & damageCur->m_hitMask) == 0) ||
                    (0.0f == damageCur->m_horizontalRadius) ||
                    (0.0f == damageCur->m_verticalRadius)) {
                    continue;
                }

                Vec hitPos;
                Vec attackVec;
                PSVECSubtract(&attackCur->m_worldPosition,
                              &attackCur->m_previousWorldPosition, &attackVec);
                if (Math.CrossCheckEllipseCapsule(
                        &hitPos, 0, &attackCur->m_previousWorldPosition, &attackVec, attackCur->m_radius,
                        &damageCur->m_worldPosition, damageCur->m_horizontalRadius, damageCur->m_verticalRadius) == 0) {
                    continue;
                }

                if ((static_cast<unsigned short>(GetCID()) & 0x2D) == 0x2D) {
                    CFlatRuntime::CStack stackIn[7];
                    stackIn[0].m_word = static_cast<u32>(attackIndex);
                    stackIn[1].m_word = static_cast<u32>(other->m_particleId);
                    stackIn[2].m_word = static_cast<u32>(damageIndex);
                    stackIn[3].m_float = hitPos.x;
                    stackIn[4].m_float = hitPos.y;
                    stackIn[5].m_float = hitPos.z;
                    stackIn[6].m_word = static_cast<CGCharaObj*>(this)->m_itemId;
                    CFlatRuntime::CStack stackOut;
                    gCFlatRuntime().SystemCall(this, 2, 0x13, 7, stackIn, &stackOut);
                    const int hitResult = onHit(attackIndex, other, damageIndex, &hitPos);
                    if (hitResult == 1) {
                        goto nextObject;
                    }
                    if (hitResult == 2) {
                        return;
                    }
                }
            }
        }
nextObject:;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800801c4
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::bgAttribCollision()
{
    if (!HasLoadedModel(m_charaModelHandle)) {
        return;
    }

    m_shieldNodeFlagBits.m_bit20 = 0;

    if ((m_displayFlags & 4) != 0) {
        if (MapPcs.CheckHitCylinderNear(CVector(m_worldPosition.x, 100.0f + m_worldPosition.y, m_worldPosition.z),
                CVector(0.0f, -10000.0f, 0.0f), 0.0f, 0x80000000) != 0) {
            Vec hitPos;
            MapPcs.CalcHitPosition(&hitPos);
            m_bgCharmFactor = m_worldPosition.y - hitPos.y;
            m_shieldNodeFlagBits.m_bit20 = 1;
        }
    }

    if (m_weaponNodeFlagBits.m_attached) {
        m_bgAttrValue = m_attachOwner->m_bgAttrValue;
        return;
    }

    if ((0.0f != m_groundHitOffset.x) || (0.0f != m_groundHitOffset.z)) {
        bgShadeCollision();
    }
}

/*
 * --INFO--
 * PAL Address: 0x800804a4
 * PAL Size: 560b
 * EN Address: 0x8007FE40
 * EN Size: 560b
 * JP Address: TODO
 * JP Size: TODO
 */

void CGObject::bgWorldCollision()
{
    CVector radial = CVector(m_worldPosition) + CVector(m_groundHitOffset);

    if (PSVECMag(radial) > 0.0f) {
        radial.Normalize();
    }
    PSVECScale(radial, radial, 1000.0f);

    CVector hitMove = -radial * 0.16000001f;

    if (MapPcs.CheckHitCylinderNear(radial, hitMove, 0.0f, m_bgHitMask) != 0) {
        MapPcs.CalcHitPosition(radial);
        m_groundHitOffset = radial - CVector(m_worldPosition);

        if ((MapPcs.GetHitGrpBit() & 0x20) == 0) {
            m_stateFlags0Bits.unk0 = 1;
            m_bgGroupMask = MapPcs.GetHitGrpBit();
            const int groupIndex = gMapHitFace->m_groupIndex;
            if (groupIndex != 0) {
                m_lastBgGroup = static_cast<char>(groupIndex);
            }
            MapPcs.GetHitFaceNormal(&HitFaceNormal());
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800806d4
 * PAL Size: 1428b
 * EN Address: 0x80080070
 * EN Size: 1428b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::bgNormalCollision()
{
    if (fabs(static_cast<double>(m_groundHitOffset.x)) < 0.001f) {
        m_groundHitOffset.x = 0.0f;
    }
    if (fabs(static_cast<double>(m_groundHitOffset.y)) < 0.001f) {
        m_groundHitOffset.y = 0.0f;
    }
    if (fabs(static_cast<double>(m_groundHitOffset.z)) < 0.001f) {
        m_groundHitOffset.z = 0.0f;
    }

    if ((0.0f == m_groundHitOffset.x) && (0.0f == m_groundHitOffset.y) && (0.0f == m_groundHitOffset.z)) {
        return;
    }

    Vec move = m_groundHitOffset;
    move.y = 0.0f;
    Vec pos = m_worldPosition;
    pos.y += 5.0f + m_capsuleHalfHeight;

    unsigned int retry = 4;
    do {
        if (MapPcs.CheckHitCylinderNear(&pos, &move, m_capsuleHalfHeight, m_bgHitMask) == 0) {
            break;
        }

        m_stateFlags0Bits.unk1 = 1;
        MapPcs.CalcHitSlide(&move, 10.0f);

        if (fabs(static_cast<double>(move.x)) < 0.001f) {
            move.x = 0.0f;
        }
        if (fabs(static_cast<double>(move.y)) < 0.001f) {
            move.y = 0.0f;
        }
        if (fabs(static_cast<double>(move.z)) < 0.001f) {
            move.z = 0.0f;
        }

        --retry;
    } while (retry != 0);

    if (retry == 0) {
        m_groundHitOffset.z = 0.0f;
        m_groundHitOffset.y = 0.0f;
        m_groundHitOffset.x = 0.0f;
        return;
    }

    PSVECAdd(&pos, &move, &pos);
    move = m_groundHitOffset;
    move.x = 0.0f;
    move.y -= 5.0f;
    move.z = 0.0f;

    if (MapPcs.CheckHitCylinderNear(&pos, &move, m_capsuleHalfHeight, m_bgHitMask) == 0) {
        goto stepMiss;
    }

    if ((MapPcs.GetHitGrpBit() & 0x20) == 0) {
        m_stateFlags0Bits.unk0 = 1;
        m_bgGroupMask = MapPcs.GetHitGrpBit();
        const int groupIndex = gMapHitFace->m_groupIndex;
        if (groupIndex != 0) {
            m_lastBgGroup = static_cast<char>(groupIndex);
        }
        MapPcs.GetHitFaceNormal(&HitFaceNormal());
    }

    if (MapPcs.CalcHitSlide(&move, 0.5f) != 0) {
        if (MapPcs.CheckHitCylinderNear(&pos, &move, m_capsuleHalfHeight, m_bgHitMask) != 0) {
            Vec hitPos;
            MapPcs.CalcHitPosition(&hitPos);
            PSVECSubtract(&hitPos, &pos, &move);
        }
    }

    pos.y -= m_capsuleHalfHeight;
    PSVECAdd(&pos, &move, &pos);

    if (!(m_jumpLandingDampening > 0.0f) || !(m_groundHitOffset.y < -1.5f)) {
        goto simple;
    }

    float oldY = (m_groundHitOffset.y < -4.0f) ? -4.0f : m_groundHitOffset.y;
    float delta = oldY - move.y;
    float clampedY = (m_groundHitOffset.y < -4.0f) ? -4.0f : m_groundHitOffset.y;

    m_worldPosition.y = pos.y;
    m_groundHitOffset.y = 0.0f;
    m_groundHitOffset.x = pos.x - m_worldPosition.x;
    m_groundHitOffset.z = pos.z - m_worldPosition.z;
    m_gravityY = m_jumpLandingDampening * -(delta + (clampedY - delta));

    if (((m_displayFlags & 1) != 0) && (m_weaponNodeFlagBits.m_attached == 0)) {
        Sound.PlaySe3D(
            0x26,
            &m_worldPosition,
            50.0f + (50.0f * m_gravityY) / 5.0f,
            100.0f + (100.0f * m_gravityY) / 5.0f,
            0);
    }
    return;

simple:
    m_groundHitOffset.y = pos.y - m_worldPosition.y;
    m_groundHitOffset.x = pos.x - m_worldPosition.x;
    m_groundHitOffset.z = pos.z - m_worldPosition.z;
    return;

stepMiss:
    pos.y -= m_capsuleHalfHeight;
    PSVECAdd(&pos, &move, &pos);
    PSVECSubtract(&pos, &m_worldPosition, &m_groundHitOffset);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::bgCollision()
{
    m_stateFlags0Bits.unk0 = 0;
    m_stateFlags0Bits.unk1 = 0;

    m_bgGroupMask = 0;
    m_gravityY = 0.0f;

    bgAttribCollision();

    if (m_bgColMask & 0x01)
    {
        g_MapHitFaceFlag = 1;

        if (Game.m_currentMapId == 0x21)
        {
            bgWorldCollision();
        }
        else
        {
            bgNormalCollision();
        }

        g_MapHitFaceFlag = 0;
    }
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
    struct ColInfo {
        CGObject* obj;
        Vec basePos;
        Vec capsulePos;
        Vec capsuleOffset;
    };

    int keepPushTimer = false;
    ColInfo self;

    self.obj = this;
    PSVECAdd(&m_worldPosition, &m_groundHitOffset, &self.basePos);
    self.capsuleOffset.x = m_bodyEllipsoidOffset * -sinf(m_rotBaseY);
    self.capsuleOffset.y = 0.0f;
    self.capsuleOffset.z = m_bodyEllipsoidOffset * -cosf(m_rotBaseY);
    PSVECAdd(&self.basePos, &self.capsuleOffset, &self.capsulePos);

    if ((m_bgColMask & 0x10000) != 0) {
        for (CGQuadObj* quad = CFlat.FindGQuadObjFirst(); quad != 0;
            quad = CFlat.FindGQuadObjNext(quad)) {
            if (quad->isInner(&self.basePos)) {
                CallOnPush(quad, this, 0);
            }
        }
    }

    for (CGObject* other = CFlat.FindGObjNext(this); other != 0;
         other = CFlat.FindGObjNext(other)) {
        if (((m_bgColMask & 0xE) == 0) || ((other->m_bgColMask & 0xE) == 0)) {
            continue;
        }

        ColInfo info;
        Vec scratch;
        info.obj = other;
        PSVECAdd(&other->m_worldPosition, &other->m_groundHitOffset, &info.basePos);
        info.capsuleOffset.x = other->m_bodyEllipsoidOffset * -sinf(other->m_rotBaseY);
        info.capsuleOffset.y = 0.0f;
        info.capsuleOffset.z = other->m_bodyEllipsoidOffset * -cosf(other->m_rotBaseY);
        PSVECAdd(&info.basePos, &info.capsuleOffset, &info.capsulePos);

        const float capsuleDistance = PSVECDistance(&info.capsulePos, &self.capsulePos);
        if ((0.0f == capsuleDistance)
            || ((m_nearColRadius + other->m_nearColRadius) < capsuleDistance)) {
            continue;
        }

        if (((m_bgColMask & 8) != 0) && ((other->m_bgColMask & 8) != 0)) {
            const unsigned int thisAttack = m_objectFlags & 2;

            if (((thisAttack != 0 && (other->m_objectFlags & 0xC) != 0)
                 || ((m_objectFlags & 0xC) != 0 && (other->m_objectFlags & 2) != 0))
                && ((m_weaponNodeFlagBits.m_attached == 0) || (m_attachOwner != other))
                && ((other->m_weaponNodeFlagBits.m_attached == 0) || (other->m_attachOwner != this))
                && (capsuleDistance < (m_attackColRadius + other->m_attackColRadius))) {
                ColInfo* frontObj;
                ColInfo* hitObj;
                if (thisAttack) {
                    frontObj = &self;
                    hitObj = &info;
                } else {
                    frontObj = &info;
                    hitObj = &self;
                }
                Vec& dir = scratch;
                PSVECSubtract(&hitObj->capsulePos, &frontObj->capsulePos, &dir);
                const float hitRot = std::atan2(dir.x, dir.z);
                const float rotDelta = Math.DstRot(frontObj->obj->m_rotBaseY, hitRot);

                if (fabs(rotDelta) < frontObj->obj->m_frontHitAngle) {
                    CallOnTalk(frontObj->obj, hitObj->obj, 1);
                    CallOnTalk(hitObj->obj, frontObj->obj, 0);
                }
            }
        }

        if (((m_bgColMask & 4) != 0) && ((other->m_bgColMask & 4) != 0)
            && (capsuleDistance < (m_bodyColRadius + other->m_bodyColRadius))) {
            CallOnPush(this, other, 1);
            CallOnPush(other, this, 0);
        }

        if (((m_bgColMask & 2) != 0) && ((other->m_bgColMask & 2) != 0)
            && (0.0f < m_bodyEllipsoidRadius)
            && (0.0f < other->m_bodyEllipsoidRadius)) {
            if (((m_weaponNodeFlagBits.m_attached == 0) || (m_attachOwner != other))
                && ((other->m_weaponNodeFlagBits.m_attached == 0) || (other->m_attachOwner != this))) {
                const int usePushTimers = ((m_objectFlags & 0x40) != 0) && ((other->m_objectFlags & 0x40) != 0);
                const float bodyDistanceLimit = m_bodyEllipsoidRadius + other->m_bodyEllipsoidRadius;

                if (capsuleDistance < bodyDistanceLimit) {
                    if (usePushTimers
                        && ((0.0f != m_groundHitOffset.x) || (0.0f != m_groundHitOffset.z)
                            || (0.0f != other->m_groundHitOffset.x) || (0.0f != other->m_groundHitOffset.z))) {
                        keepPushTimer = true;
                    }

                    if (!usePushTimers || (m_collisionPushTimerMax != 0) || (other->m_collisionPushTimerMax == 0)) {
                        const float thisPush = static_cast<float>(m_pushParamA + m_pushParamB);
                        const float otherPush = static_cast<float>(other->m_pushParamA + other->m_pushParamB);
                        const float rawSplit = 0.5f + (thisPush - otherPush) / 50.0f;
                        float split = (rawSplit < 0.0f)
                            ? 0.0f
                            : ((1.0f < rawSplit) ? 1.0f : rawSplit);

                        Vec& delta = scratch;
                        Vec scaledDelta;
                        PSVECSubtract(&self.capsulePos, &info.capsulePos, &delta);
                        PSVECScale(&delta, &delta, (bodyDistanceLimit - capsuleDistance) / bodyDistanceLimit);
                        PSVECScale(&delta, &scaledDelta, 1.0f - split);
                        PSVECAdd(&self.capsulePos, &scaledDelta, &self.capsulePos);
                        PSVECScale(&delta, &scaledDelta, -split);
                        PSVECAdd(&info.capsulePos, &scaledDelta, &info.capsulePos);
                    }
                }
            }
        }

        PSVECSubtract(&info.capsulePos, &other->m_worldPosition, &other->m_groundHitOffset);
        PSVECSubtract(&other->m_groundHitOffset, &info.capsuleOffset, &other->m_groundHitOffset);
    }

    if (keepPushTimer) {
        int dec = m_collisionPushTimerMax - 1;
        m_collisionPushTimerMax = dec & ~(dec >> 31);
    } else {
        m_collisionPushTimerMax = 0x32;
    }

    PSVECSubtract(&self.capsulePos, &m_worldPosition, &m_groundHitOffset);
    PSVECSubtract(&m_groundHitOffset, &self.capsuleOffset, &m_groundHitOffset);
}

/*
 * --INFO--
 * PAL Address: 0x80081318
 * PAL Size: 2752b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::move()
{
    if (!HasLoadedModel(m_charaModelHandle)) {
        return;
    }

    if (Game.m_currentMapId != 0x21 && m_weaponNodeFlagBits.m_unk10 && !m_weaponNodeFlagBits.m_control3) {
        PSVECAdd(&m_groundHitOffset, &m_bodyOffset, &m_groundHitOffset);
        if (m_groundHitOffset.y < -5.0f) {
            m_groundHitOffset.y = -5.0f;
        }
    } else if (m_weaponNodeFlagBits.m_unk04) {
        m_groundHitOffset.y = 0.0f;
    }

    int movingWithScript = 0;
    int hasStickInput = 0;
    m_groundHitOffset.y += m_gravityY;
    Vec moveVec;

    if (m_weaponNodeFlagAll.m_bits1.m_bit20) {
        int scriptMoveEnd = 0;
        if (m_weaponNodeFlagAll.m_bits1.m_bit10) {
            moveVec = m_moveTarget;
        } else {
            PSVECSubtract(&m_moveTarget, &m_worldPosition, &moveVec);
        }

        if ((Game.m_currentMapId != 0x21) && !m_weaponNodeFlagAll.m_bits1.m_bit02) {
            moveVec.y = 0.0f;
        }

        const float moveMag = PSVECMag(&moveVec);
        if (0.0f == moveMag) {
            scriptMoveEnd = 1;
        } else if (m_weaponNodeFlagAll.m_bits1.m_bit10) {
            PSVECNormalize(&moveVec, &moveVec);
            PSVECScale(&moveVec, &moveVec, static_cast<float>(m_moveTimer));
        } else if (moveMag < m_moveTimer) {
            scriptMoveEnd = 1;
        } else {
            PSVECNormalize(&moveVec, &moveVec);
            PSVECScale(&moveVec, &moveVec, static_cast<float>(m_moveTimer));
        }

        m_turnFrames -= 1;
        if (static_cast<int>(m_turnFrames) <= 0) {
            scriptMoveEnd = 2;
        }

        if ((!m_weaponNodeFlagAll.m_bits1.m_bit10 && (scriptMoveEnd != 0))
            || (m_weaponNodeFlagAll.m_bits1.m_bit10 && (scriptMoveEnd == 2))) {
            m_weaponNodeFlagAll.m_bits1.m_bit20 = 0;
            CFlatRuntime::CStack stack;
            stack.m_word = (scriptMoveEnd == 2) ? 1 : 0;
            gCFlatRuntime().SystemCall(this, 2, 7, 1, &stack, 0);
        }

        movingWithScript = 1;
    } else {
        if (!((m_animStateMisc >= 0)
              && (m_animStateMisc < 4)
              && m_weaponNodeFlagAll.m_bits1.m_shield
              && m_weaponNodeFlagAll.m_bits1.m_menuReady
              && ((Game.m_gameWork.m_menuStageMode == 0)
                  || ((Game.m_gameWork.m_menuStageMode != 0) && (m_animStateMisc == 0))))) {
            goto calcAnimSlot;
        }

        u16 buttons = Pad.GetButton(m_animStateMisc);
        const u16 buttonsDown = Pad.GetButtonDown(m_animStateMisc);
        const u16 buttonsRepeat = Pad.GetButtonUp(m_animStateMisc);

        if ((buttons != 0) && (buttonsRepeat != 0)) {
            buttons |= buttonsRepeat;
        }

        moveVec.z = 0.0f;
        moveVec.y = 0.0f;
        moveVec.x = 0.0f;

        u32 miniGameFlags = DbgMenuPcs.GetDbgFlagsRaw();
        if ((miniGameFlags & 0x100) != 0 && moveVec.x == 0.0f && moveVec.x == 0.0f) {
            moveVec.x -= Pad.GetLeftStickX(m_animStateMisc);
            moveVec.z += Pad.GetLeftStickY(m_animStateMisc);
            if (moveVec.x || moveVec.z) {
                hasStickInput = 1;
            }
        }

        if (!hasStickInput) {
            if ((buttons & 1) != 0) {
                moveVec.x += 1.0f;
            }
            if ((buttons & 2) != 0) {
                moveVec.x -= 1.0f;
            }
            if ((buttons & 8) != 0) {
                moveVec.z += 1.0f;
            }
            if ((buttons & 4) != 0) {
                moveVec.z -= 1.0f;
            }
        }

        if (((miniGameFlags & 0x40) == 0) && ((buttonsDown & 0x1000) != 0)) {
            if (m_weaponNodeFlagBits.m_unk10) {
                PSVECAdd(&m_groundHitOffset, &m_jumpOffset, &m_groundHitOffset);
            } else {
                m_worldPosition.y += 10.0f;
            }
        }

        if (Game.m_currentMapId == 0x21) {
            Mtx cameraWorldMtx;
            PSMTXCopy(CameraPcs.m_cameraWorldMtx, cameraWorldMtx);
            moveVec.x = -moveVec.x;
            moveVec.y = 0.0f;
            moveVec.z = -moveVec.z;
            PSMTXMultVec(cameraWorldMtx, &moveVec, &moveVec);
        }
    }

    if (moveVec.x || moveVec.z || moveVec.y) {
        float inputYawF;
        float cameraYaw;
        if (movingWithScript) {
            cameraYaw = 0.0f;
        } else {
            cameraYaw = CameraPcs.m_yaw;
        }

        const double inputYaw = atan2(static_cast<double>(moveVec.x), static_cast<double>(moveVec.z));
        inputYawF = static_cast<float>(inputYaw);

        const float sinYaw = static_cast<float>(sin(static_cast<double>(cameraYaw)));
        const float cosYaw = static_cast<float>(cos(static_cast<double>(cameraYaw)));
        if (Game.m_currentMapId != 0x21) {
            const float oldZ = moveVec.z;
            const float oldX = moveVec.x;
            moveVec.z = oldX * sinYaw + oldZ * cosYaw;
            moveVec.x = oldX * cosYaw - oldZ * sinYaw;
        }

        if (!movingWithScript) {
            float speed = m_moveBaseSpeed;
            if (hasStickInput && ((DbgMenuPcs.GetDbgFlagsRaw() & 0x200) != 0)) {
                const float mag = PSVECMag(&moveVec);
                speed *= 4.0f * mag;
            }

            PSVECNormalize(&moveVec, &moveVec);

            if (m_weaponNodeFlagAll.m_bits1.m_shield
                && m_weaponNodeFlagAll.m_bits1.m_menuReady
                && (m_ownerType == 0)) {
                if ((DbgMenuPcs.GetDbgFlagsRaw() & 2) != 0) {
                    speed *= 4.0f;
                }

                const s32 cflatCenterState = CFlatCenterState();
                if (cflatCenterState == 1) {
                    Vec partyCenter;
                    partyCenter.x = (Game.m_partyBound.m_min.x + Game.m_partyBound.m_max.x) / 2.0f;
                    partyCenter.y = (Game.m_partyBound.m_min.y + Game.m_partyBound.m_max.y) / 2.0f;
                    partyCenter.z = (Game.m_partyBound.m_min.z + Game.m_partyBound.m_max.z) / 2.0f;

                    Vec centerDelta;
                    PSVECSubtract(&m_worldPosition, &partyCenter, &centerDelta);
                    float centerDist = PSVECMag(&centerDelta);
                    PSVECNormalize(&centerDelta, &centerDelta);

                    const float dirDot = PSVECDotProduct(&moveVec, &centerDelta);
                    if (0.0f < dirDot) {
                        centerDist /= CFlatCenterDistanceScale();
                        const float clampDist = ClampFloat(centerDist, 0.0f, 1.0f);
                        speed *= -((clampDist * clampDist) - 1.0f);
                    }
                }
            }

            if ((m_bgGroupMask & 0x400000) != 0) {
                speed *= 0.75f;
            }

            PSVECScale(&moveVec, &moveVec, speed);
        }

        PSVECAdd(&m_groundHitOffset, &moveVec, &m_groundHitOffset);

        if (!movingWithScript || m_weaponNodeFlagAll.m_bits1.m_bit08) {
            if (Game.m_currentMapId == 0x21) {
                const float slideSq = PSVECSquareMag(&m_groundHitOffset);
                if (0.01f < slideSq) {
                    Mtx yawMtx;
                    Mtx pitchMtx;
                    Vec worldUp;
                    Vec worldPosNorm;
                    Vec tangent;
                    Vec moveNorm;
                    Vec cross;

                    PSMTXRotRad(yawMtx, 'y', static_cast<float>(atan2(static_cast<double>(m_worldPosition.x),
                                                                      static_cast<double>(m_worldPosition.z))));
                    reinterpret_cast<u32*>(&worldUp)[0] = reinterpret_cast<const u32*>(&sMap21WorldUpAxis)[0];
                    reinterpret_cast<u32*>(&worldUp)[1] = reinterpret_cast<const u32*>(&sMap21WorldUpAxis)[1];
                    reinterpret_cast<u32*>(&worldUp)[2] = reinterpret_cast<const u32*>(&sMap21WorldUpAxis)[2];
                    reinterpret_cast<u32*>(&tangent)[0] = reinterpret_cast<const u32*>(&sMap21TangentAxis)[0];
                    reinterpret_cast<u32*>(&tangent)[1] = reinterpret_cast<const u32*>(&sMap21TangentAxis)[1];
                    reinterpret_cast<u32*>(&tangent)[2] = reinterpret_cast<const u32*>(&sMap21TangentAxis)[2];
                    PSVECNormalize(&m_worldPosition, &worldPosNorm);
                    float upDot = PSVECDotProduct(&worldUp, &worldPosNorm);
                    PSMTXRotRad(pitchMtx, 'x', acosf(upDot));
                    PSMTXConcat(yawMtx, pitchMtx, yawMtx);

                    PSVECNormalize(&m_groundHitOffset, &moveNorm);
                    PSMTXMultVec(yawMtx, &tangent, &tangent);
                    float tanDot = PSVECDotProduct(&tangent, &moveNorm);
                    float targetRot = acosf(tanDot);

                    PSVECCrossProduct(&tangent, &moveNorm, &cross);
                    if (PSVECDotProduct(&worldPosNorm, &cross) < 0.0f) {
                        targetRot = -targetRot;
                    }
                    m_rotTargetY = targetRot;
                }
            } else {
                m_rotTargetY = inputYawF - cameraYaw;
            }
        }

        if (!movingWithScript || m_weaponNodeFlagAll.m_bits1.m_bit04) {
            m_animSlotSel = m_animSlots[1];
        } else {
            m_animSlotSel = m_animSlots[0];
        }
        return;
    }

calcAnimSlot:
    const double rotDelta = static_cast<double>(Math.DstRot(m_rotTargetY, m_rotBaseY));
    m_animSlotSel = m_animSlots[(fabs(rotDelta) <= 0.7853982f) ? 0 : 1];
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
 * PAL Address: 0x80081ea4
 * PAL Size: 980b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::onCreate()
{
    int cFill = -1;
    m_worldPosition.z = 0.0f;
    m_worldPosition.y = 0.0f;
    m_worldPosition.x = 0.0f;
    m_groundHitOffset.z = 0.0f;
    m_groundHitOffset.y = 0.0f;
    m_groundHitOffset.x = 0.0f;

    m_rotBaseZ = 0.0f;
    m_rotBaseY = 0.0f;
    m_rotBaseX = 0.0f;
    m_rotTargetZ = 0.0f;
    m_rotTargetY = 0.0f;
    m_rotTargetX = 0.0f;

    m_bodyOffset.x = 0.0f;
    m_bodyOffset.y = -1.0f;
    m_bodyOffset.z = 0.0f;
    m_jumpOffset.x = 0.0f;
    m_jumpOffset.y = 10.0f;
    m_jumpOffset.z = 0.0f;
    m_moveOffset.x = 0.0f;
    m_moveOffset.y = 1.0f;
    m_moveOffset.z = 0.0f;

    m_charaModelHandle = 0;
    m_weaponModelHandle = 0;
    m_shieldModelHandle = 0;

    m_animStateMisc = cFill;
    m_weaponNodeFlagAll.m_bits1.m_shield = 0;
    m_weaponNodeFlagAll.m_bits1.m_menuReady = 1;

    m_moveBaseSpeed = 2.0f;
    m_currentAnimSlot = cFill;

    m_bodyEllipsoidRadius = 5.0f;
    m_bodyEllipsoidOffset = 0.0f;
    m_bodyEllipsoidAspect = 1.0f;
    m_capsuleHalfHeight = 5.0f;

    m_attackColRadius = 7.0f;
    m_bodyColRadius = 6.0f;
    m_nearColRadius = 10.0f;
    m_bgColMask = 0;

    m_weaponNodeFlagAll.m_bits1.m_bit20 = 0;
    m_weaponNodeFlagBits.m_unk10 = 1;
    m_weaponNodeFlagBits.m_control3 = 0;
    m_weaponNodeFlagBits.m_unk04 = 1;

    m_objectFlags = 1;
    m_displayFlags = 3;
    m_rotationX = 1.0f;
    m_rotationY = 1.0f;
    m_rotationZ = 1.0f;
    m_attrFlags = 0;
    m_ownerType = cFill;
    m_classWorkIndex = 0;
    m_scriptHandle = 0;

    unk_0x184 = 0.0f;
    unk_0x188 = 0.0f;
    m_weaponNodeFlagBits.m_attached = 0;
    m_weaponNodeFlagBits.m_unk20 = 1;
    m_weaponNodeFlagBits.m_unk40 = 0;
    m_bgHitMask = cFill;
    m_animSlotSel = cFill;
    m_turnSpeed = 0.0f;
    m_pushParamB = 0;
    m_pushParamA = 0;

    m_shieldNodeFlagBits.m_bit40 = 0;
    m_frontHitAngle = 0.7853982f;
    m_lookAtTarget = 0;
    m_alphaTarget = 1.0f;
    m_currentAlpha = 1.0f;
    m_shieldNodeFlagBits.m_bit20 = 0;
    m_animBlend = 1.0f;
    m_bgAttrValue = 1.0f;
    m_bounceFactor = 1.0f;
    m_gravityY = 0.0f;
    m_jumpLandingDampening = 0.0f;

    m_stateFlags0Bits.unk3 = 0;

    m_bgCollisionQtrn.z = 0.0f;
    m_bgCollisionQtrn.y = 0.0f;
    m_bgCollisionQtrn.x = 0.0f;
    m_bgCollisionQtrn.w = 1.0f;

    m_shieldNodeFlagBits.m_bit10 = 0;
    m_dispItemTimer = 0;
    m_shieldNodeFlagBits.m_bit80 = 0;
    m_lastBgAttr = 1.0f;
    m_shieldNodeFlagBits.m_bit08 = 0;
    m_shieldNodeFlagBits.m_bit04 = 0;
    m_collisionPushTimerMax = 0x32;

    m_bgGroupMask = 0;
    m_lastBgGroup = 0;
    m_lifeTimer = 0;
    m_stateFlags0Bits.unk4 = 0;
    m_ownerSlot = 0;
    m_stateFlags0Bits.unk0 = 0;
    m_swayTarget.z = 0.0f;
    m_swayTarget.x = 0.0f;
    m_swayTarget.y = 1.0f;
    m_swayDirection.x = m_swayTarget.x;
    m_swayDirection.y = m_swayTarget.y;
    m_swayDirection.z = m_swayTarget.z;

    m_turnFactor = 0.25f;
    m_alphaStep = 0.033333335f;
    m_moveMode = 0;
    m_moveModePrevious = 4;
    m_hitFaceNormal.z = 0.0f;
    m_hitFaceNormal.y = 0.0f;
    m_hitFaceNormal.x = 0.0f;
    m_worldParam = 0.0f;

    m_lookAtTargetNodeIndex = cFill;
    m_worldParamA = 0;
    m_lookAtAccumYaw = 0.0f;
    m_lookAtAccumPitch = 0.0f;
    m_weaponAttachNode = cFill;
    m_shieldAttachNodeIndex = cFill;
    m_motionMode = 0;
    m_weaponNodeFlagBits.m_prg = 0;
    m_extraMoveVec.z = 0.0f;
    m_extraMoveVec.y = 0.0f;
    m_extraMoveVec.x = 0.0f;
    m_shieldNodeFlagBits.m_bit01 = 0;
    m_field_0x56 = 0x7D;
    m_twistTarget = 0.0f;

    for (unsigned int i = 0; i < sizeof(m_animSlots); i++) {
        m_animSlots[i] = cFill;
    }

    memset(m_attackColliders, 0, sizeof(m_attackColliders));
    memset(m_damageColliders, 0, sizeof(m_damageColliders));
    memset(m_dropItemCodes, 0, sizeof(m_dropItemCodes));
}


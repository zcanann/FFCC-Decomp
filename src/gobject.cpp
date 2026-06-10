#include "ffcc/ptrarray.h"
#include "ffcc/gobject.h"

#include "ffcc/cflat_runtime.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/color.h"
#include "ffcc/game.h"
#include "ffcc/graphic.h"
#include "ffcc/itemobj.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_dbgmenu.h"
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

extern "C" int CrossCheckSphereVector__5CMathFP3VecPfP3VecP3VecP3Vecf(
    CMath*, Vec*, float*, Vec*, Vec*, Vec*, float, float, float);
extern double DOUBLE_803303e8;
extern double DOUBLE_80330400;
extern const Vec DAT_801D9B88;
extern const Vec DAT_801D9B94;

struct CModelAnimState {
    u8 _padB4[0xB4];
    float m_time;
    u8 _padB8[4];
    float m_animStart;
    float m_animEnd;
    u8 _padC4[0xC];
    CChara::CAnim* m_anim;
};

struct GObjectSRT {
    Vec m_trans;
    Vec m_rot;
    Vec m_scale;
};

STATIC_ASSERT(offsetof(CGObject, m_weaponNodeFlags) == 0x9A);
STATIC_ASSERT(offsetof(CGObject, m_weaponNodeFlagBits) == 0x9A);
STATIC_ASSERT(offsetof(CGObject, m_weaponNodeFlagBytes) == 0x9A);
STATIC_ASSERT(sizeof(CGObject::WeaponNodeFlagBits) == 1);
STATIC_ASSERT(sizeof(CGObject::WeaponNodeFlagBytes) == 2);

static inline CModelAnimState& ModelAnimState(CChara::CModel* model)
{
    return *reinterpret_cast<CModelAnimState*>(model);
}

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

static inline unsigned char* ModelBytes(CChara::CModel* model)
{
    return reinterpret_cast<unsigned char*>(model);
}

static inline unsigned char* ModelNodes(CChara::CModel* model)
{
    return reinterpret_cast<unsigned char*>(model->m_nodes);
}

static inline MtxPtr ModelNodeMtx(CChara::CModel* model, int nodeIndex)
{
    return reinterpret_cast<MtxPtr>(ModelNodes(model) + nodeIndex * 0xC0 + 0x6C);
}

static inline float& ModelLightAlpha(CChara::CModel* model)
{
    return model->m_lightAlpha;
}

static inline CChara::CAnim*& ModelAnim(CChara::CModel* model)
{
    return model->m_anim;
}

static inline float& ModelTime(CChara::CModel* model)
{
    return model->m_curFrame;
}

static inline float& ModelAnimStart(CChara::CModel* model)
{
    return model->m_animStart;
}

static inline float& ModelAnimEnd(CChara::CModel* model)
{
    return model->m_animEnd;
}

static inline unsigned char& ModelFlagsA0(CChara::CModel* model)
{
    return model->m_flagsA0;
}

static inline int RemapPadSlot(CPad* pad, int padIndex)
{
    int activePad = pad->m_debugPadPort;
    return static_cast<int>(padIndex & ~(static_cast<int>(~((activePad - padIndex) | (padIndex - activePad))) >> 31));
}

static inline float& ModelChestAmp(CChara::CModel* model)
{
    return *reinterpret_cast<float*>(ModelBytes(model) + 0xDC);
}

static inline float& ModelChestTilt(CChara::CModel* model)
{
    return *reinterpret_cast<float*>(ModelBytes(model) + 0xE0);
}

static inline float& ModelTwistAngle(CChara::CModel* model)
{
    return *reinterpret_cast<float*>(ModelBytes(model) + 0x120);
}

static inline Vec& ModelWindVector(CChara::CModel* model)
{
    return *reinterpret_cast<Vec*>(ModelBytes(model) + 0xC4);
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

extern "C" float sAnimFrameOffset;
extern "C" const float sZeroFloat;

static inline float WrapAnimFrame(float value, float span)
{
    if (value < sZeroFloat) {
        return (span - sAnimFrameOffset) - fmodf(-value, span);
    }
    return fmodf(value, span);
}

static const float sBgDefaultGravityY = 0.0;
static const char s_gobject_cpp[] = "gobject.cpp";
static const char s_l_item2[] = "l_item2";
static const char s_r_item[] = "r_item";
static const char s_noTurnMotion[36] =
    "\203\136\201\133\203\223\203\202\201\133\203\126\203\207\203\223"
    "\202\315\202\240\202\350\202\334\202\271\202\361\201\102\012";
extern "C" float sAnimFrameOffset;                    // FLOAT_80330338
static const float sHugeCylinderExtent = 10000000000.0f; // FLOAT_8033033c
static const float sNegHugeCylinderExtent = -10000000000.0f; // FLOAT_80330340
static const float sQuarterTurn = 1.5707964f;         // FLOAT_80330344
extern "C" const double sLoopBias;                    // DOUBLE_80330378
extern "C" const float sZeroFloat;                    // FLOAT_80330350
static const float sPushDistance = 1000.0f;           // FLOAT_80330354
extern const float sDownUnitY = -1.0f;                // FLOAT_80330358
static const float sDownProbeDistance = -10000.0f;    // FLOAT_8033035c
static const float sStepProbeHeight = 5.0f;           // FLOAT_80330360
static const float sBgAttrSlow = 0.75f;               // FLOAT_80330364
static const float sBgAttrNormal = 0.5f;              // FLOAT_80330368
static const float sBgAttrFast = 0.25f;               // FLOAT_8033036c
static const float sDebugScreenY = 320.0f;            // FLOAT_80330370
static const float sDebugScreenX = 224.0f;            // FLOAT_80330374
static const float sNegativeOne = -1.0f;              // FLOAT_80330390
static const float sLargeDistance = 10000000.0f;      // FLOAT_80330394
static const float sDefaultMoveBaseSpeed = 2.0f;      // FLOAT_803303d4
static const float sHitProbeHeight = 100.0f;          // FLOAT_80330410
static const float sHitMoveScale = 0.16000001f;       // FLOAT_80330414
static const float sJumpLift = 10.0f;                 // FLOAT_80330418
static const float sLandingDampenCutoff = -1.5f;      // FLOAT_8033041c
static const float sMinGroundClamp = -4.0f;           // FLOAT_80330420
static const float sCrossCheckOuterRadius = 50.0f;    // FLOAT_80330424
static const float sGroundOffsetFloor = -5.0f;        // FLOAT_80330428
static const float sAnalogSpeedScale = 4.0f;          // FLOAT_8033042c
static const float sSlideThreshold = 0.01f;           // FLOAT_80330430
static const float sDefaultAttackColRadius = 7.0f;    // FLOAT_80330434
static const float sDefaultBodyColRadius = 6.0f;      // FLOAT_80330438
static const float sDefaultFrontHitAngle = 0.78539819f; // FLOAT_8033043c
static const float sDefaultBgDownDist = 0.033333335f; // FLOAT_80330440

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
#pragma push
#pragma optimization_level 3
void CGObject::onCreate()
{
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
    m_bodyOffset.y = sNegativeOne;
    m_bodyOffset.z = 0.0f;
    m_jumpOffset.x = 0.0f;
    m_jumpOffset.y = sJumpLift;
    m_jumpOffset.z = 0.0f;
    m_moveOffset.x = 0.0f;
    m_moveOffset.y = 1.0f;
    m_moveOffset.z = 0.0f;

    m_charaModelHandle = 0;
    m_weaponModelHandle = 0;
    m_shieldModelHandle = 0;

    *reinterpret_cast<char*>(&m_animStateMisc) = -1;
    m_weaponNodeFlagAll.m_bits1.m_shield = 0;
    m_weaponNodeFlagAll.m_bits1.m_menuReady = 1;

    m_moveBaseSpeed = sDefaultMoveBaseSpeed;
    m_currentAnimSlot = -1;

    m_bodyEllipsoidRadius = sStepProbeHeight;
    m_bodyEllipsoidOffset = 0.0f;
    m_bodyEllipsoidAspect = 1.0f;
    m_capsuleHalfHeight = sStepProbeHeight;

    m_attackColRadius = sDefaultAttackColRadius;
    m_bodyColRadius = sDefaultBodyColRadius;
    m_nearColRadius = sJumpLift;
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
    m_ownerType = -1;
    m_classWorkIndex = 0;
    m_scriptHandle = 0;

    unk_0x184 = 0.0f;
    unk_0x188 = 0.0f;
    m_weaponNodeFlagBits.m_attached = 0;
    m_weaponNodeFlagBits.m_unk20 = 1;
    m_weaponNodeFlagBits.m_unk40 = 0;
    m_bgHitMask = -1;
    m_animSlotSel = -1;
    m_turnSpeed = 0.0f;
    m_pushParamB = 0;
    m_pushParamA = 0;

    m_shieldNodeFlagBits.m_bit40 = 0;
    m_frontHitAngle = sDefaultFrontHitAngle;
    m_lookAtTarget = 0;
    m_stepSlopeLimit = 1.0f;
    m_lookAtTimer = 1.0f;
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

    *reinterpret_cast<u32*>(&m_radiusCtrl.x) = 0;
    *reinterpret_cast<unsigned char*>(&m_lastBgGroup) = 0;
    *reinterpret_cast<u32*>(&m_moveAnimState) = 0;
    m_stateFlags0Bits.unk4 = 0;
    m_ownerSlot = 0;
    m_stateFlags0Bits.unk0 = 0;
    m_radiusCtrlVel.x = 0.0f;
    m_radiusCtrl.y = 0.0f;
    m_radiusCtrl.z = 1.0f;
    m_radiusCtrlVel.y = m_radiusCtrl.y;
    m_radiusCtrlVel.z = m_radiusCtrl.z;
    m_groundFriction = m_radiusCtrlVel.x;
    m_moveMode = 0;
    m_moveModePrevious = 4;

    m_hitNormal.x = sBgAttrFast;
    m_hitNormal.y = 0.0f;
    m_hitNormal.z = 0.0f;
    m_bgDownDist = sDefaultBgDownDist;
    m_groundSlide = 0.0f;
    m_worldParam = 0.0f;
    m_worldParamA = 0;
    m_field_0x56 = 0x7D;
    *reinterpret_cast<float*>(m_worldMode) = 0.0f;

    m_lookAtTargetNodeIndex = -1;
    m_lookAtAccumYaw = 0.0f;
    m_lookAtAccumPitch = 0.0f;
    m_weaponAttachNode = -1;
    m_shieldAttachNodeIndex = -1;
    *reinterpret_cast<u16*>(&m_lastMapIdHit) = 0;
    m_weaponNodeFlagBits.m_prg = 0;
    m_extraMoveVec.z = 0.0f;
    m_extraMoveVec.y = 0.0f;
    m_extraMoveVec.x = 0.0f;
    m_shieldNodeFlagBits.m_bit01 = 0;

    int animStateOffset = 0;
    for (int i = 0; i < 2; i++) {
        s8* animState = reinterpret_cast<s8*>(m_animQueue) + animStateOffset - 0x41;
        animState[0] = -1;
        animState[1] = -1;
        animState[2] = -1;
        animState[3] = -1;
        animState[4] = 0xFF;
        animState[5] = -1;
        animState[6] = -1;
        animState[7] = 0xFF;
        animState = reinterpret_cast<s8*>(m_animQueue) + animStateOffset - 0x39;
        animState[0] = -1;
        animState[1] = -1;
        animState[2] = -1;
        animState[3] = -1;
        animState[4] = 0xFF;
        animState[5] = -1;
        animState[6] = -1;
        animState[7] = 0xFF;
        animState = reinterpret_cast<s8*>(m_animQueue) + animStateOffset - 0x31;
        animState[0] = -1;
        animState[1] = -1;
        animState[2] = -1;
        animState[3] = -1;
        animState[4] = 0xFF;
        animState[5] = -1;
        animState[6] = -1;
        animState[7] = 0xFF;
        animState = reinterpret_cast<s8*>(m_animQueue) + animStateOffset - 0x29;
        animStateOffset += 0x20;
        animState[0] = -1;
        animState[1] = -1;
        animState[2] = -1;
        animState[3] = -1;
        animState[4] = 0xFF;
        animState[5] = -1;
        animState[6] = -1;
        animState[7] = 0xFF;
    }

    memset(&m_attackColliders[0].m_localStart.y, 0, 0x180);
    memset(&m_damageColliders[0].m_localPosition.y, 0, 0x140);
    memset(m_dropItemCodes, 0, sizeof(m_dropItemCodes));
}
#pragma pop

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
        if (m_groundHitOffset.y < sGroundOffsetFloor) {
            m_groundHitOffset.y = sGroundOffsetFloor;
        }
    } else if (m_weaponNodeFlagBits.m_unk04) {
        m_groundHitOffset.y = sZeroFloat;
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
            moveVec.y = sZeroFloat;
        }

        const double moveMag = static_cast<double>(PSVECMag(&moveVec));
        if (static_cast<double>(sZeroFloat) == moveMag) {
            scriptMoveEnd = 1;
        } else if (m_weaponNodeFlagAll.m_bits1.m_bit10) {
            PSVECNormalize(&moveVec, &moveVec);
            PSVECScale(&moveVec, &moveVec, static_cast<float>(m_moveTimer));
        } else if (moveMag < static_cast<double>(m_moveTimer)) {
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
            stack.m_word = static_cast<u32>(__cntlzw(static_cast<u32>(2 - scriptMoveEnd))) >> 5;
            gCFlatRuntime().SystemCall(this, 2, 7, 1, &stack, 0);
        }

        movingWithScript = 1;
    } else {
        const int player = static_cast<s8>(m_animStateMisc);
        if ((static_cast<s8>(m_animStateMisc) >= 0)
            && (static_cast<s8>(m_animStateMisc) < 4)
            && m_weaponNodeFlagAll.m_bits1.m_shield
            && m_weaponNodeFlagAll.m_bits1.m_menuReady
            && ((Game.m_gameWork.m_menuStageMode == 0) || (static_cast<s8>(m_animStateMisc) == 0))) {
            u16 buttons = (Pad.m_debugPadLock != 0 || (player == 0 && Pad.m_debugPadPort != -1))
                ? 0
                : Pad.GetPadInputs()[RemapPadSlot(&Pad, player)].button[0];
            const u16 buttonsDown = (Pad.m_debugPadLock != 0 || (player == 0 && Pad.m_debugPadPort != -1))
                ? 0
                : Pad.GetPadInputs()[RemapPadSlot(&Pad, player)].buttonDown[0];
            const u16 buttonsRepeat = (Pad.m_debugPadLock != 0 || (player == 0 && Pad.m_debugPadPort != -1))
                ? 0
                : Pad.GetPadInputs()[RemapPadSlot(&Pad, player)].repeatButton;

            if ((buttons != 0) && (buttonsRepeat != 0)) {
                buttons |= buttonsRepeat;
            }

            moveVec.z = sZeroFloat;
            moveVec.y = sZeroFloat;
            moveVec.x = sZeroFloat;

            u32 miniGameFlags = DbgMenuPcs.GetDbgFlagsRaw();
            if ((miniGameFlags & 0x100) != 0) {
                const float stickX = (Pad.m_debugPadLock != 0 || (player == 0 && Pad.m_debugPadPort != -1))
                    ? sZeroFloat
                    : Pad.GetPadInputs()[RemapPadSlot(&Pad, player)].stickXF;
                const float stickY = (Pad.m_debugPadLock != 0 || (player == 0 && Pad.m_debugPadPort != -1))
                    ? sZeroFloat
                    : Pad.GetPadInputs()[RemapPadSlot(&Pad, player)].stickYF;
                moveVec.x = sZeroFloat - stickX;
                moveVec.z = sZeroFloat + stickY;
                if ((moveVec.x != sZeroFloat) || (moveVec.z != sZeroFloat)) {
                    hasStickInput = 1;
                }
            }

            if (!hasStickInput) {
                if ((buttons & 1) != 0) {
                    moveVec.x += sAnimFrameOffset;
                }
                if ((buttons & 2) != 0) {
                    moveVec.x -= sAnimFrameOffset;
                }
                if ((buttons & 8) != 0) {
                    moveVec.z += sAnimFrameOffset;
                }
                if ((buttons & 4) != 0) {
                    moveVec.z -= sAnimFrameOffset;
                }
            }

            if (((miniGameFlags & 0x40) == 0) && ((buttonsDown & 0x1000) != 0)) {
                if (m_weaponNodeFlagBits.m_unk10) {
                    PSVECAdd(&m_groundHitOffset, &m_jumpOffset, &m_groundHitOffset);
                } else {
                    m_worldPosition.y += sJumpLift;
                }
            }

            if (Game.m_currentMapId == 0x21) {
                Mtx cameraWorldMtx;
                PSMTXCopy(CameraPcs.m_cameraWorldMtx, cameraWorldMtx);
                moveVec.x = -moveVec.x;
                moveVec.z = -moveVec.z;
                moveVec.y = sZeroFloat;
                PSMTXMultVec(cameraWorldMtx, &moveVec, &moveVec);
            }
        }
    }

    if ((moveVec.x != sZeroFloat) || (moveVec.y != sZeroFloat) || (moveVec.z != sZeroFloat)) {
        float cameraYaw;
        if (movingWithScript) {
            cameraYaw = sZeroFloat;
        } else {
            cameraYaw = *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs) + 0xf8);
        }

        const double inputYaw = atan2(static_cast<double>(moveVec.x), static_cast<double>(moveVec.z));
        const float inputYawF = static_cast<float>(inputYaw);

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
                speed *= sAnalogSpeedScale * mag;
            }

            PSVECNormalize(&moveVec, &moveVec);

            if (m_weaponNodeFlagAll.m_bits1.m_shield
                && m_weaponNodeFlagAll.m_bits1.m_menuReady
                && (m_ownerType == 0)) {
                if ((DbgMenuPcs.GetDbgFlagsRaw() & 2) != 0) {
                    speed *= sAnalogSpeedScale;
                }

                const s32 cflatCenterState = CFlatCenterState();
                if (cflatCenterState == 1) {
                    Vec partyCenter;
                    partyCenter.x = (Game.m_partyMinX + Game.m_partyMaxX) * sBgAttrNormal;
                    partyCenter.y = (Game.m_partyMinY + Game.m_partyMaxY) * sBgAttrNormal;
                    partyCenter.z = (Game.m_partyMinZ + Game.m_partyMaxZ) * sBgAttrNormal;

                    Vec centerDelta;
                    PSVECSubtract(&m_worldPosition, &partyCenter, &centerDelta);
                    float centerDist = PSVECMag(&centerDelta);
                    PSVECNormalize(&centerDelta, &centerDelta);

                    const float dirDot = PSVECDotProduct(&moveVec, &centerDelta);
                    if (sZeroFloat < dirDot) {
                        centerDist /= CFlatCenterDistanceScale();
                        float clampDist = centerDist;
                        if (!(clampDist < sZeroFloat)) {
                            if (sAnimFrameOffset < clampDist) {
                                clampDist = sAnimFrameOffset;
                            }
                            speed *= -((clampDist * clampDist) - sAnimFrameOffset);
                        }
                    }
                }
            }

            if ((*reinterpret_cast<u32*>(&m_radiusCtrl.x) & 0x400000) != 0) {
                speed *= sBgAttrSlow;
            }

            PSVECScale(&moveVec, &moveVec, speed);
        }

        PSVECAdd(&m_groundHitOffset, &moveVec, &m_groundHitOffset);

        if (!movingWithScript || m_weaponNodeFlagAll.m_bits1.m_bit08) {
            if (Game.m_currentMapId == 0x21) {
                const float slideSq = PSVECSquareMag(&m_groundHitOffset);
                if (sSlideThreshold < slideSq) {
                    Mtx yawMtx;
                    Mtx pitchMtx;
                    Vec worldPosNorm;
                    Vec worldUp;
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
                    if (PSVECDotProduct(&worldPosNorm, &cross) < sZeroFloat) {
                        targetRot = -targetRot;
                    }
                    m_rotTargetY = targetRot;
                }
            } else {
                m_rotTargetY = inputYawF - cameraYaw;
            }
        }

        if (!movingWithScript || m_weaponNodeFlagAll.m_bits1.m_bit04) {
            m_animSlotSel = *reinterpret_cast<s8*>(&m_animStartFrame);
        } else {
            m_animSlotSel = *(reinterpret_cast<s8*>(&m_shieldNodeFlags) + 1);
        }
        return;
    }

    const double rotDelta = static_cast<double>(Math.DstRot(m_rotTargetY, m_rotBaseY));
    m_animSlotSel = (reinterpret_cast<s8*>(&m_shieldNodeFlags) + 1)
        [(fabs(rotDelta) <= DOUBLE_803303e8) ? 0 : 1];
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
    self.capsuleOffset.y = sZeroFloat;
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
        info.capsuleOffset.y = sZeroFloat;
        info.capsuleOffset.z = other->m_bodyEllipsoidOffset * -cosf(other->m_rotBaseY);
        PSVECAdd(&info.basePos, &info.capsuleOffset, &info.capsulePos);

        const float capsuleDistance = PSVECDistance(&self.capsulePos, &info.capsulePos);
        if ((sZeroFloat == capsuleDistance)
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
                const float hitRot = atan2f(dir.x, dir.z);
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
            && (sZeroFloat < m_bodyEllipsoidRadius)
            && (sZeroFloat < other->m_bodyEllipsoidRadius)) {
            if (((m_weaponNodeFlagBits.m_attached == 0) || (m_attachOwner != other))
                && ((other->m_weaponNodeFlagBits.m_attached == 0) || (other->m_attachOwner != this))) {
                const int usePushTimers = ((m_objectFlags & 0x40) != 0) && ((other->m_objectFlags & 0x40) != 0);
                const float bodyDistanceLimit = m_bodyEllipsoidRadius + other->m_bodyEllipsoidRadius;

                if (capsuleDistance < bodyDistanceLimit) {
                    if (usePushTimers
                        && ((sZeroFloat != m_groundHitOffset.x) || (sZeroFloat != m_groundHitOffset.z)
                            || (sZeroFloat != other->m_groundHitOffset.x) || (sZeroFloat != other->m_groundHitOffset.z))) {
                        keepPushTimer = true;
                    }

                    if (!usePushTimers || (m_collisionPushTimerMax != 0) || (other->m_collisionPushTimerMax == 0)) {
                        const float thisPush = static_cast<float>(m_pushParamA + m_pushParamB);
                        const float otherPush = static_cast<float>(other->m_pushParamA + other->m_pushParamB);
                        const float rawSplit = 0.5f + (thisPush - otherPush) / 50.0f;
                        float split;
                        if (rawSplit < sZeroFloat) {
                            split = sZeroFloat;
                        } else if (sAnimFrameOffset < rawSplit) {
                            split = sAnimFrameOffset;
                        } else {
                            split = rawSplit;
                        }

                        Vec& delta = scratch;
                        Vec scaledDelta;
                        PSVECSubtract(&self.capsulePos, &info.capsulePos, &delta);
                        PSVECScale(&delta, &delta, (bodyDistanceLimit - capsuleDistance) / bodyDistanceLimit);
                        PSVECScale(&delta, &scaledDelta, sAnimFrameOffset - split);
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
 * Address:	TODO
 * Size:	TODO
 */
#pragma push
#pragma opt_common_subs off
void CGObject::bgCollision()
{
    m_stateFlags0Bits.unk0 = 0;
    m_stateFlags0Bits.unk1 = 0;

    *reinterpret_cast<int*>(&m_radiusCtrl.x) = 0;
    m_gravityY = sZeroFloat;

    bgAttribCollision();

    if (m_bgColMask & 0x01)
    {
        s_bitMask.m_fields.m_drawFlags = 1;

        if (Game.m_currentMapId == 0x21)
        {
            bgWorldCollision();
        }
        else
        {
            bgNormalCollision();
        }

        s_bitMask.m_fields.m_drawFlags = 0;
    }
}
#pragma pop

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

    if ((sZeroFloat == m_groundHitOffset.x) && (sZeroFloat == m_groundHitOffset.y) && (sZeroFloat == m_groundHitOffset.z)) {
        return;
    }

    Vec move = m_groundHitOffset;
    move.y = sZeroFloat;
    Vec pos = m_worldPosition;
    pos.y += sStepProbeHeight + m_capsuleHalfHeight;

    unsigned int retry = 4;
    const double epsilon = DOUBLE_80330400;
    while (retry != 0) {
        CMapCylinder bodyCylinder(sHugeCylinderExtent, sNegHugeCylinderExtent);
        bodyCylinder.m_bottom = pos;
        bodyCylinder.m_axis = move;
        bodyCylinder.m_radius = m_capsuleHalfHeight;

        if (MapMng.CheckHitCylinderNear(&bodyCylinder, &move, m_bgHitMask) == 0) {
            break;
        }

        m_stateFlags0Bits.unk1 = 1;
        MapMng.m_hitMapObj->CalcHitSlide(&move, sJumpLift);

        if (fabs(static_cast<double>(move.x)) < epsilon) {
            move.x = sZeroFloat;
        }
        if (fabs(static_cast<double>(move.y)) < epsilon) {
            move.y = sZeroFloat;
        }
        if (fabs(static_cast<double>(move.z)) < epsilon) {
            move.z = sZeroFloat;
        }

        --retry;
    }

    if (retry == 0) {
        m_groundHitOffset.z = sZeroFloat;
        m_groundHitOffset.y = sZeroFloat;
        m_groundHitOffset.x = sZeroFloat;
        return;
    }

    PSVECAdd(&pos, &move, &pos);
    move.x = sZeroFloat;
    move.y = m_groundHitOffset.y - sStepProbeHeight;
    move.z = sZeroFloat;

    CMapCylinder stepCylinder(sHugeCylinderExtent, sNegHugeCylinderExtent);
    stepCylinder.m_bottom = pos;
    stepCylinder.m_axis.x = sZeroFloat;
    stepCylinder.m_axis.z = sZeroFloat;
    stepCylinder.m_axis.y = move.y;
    stepCylinder.m_radius = m_capsuleHalfHeight;

    if (MapMng.CheckHitCylinderNear(&stepCylinder, &move, m_bgHitMask) == 0) {
        goto stepMiss;
    }

    if ((MapMng.GetMapIdGrpArray()[gMapHitFace->m_groupIndex].m_mask & 0x20) == 0) {
        m_stateFlags0Bits.unk0 = 1;
        *reinterpret_cast<u32*>(&m_radiusCtrl.x) =
            MapMng.GetMapIdGrpArray()[gMapHitFace->m_groupIndex].m_mask;
        const int groupIndex = gMapHitFace->m_groupIndex;
        if (groupIndex != 0) {
            *reinterpret_cast<char*>(&m_lastBgGroup) = static_cast<char>(groupIndex);
        }
        MapMng.m_hitMapObj->GetHitFaceNormal(&HitFaceNormal());
    }

    if (MapMng.m_hitMapObj->CalcHitSlide(&move, sBgAttrNormal) != 0) {
        CMapCylinder hitCylinder(sHugeCylinderExtent, sNegHugeCylinderExtent);
        hitCylinder.m_bottom = pos;
        hitCylinder.m_axis = move;
        hitCylinder.m_radius = m_capsuleHalfHeight;

        if (MapMng.CheckHitCylinderNear(&hitCylinder, &move, m_bgHitMask) != 0) {
            Vec hitPos;
            MapMng.m_hitMapObj->CalcHitPosition(&hitPos);
            PSVECSubtract(&hitPos, &pos, &move);
        }
    }

    pos.y -= m_capsuleHalfHeight;
    PSVECAdd(&pos, &move, &pos);

    if (!(m_jumpLandingDampening > sZeroFloat) || !(m_groundHitOffset.y < sLandingDampenCutoff)) {
        goto simple;
    }

    float oldY = (m_groundHitOffset.y < sMinGroundClamp) ? sMinGroundClamp : m_groundHitOffset.y;
    float clampedY = (m_groundHitOffset.y < sMinGroundClamp) ? sMinGroundClamp : m_groundHitOffset.y;

    float delta = oldY - move.y;
    m_worldPosition.y = pos.y;
    m_gravityY = m_jumpLandingDampening * -((clampedY - delta) + delta);
    m_groundHitOffset.y = sZeroFloat;
    m_groundHitOffset.x = pos.x - m_worldPosition.x;
    m_groundHitOffset.z = pos.z - m_worldPosition.z;

    if (((m_displayFlags & 1) != 0) && (m_weaponNodeFlagBits.m_attached == 0)) {
        Sound.PlaySe3D(
            0x26,
            &m_worldPosition,
            sCrossCheckOuterRadius + (sCrossCheckOuterRadius * m_gravityY) / sStepProbeHeight,
            sHitProbeHeight + (sHitProbeHeight * m_gravityY) / sStepProbeHeight,
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
 * PAL Address: 0x800804a4
 * PAL Size: 560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::bgWorldCollision()
{
    CVector groundOffset(m_groundHitOffset);
    CVector worldPosition(m_worldPosition);
    CVector radialSum;
    PSVECAdd(reinterpret_cast<Vec*>(&worldPosition), reinterpret_cast<Vec*>(&groundOffset),
             reinterpret_cast<Vec*>(&radialSum));

    Vec radial;
    radial.x = radialSum.x;
    radial.y = radialSum.y;
    radial.z = radialSum.z;

    if (PSVECMag(&radial) > sZeroFloat) {
        reinterpret_cast<CVector*>(&radial)->Normalize();
    }
    PSVECScale(&radial, &radial, sPushDistance);

    CVector reverseRadial(-radial.x, -radial.y, -radial.z);
    CVector scaledHitMove;
    PSVECScale(reinterpret_cast<Vec*>(&reverseRadial), reinterpret_cast<Vec*>(&scaledHitMove), sHitMoveScale);
    Vec hitMove;
    hitMove.x = scaledHitMove.x;
    hitMove.y = scaledHitMove.y;
    hitMove.z = scaledHitMove.z;

    CMapCylinder bodyCylinder(sHugeCylinderExtent, sNegHugeCylinderExtent);
    bodyCylinder.m_bottom = radial;
    bodyCylinder.m_axis.x = scaledHitMove.x;
    bodyCylinder.m_axis.y = scaledHitMove.y;
    bodyCylinder.m_axis.z = scaledHitMove.z;
    bodyCylinder.m_radius = sZeroFloat;

    const u32 hitMask = m_bgHitMask;
    if (MapMng.CheckHitCylinderNear(&bodyCylinder, &hitMove, hitMask) == 0) {
        return;
    }

    MapMng.m_hitMapObj->CalcHitPosition(&radial);
    CVector hitWorldPosition(m_worldPosition);
    CVector newOffset;
    PSVECSubtract(&radial, reinterpret_cast<Vec*>(&hitWorldPosition), reinterpret_cast<Vec*>(&newOffset));
    m_groundHitOffset.x = newOffset.x;
    m_groundHitOffset.y = newOffset.y;
    m_groundHitOffset.z = newOffset.z;

    if ((MapMng.GetMapIdGrpArray()[gMapHitFace->m_groupIndex].m_mask & 0x20) == 0) {
        m_stateFlags0Bits.unk0 = 1;
        *reinterpret_cast<u32*>(&m_radiusCtrl.x) =
            MapMng.GetMapIdGrpArray()[gMapHitFace->m_groupIndex].m_mask;
        const int groupIndex = gMapHitFace->m_groupIndex;
        if (groupIndex != 0) {
            *reinterpret_cast<char*>(&m_lastBgGroup) = static_cast<char>(groupIndex);
        }
        MapMng.m_hitMapObj->GetHitFaceNormal(&HitFaceNormal());
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
#pragma push
#pragma opt_common_subs off
void CGObject::bgAttribCollision()
{
    if (!HasLoadedModel(m_charaModelHandle)) {
        return;
    }

    m_shieldNodeFlagBits.m_bit20 = 0;

    if ((m_displayFlags & 4) != 0) {
        CVector probeMove(sZeroFloat, sDownProbeDistance, sZeroFloat);
        CVector probeBase(m_worldPosition.x, m_worldPosition.y + sHitProbeHeight, m_worldPosition.z);

        CMapCylinder charmCylinder(sHugeCylinderExtent, sNegHugeCylinderExtent);
        charmCylinder.m_bottom = probeBase;
        charmCylinder.m_axis = probeMove;
        charmCylinder.m_radius = sZeroFloat;

        if (MapMng.CheckHitCylinderNear(
                &charmCylinder, reinterpret_cast<Vec*>(&probeMove),
                0x80000000) != 0) {
            Vec hitPos;
            MapMng.m_hitMapObj->CalcHitPosition(&hitPos);
            m_bgCharmFactor = m_worldPosition.y - hitPos.y;
            m_shieldNodeFlagBits.m_bit20 = 1;
        }
    }

    if (m_weaponNodeFlagBits.m_attached) {
        m_bgAttrValue = m_attachOwner->m_bgAttrValue;
        return;
    }

    {
        if ((sZeroFloat != m_groundHitOffset.x) || (sZeroFloat != m_groundHitOffset.z)) {
            const bool hasModel =
                (m_charaModelHandle != (CCharaPcs::CHandle*)0) &&
                (m_charaModelHandle->m_model != (CChara::CModel*)0);
            if (hasModel) {
                CVector probeMove(sZeroFloat, sDownProbeDistance, sZeroFloat);
                CVector probeBase(m_worldPosition.x, m_worldPosition.y + sStepProbeHeight, m_worldPosition.z);

                CMapCylinder attrCylinder(sHugeCylinderExtent, sNegHugeCylinderExtent);
                attrCylinder.m_bottom.x = probeBase.x;
                attrCylinder.m_bottom.y = probeBase.y;
                attrCylinder.m_bottom.z = probeBase.z;
                attrCylinder.m_axis.x = probeMove.x;
                attrCylinder.m_axis.y = probeMove.y;
                attrCylinder.m_axis.z = probeMove.z;
                attrCylinder.m_radius = sZeroFloat;

                if (MapMng.CheckHitCylinderNear(
                        &attrCylinder, reinterpret_cast<Vec*>(&probeMove),
                        0x78000000) != 0) {
                    switch (gMapHitFace->m_groupIndex - 0x28) {
                    case 0:
                        m_bgAttrValue = sBgAttrSlow;
                        break;
                    case 1:
                        m_bgAttrValue = sBgAttrNormal;
                        break;
                    case 2:
                        m_bgAttrValue = sBgAttrFast;
                        break;
                    case 3:
                        m_bgAttrValue = sZeroFloat;
                        break;
                    default:
                        break;
                    }
                } else {
                    m_bgAttrValue = sAnimFrameOffset;
                }
            }
        }
    }
}
#pragma pop

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
        AttackCol* attack = &m_attackColliders[i];
        const int node = attack->m_nodeIndex;
        u8* const modelNodes =
            *reinterpret_cast<u8**>(reinterpret_cast<u8*>(m_charaModelHandle->m_model) + 0xA8);
        PSMTXMultVec(reinterpret_cast<const float (*)[4]>(modelNodes + node * 0xC0 + 0x6C),
                     reinterpret_cast<Vec*>(&attack->m_localStart.y),
                     reinterpret_cast<Vec*>(&attack->m_worldPosition.y));
        PSVECAdd(reinterpret_cast<Vec*>(&attack->m_worldPosition.y), &m_worldPosition,
                 reinterpret_cast<Vec*>(&attack->m_worldPosition.y));
    }

    for (int i = 0; i < 8; i++) {
        DamageCol* damage = &m_damageColliders[i];
        const int node = damage->m_nodeIndex;
        u8* const modelNodes =
            *reinterpret_cast<u8**>(reinterpret_cast<u8*>(m_charaModelHandle->m_model) + 0xA8);
        PSMTXMultVec(reinterpret_cast<const float (*)[4]>(modelNodes + node * 0xC0 + 0x6C),
                     reinterpret_cast<Vec*>(&damage->m_localPosition.y),
                     reinterpret_cast<Vec*>(&damage->m_worldPosition.y));
        PSVECAdd(reinterpret_cast<Vec*>(&damage->m_worldPosition.y), &m_worldPosition,
                 reinterpret_cast<Vec*>(&damage->m_worldPosition.y));
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

        const float zero = sZeroFloat;

        for (int attackIndex = 0; attackIndex < 8; attackIndex++) {
            AttackCol* attack = &m_attackColliders[attackIndex];
            if (attack->m_hitMask == 0) {
                continue;
            }

            for (int damageIndex = 0; damageIndex < 8; damageIndex++) {
                DamageCol* damage = &other->m_damageColliders[damageIndex];
                if (((attack->m_hitMask & damage->m_hitMask) == 0) ||
                    (zero == damage->m_innerRadius) ||
                    (zero == damage->m_outerRadius)) {
                    continue;
                }

                Vec attackVec;
                Vec hitPos;
                PSVECSubtract(&attack->m_worldPosition, &attack->m_localEnd, &attackVec);
                if (CrossCheckSphereVector__5CMathFP3VecPfP3VecP3VecP3Vecf(
                        &Math, &hitPos, 0, &attack->m_localEnd, &attackVec,
                        reinterpret_cast<Vec*>(&damage->m_worldPosition.y),
                        attack->m_radius2, damage->m_innerRadius, damage->m_outerRadius) == 0) {
                    continue;
                }

                if ((static_cast<unsigned short>(GetCID()) & 0x2D) == 0x2D) {
                    CFlatRuntime::CStack stackIn[7];
                    stackIn[0].m_word = static_cast<u32>(attackIndex);
                    stackIn[1].m_word = static_cast<u32>(other->m_particleId);
                    stackIn[2].m_word = static_cast<u32>(damageIndex);
                    *reinterpret_cast<float*>(&stackIn[3].m_word) = hitPos.x;
                    *reinterpret_cast<float*>(&stackIn[4].m_word) = hitPos.y;
                    *reinterpret_cast<float*>(&stackIn[5].m_word) = hitPos.z;
                    stackIn[6].m_word = reinterpret_cast<u32>(m_scriptHandle);
                    CFlatRuntime::CStack stackOut;
                    gCFlatRuntime().SystemCall(this, 2, 0x13, 7, stackIn, &stackOut);
                    const int hitResult = onHit(attackIndex, other, damageIndex, &hitPos);
                    if (hitResult == 1) {
                        continue;
                    }
                    if (hitResult == 2) {
                        break;
                    }
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8007e698
 * PAL Size: 6216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::update()
{
    const unsigned int dbgFlags = DbgMenuPcs.GetDbgFlagsRaw();
    const int miniGameModelPass = (static_cast<unsigned int>(__cntlzw(dbgFlags & 0x8000)) >> 5) & 0xFF;
    unsigned char& weaponFlagsLo = m_weaponNodeFlagBytes.m_flags0;
    unsigned char& weaponFlagsHi = m_weaponNodeFlagBytes.m_flags1;
    unsigned char& shieldFlagsLo = *reinterpret_cast<unsigned char*>(&m_shieldNodeFlags);
    unsigned char& shieldFlagsHi = *(reinterpret_cast<unsigned char*>(&m_shieldNodeFlags) + 1);

    int dispItemTimer = static_cast<signed char>(m_dispItemTimer) - 1;
    m_dispItemTimer = dispItemTimer & ~(dispItemTimer >> 31);

    if (HasLoadedModel(m_charaModelHandle)) {
        for (int i = 0; i < 8; i++) {
            AttackCol* attack = &m_attackColliders[i];
            attack->m_localEnd.y = attack->m_worldPosition.y;
            attack->m_localEnd.z = attack->m_worldPosition.z;
            attack->m_worldPosition.x = attack->m_radius;
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
            float frame = sZeroFloat;
            if (m_lastBgAttr < sZeroFloat) {
                const float animStart = ModelAnimStart(m_charaModelHandle->m_model);
                frame = ModelAnimEnd(m_charaModelHandle->m_model) - animStart;
            }
            m_turnSpeed = frame;
            m_charaModelHandle->m_model->SetFrame(m_turnSpeed);
        }

        m_shieldNodeFlagBits.m_bit08 = 0;
    }

    PSVECAdd(&m_worldPosition, &m_groundHitOffset, &m_worldPosition);

    float turnDelta = Math.DstRot(m_rotTargetY, m_rotBaseY);
    float turnFactor;
    if (m_animSlotSel != -1 && m_shieldNodeFlagBits.m_bit40) {
        const double turnLimit = fabs(m_turnBaseSpeed);
        double clampedTurn = (turnDelta < -turnLimit)
                                 ? -turnLimit
                                 : (turnLimit < turnDelta ? turnLimit : turnDelta);
        turnDelta = clampedTurn;
        turnFactor = sAnimFrameOffset;
    } else {
        turnFactor = m_hitNormal.x;
    }
    m_rotBaseY += turnDelta * turnFactor;

    Mtx modelMtx;
    Mtx ecScratch;
    if (Game.m_currentMapId == 0x21) {
        Mtx tempMtx;
        Vec worldNorm;

        PSMTXRotRad(modelMtx, 'y', atan2f(m_worldPosition.x, m_worldPosition.z));
        Vec mapUp = DAT_801D9B88;
        PSVECNormalize(&m_worldPosition, &worldNorm);
        PSMTXRotRad(tempMtx, 'x', acosf(PSVECDotProduct(&worldNorm, &mapUp)));
        PSMTXConcat(modelMtx, tempMtx, modelMtx);

        PSMTXRotRad(tempMtx, 'y', m_rotBaseY);
        PSMTXConcat(modelMtx, tempMtx, modelMtx);
        PSMTXScaleApply(modelMtx, modelMtx, m_rotationX, m_rotationY, m_rotationZ);
        modelMtx[0][3] = m_worldPosition.x;
        modelMtx[1][3] = m_worldPosition.y;
        modelMtx[2][3] = m_worldPosition.z;
    } else {
        GObjectSRT srt;
        srt.m_scale.x = sAnimFrameOffset;
        srt.m_scale.y = sAnimFrameOffset;
        srt.m_scale.z = sAnimFrameOffset;
        srt.m_trans.x = sZeroFloat;
        srt.m_trans.y = sZeroFloat;
        srt.m_trans.z = sZeroFloat;
        srt.m_rot.x = sZeroFloat;
        srt.m_rot.y = sZeroFloat;
        srt.m_rot.z = sZeroFloat;
        srt.m_trans = m_worldPosition;
        PSVECAdd(&srt.m_trans, &m_extraMoveVec, &srt.m_trans);

        srt.m_rot.x = m_rotBaseX;
        srt.m_rot.y = m_rotBaseY;
        srt.m_rot.z = m_rotBaseZ;
        srt.m_scale.x = m_rotationX;
        srt.m_scale.y = m_rotationY;
        srt.m_scale.z = m_rotationZ;

        if (m_worldParamA == 0x20 || m_worldParamA == 0x13 || m_worldParamA == 0x15 ||
            m_worldParamA == 0x16 || m_worldParamA == 0x17 || m_worldParamA == 0x14) {
            const float wobbleBias = m_worldParamA == 0x20 ? 0.3f : 0.05f;
            m_radiusCtrl.z += 0.8f * m_radiusCtrl.y + wobbleBias;
            m_radiusCtrl.y *= 0.95f;
            srt.m_rot.y += m_radiusCtrl.z;
        } else if (m_worldParamA == 0x24 || m_worldParamB == 0x125) {
            const float cameraYaw = CameraPcs.m_yaw;
            srt.m_rot.y = 3.1415927f - cameraYaw;
            srt.m_rot.y += sBgAttrNormal * cosf(sBgAttrNormal * m_radiusCtrl.y);
            srt.m_trans.y += sAnimFrameOffset + sinf(m_radiusCtrl.y);
            m_radiusCtrl.y += 0.1f;
        }

        Math.SRTToMatrix(modelMtx, reinterpret_cast<SRT*>(&srt));

        Mtx rotScratch;
        if (m_stateFlags0Bits.unk3) {
            Mtx tiltMtx;
            if (m_groundHitOffset.x != sZeroFloat || m_groundHitOffset.z != sZeroFloat) {
                Vec axis;
                const float slideMagSq =
                    m_groundHitOffset.x * m_groundHitOffset.x + m_groundHitOffset.z * m_groundHitOffset.z;
                const float slideMag = sqrtf(slideMagSq);
                CVector worldUp(sZeroFloat, sAnimFrameOffset, sZeroFloat);
                PSVECCrossProduct(&m_groundHitOffset, worldUp, &axis);
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
            CVector tiltZero0(sZeroFloat, sZeroFloat, sZeroFloat);
            modelMtx[0][3] = tiltZero0.x;
            CVector tiltZero1(sZeroFloat, sZeroFloat, sZeroFloat);
            modelMtx[1][3] = tiltZero1.y;
            CVector tiltZero2(sZeroFloat, sZeroFloat, sZeroFloat);
            modelMtx[2][3] = tiltZero2.z;
            PSMTXConcat(tiltMtx, modelMtx, modelMtx);
            modelMtx[0][3] = tx;
            modelMtx[1][3] = ty;
            modelMtx[2][3] = tz;
        } else if ((m_objectFlags & 0x90) != 0 && m_stateFlags0Bits.unk0) {
            if (m_groundHitOffset.x != sZeroFloat || m_groundHitOffset.z != sZeroFloat) {
                m_radiusCtrl.y += 0.2f * m_groundHitOffset.x;
                m_radiusCtrlVel.x += 0.2f * m_groundHitOffset.z;
            }

            const float swayDx = m_radiusCtrlVel.x - m_groundFriction;
            const float swayDz = m_radiusCtrl.y - m_radiusCtrlVel.y;
            m_radiusCtrlVel.y += sBgAttrNormal * swayDz;
            m_groundFriction += sBgAttrNormal * swayDx;

            Vec swayDir;
            PSVECNormalize(reinterpret_cast<Vec*>(&m_radiusCtrlVel.y), &swayDir);
            CVector swayUp(sZeroFloat, sAnimFrameOffset, sZeroFloat);
            const float swayDot = PSVECDotProduct(&swayDir, swayUp);
            if (swayDot < 0.9999f) {
                const float swayAngle = acosf(swayDot);
                CVector swayAxisUp(sZeroFloat, sAnimFrameOffset, sZeroFloat);
                Vec swayAxis;
                PSVECCrossProduct(&swayDir, swayAxisUp, &swayAxis);
                PSMTXRotAxisRad(rotScratch, &swayAxis, -swayAngle);

                const float mtx0 = modelMtx[0][3];
                const float mtx1 = modelMtx[1][3];
                const float mtx2 = modelMtx[2][3];
                CVector swayZero0(sZeroFloat, sZeroFloat, sZeroFloat);
                modelMtx[0][3] = swayZero0.x;
                CVector swayZero1(sZeroFloat, sZeroFloat, sZeroFloat);
                modelMtx[1][3] = swayZero1.y;
                CVector swayZero2(sZeroFloat, sZeroFloat, sZeroFloat);
                modelMtx[2][3] = swayZero2.z;
                PSMTXConcat(rotScratch, modelMtx, modelMtx);
                const float swayTan = tan(-swayAngle);
                const float swayTanScaled = 2.0f * swayTan;
                modelMtx[0][3] = mtx0;
                modelMtx[2][3] = mtx2;
                modelMtx[1][3] = mtx1 - swayTanScaled;
            }

            float swayClamp = swayDot < sAnimFrameOffset ? swayDot : sAnimFrameOffset;
            swayClamp = swayClamp < sZeroFloat ? sZeroFloat : swayClamp;
            const float swaySin = sinf(swayClamp);
            const float swayCos = cosf(swayClamp);
            const float swayRy = m_radiusCtrl.y;
            const float swayRx = m_radiusCtrlVel.x;
            m_radiusCtrl.y = swayCos * swayRy - swaySin * swayRx;
            m_radiusCtrlVel.x = swaySin * swayRy + swayCos * swayRx;
            m_radiusCtrl.y *= 0.9f;
            m_radiusCtrlVel.x *= 0.9f;
        }
    }

    if (m_weaponNodeFlagBits.m_attached) {
        CChara::CModel* ownerModel = m_attachOwner->m_charaModelHandle->m_model;
        PSMTXCopy(ModelNodeMtx(ownerModel, m_attachNode), modelMtx);

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
            float interp = static_cast<float>(m_moveMode) / static_cast<float>(m_moveModePrevious);
            Vec fromOwner;
            Vec fromSelf;
            PSVECScale(&attachPos, &fromOwner, sAnimFrameOffset - interp);
            PSVECScale(&m_worldPosition, &fromSelf, interp);
            PSVECAdd(&fromOwner, &fromSelf, &m_worldPosition);
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
                targetNodeY = ModelNodeMtx(m_lookAtTarget->m_charaModelHandle->m_model, m_lookAtTargetNodeIndex)[1][3];
            }
            lookDelta.y += unk_0x184 - targetNodeY;

            const float lookDistance = PSVECMag(&lookDelta);
            if (lookDistance > sZeroFloat) {
                const float targetYaw = atan2f(-lookDelta.x, -lookDelta.z);
                const float yawDelta = Math.DstRot(targetYaw, m_rotBaseY);
                if (fabs(yawDelta) < 1.5707964f) {
                    const float pitchDelta = atan2f(lookDelta.y, lookDistance);
                    if (fabs(pitchDelta) < 0.78539819f) {
                        lookYaw += yawDelta;
                        lookPitch += pitchDelta;
                    }
                }
            }
        }

        const unsigned char lookBlendByte = *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x56);
        float lookBlend = 0.001f * static_cast<float>(lookBlendByte);
        CChara::CModel* chestModel = m_charaModelHandle->m_model;
        const float chestAmp = ModelChestAmp(chestModel);
        const float chestTilt = ModelChestTilt(chestModel);
        ModelChestAmp(chestModel) = lookBlend * (lookYaw - chestAmp) + chestAmp;
        ModelChestTilt(chestModel) = lookBlend * (lookPitch - chestTilt) + chestTilt;
        ModelTwistAngle(m_charaModelHandle->m_model) +=
            sBgAttrFast * (*reinterpret_cast<float*>(m_worldMode) - ModelTwistAngle(m_charaModelHandle->m_model));

        m_charaModelHandle->m_model->SetMatrix(modelMtx);

        Vec windVec;
        Wind.Calc(&windVec, &m_worldPosition, 0);
        windVec.x = -(m_groundHitOffset.x * Math.RandF() - windVec.x);
        windVec.z = -(m_groundHitOffset.z * Math.RandF() - windVec.z);
        CChara::CModel* windModel = m_charaModelHandle->m_model;
        CVector windCopy(windVec);
        ModelWindVector(windModel).x = windCopy.x;
        ModelWindVector(windModel).y = windCopy.y;
        ModelWindVector(windModel).z = windCopy.z;

        boundCheck();

        float visibleScale = sAnimFrameOffset;
        if (Game.m_currentMapId == 0x21) {
            visibleScale = m_screenDepth > 10000.0f ? sZeroFloat : sAnimFrameOffset;
        } else {
            visibleScale = m_screenDepth > 750.0f ? sZeroFloat : sAnimFrameOffset;
        }

        const float alphaTarget = m_stepSlopeLimit * onAlphaUpdate() * visibleScale;
        const float alphaStep = ClampFloat(alphaTarget - m_lookAtTimer, -m_bgDownDist, m_bgDownDist);
        m_lookAtTimer = ClampFloat(m_lookAtTimer + alphaStep, sZeroFloat, sAnimFrameOffset);
        m_worldParam = m_worldParam > 0.05f ? m_worldParam - 0.05f : sZeroFloat;
        if ((m_displayFlags & 0x1000) != 0) {
            m_lookAtTimer = alphaTarget;
        }

        if (m_lookAtTimer == sZeroFloat) {
            m_weaponNodeFlagBits.m_unk20 = 0;
        }
        m_weaponNodeFlagBits.m_unk40 =
            (static_cast<s32>(static_cast<s32>(weaponFlagsLo) << 25 | static_cast<u32>(weaponFlagsLo) >> 7) |
             static_cast<s32>(static_cast<u32>(weaponFlagsLo) << 26 | static_cast<u32>(weaponFlagsLo) >> 6)) < 0;

        if ((m_displayFlags & 1) != 0) {
            if ((static_cast<s32>(static_cast<u32>(weaponFlagsLo) << 26 | static_cast<u32>(weaponFlagsLo) >> 6) < 0 &&
                 miniGameModelPass == 0) ||
                m_currentAnimSlot != -1 || m_animSlotSel != static_cast<signed char>(shieldFlagsHi)) {
                m_charaModelHandle->m_model->CalcMatrix();
            }
            if (m_weaponNodeFlagBits.m_unk04 &&
                miniGameModelPass == 0) {
                m_charaModelHandle->m_model->CalcSkin();
            }

            ModelLightAlpha(m_charaModelHandle->m_model) = m_lookAtTimer;
            m_charaModelHandle->m_model->m_flagsA0Bits.m_flagA0_20 =
                static_cast<s32>(static_cast<s32>(weaponFlagsLo) << 26 | static_cast<u32>(weaponFlagsLo) >> 6) < 0;
            m_charaModelHandle->m_model->m_flagsA0Bits.m_flagA0_80 = (m_displayFlags & 0x20) != 0;
        }

        m_charaModelHandle->m_model->CalcFurColor();

        if ((m_displayFlags & 2) != 0) {
            float frameStep;
            if (m_animSlotSel != -1 && (shieldFlagsLo & 0x40) != 0) {
                if (ModelAnim(m_charaModelHandle->m_model) != 0) {
                    const unsigned short frameCount = *reinterpret_cast<unsigned short*>(
                        reinterpret_cast<unsigned char*>(ModelAnim(m_charaModelHandle->m_model)) + 0x10);
                    frameStep = m_turnSpeed + static_cast<float>(frameCount) /
                                 static_cast<float>(*reinterpret_cast<unsigned int*>(&m_attackColliders[0].m_localStart.x));
                } else {
                    if (static_cast<unsigned int>(System.m_execParam) >= 2) {
                        System.Printf(const_cast<char*>(s_noTurnMotion));
                    }
                    frameStep = m_turnSpeed + sAnimFrameOffset;
                }
            } else {
                float frameDelta = m_lastBgAttr;
                const int activeAnimIndex = m_charaModelHandle->m_currentAnimIndex;
                if (activeAnimIndex >= 0 &&
                    (*reinterpret_cast<unsigned int*>(
                         reinterpret_cast<unsigned char*>(m_charaModelHandle->m_animSlot[activeAnimIndex]) + 0x70) &
                     0x4) != 0) {
                    frameDelta = m_lastBgAttr < sZeroFloat ? sNegativeOne : sAnimFrameOffset;
                }
                frameStep = m_turnSpeed + frameDelta * 1.2f;
            }

            const float prevTime = m_charaModelHandle->m_model->m_time;
            m_charaModelHandle->m_model->SetFrame(frameStep);

            const int activeAnimIndex = m_charaModelHandle->m_currentAnimIndex;
            if (activeAnimIndex >= 0 && m_charaModelHandle->m_animSlot[activeAnimIndex] != 0) {
                unsigned char* animRefBytes =
                    reinterpret_cast<unsigned char*>(m_charaModelHandle->m_animSlot[activeAnimIndex]);
                const unsigned short pointCount = *reinterpret_cast<short*>(animRefBytes + 0x2C);
                if (pointCount > 0) {
                    const float animSpan =
                        sAnimFrameOffset + (ModelAnimEnd(m_charaModelHandle->m_model) - ModelAnimStart(m_charaModelHandle->m_model));
                    float prevWrapped = WrapAnimFrame(prevTime, animSpan);
                    float nextWrapped = WrapAnimFrame(frameStep, animSpan);
                    if (frameStep < prevTime) {
                        prevWrapped = (animSpan - sAnimFrameOffset) - prevWrapped;
                        nextWrapped = (animSpan - sAnimFrameOffset) - nextWrapped;
                    }

                    for (int i = 0; i < pointCount; i++) {
                        const unsigned short pointFrame = *reinterpret_cast<unsigned short*>(animRefBytes + 0x30 + i * 4);
                        const float eventFrame = static_cast<float>(pointFrame) + ModelAnimStart(m_charaModelHandle->m_model);
                        if (prevWrapped < eventFrame && (eventFrame <= nextWrapped || nextWrapped < prevWrapped)) {
                            CFlatRuntime::CStack stackIn[2];
                            stackIn[0].m_word = static_cast<unsigned int>(m_animSlotSel);
                            stackIn[1].m_word = static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(animRefBytes + 0x32 + i * 4));
                            gCFlatRuntime().SystemCall(this, 2, 9, 2, stackIn, 0);
                            onAnimPoint(m_animSlotSel, *reinterpret_cast<unsigned short*>(animRefBytes + 0x32 + i * 4));
                        }
                    }
                }
            }

            m_turnSpeed = frameStep;
        }

        if (m_currentAnimSlot != -1 && !m_weaponNodeFlagAll.m_bits1.m_bit01) {
            bool animFinished = HasLoadedModel(m_charaModelHandle);
            if (animFinished && m_currentAnimSlot != -1) {
                if (ModelAnim(m_charaModelHandle->m_model) == 0) {
                    animFinished = true;
                } else {
                    const float animSpan = sAnimFrameOffset + (ModelAnimEnd(m_charaModelHandle->m_model) - ModelAnimStart(m_charaModelHandle->m_model));
                    if (animSpan == sAnimFrameOffset) {
                        animFinished = true;
                    } else if (m_lastBgAttr < sZeroFloat) {
                        animFinished = ModelTime(m_charaModelHandle->m_model) <= sZeroFloat;
                    } else {
                        animFinished = animSpan - sAnimFrameOffset < ModelTime(m_charaModelHandle->m_model);
                    }
                }
            } else {
                animFinished = true;
            }

            if (animFinished) {
                if (m_shieldNodeFlagBits.m_bit80) {
                    const unsigned char queuePos = m_animQueuePos++;
                    const char queuedAnim = m_animQueue[queuePos];
                    if (queuedAnim != -1) {
                        m_currentAnimSlot =
                            (queuedAnim >= 'A' && queuedAnim < 'A' + 4) ? m_animQueue[queuedAnim - 'A'] : queuedAnim;
                        m_weaponNodeFlagAll.m_bits1.m_bit01 = 0;
                        m_animExtraIndex = -1;
                        m_collisionPushTimer = -1;
                        m_shieldNodeFlagBits.m_bit02 = 0;
                        m_shieldNodeFlagBits.m_bit80 = 0;
                        m_shieldNodeFlagBits.m_bit08 = 1;
                        m_turnSpeed = sZeroFloat;
                    } else {
                        m_currentAnimSlot = -1;
                        m_shieldNodeFlagBits.m_bit40 = 0;
                        m_turnSpeed = sZeroFloat;
                        m_rotTargetY = m_rotBaseY;
                        m_shieldNodeFlagBits.m_bit08 = 0;
                        m_shieldNodeFlagBits.m_bit80 = 0;
                        gCFlatRuntime().SystemCall(this, 2, 10, 0, 0, 0);
                    }
                } else {
                    m_currentAnimSlot = -1;
                    m_shieldNodeFlagBits.m_bit40 = 0;
                    m_turnSpeed = sZeroFloat;
                    m_rotTargetY = m_rotBaseY;
                    m_shieldNodeFlagBits.m_bit08 = 0;
                    m_shieldNodeFlagBits.m_bit80 = 0;
                    gCFlatRuntime().SystemCall(this, 2, 10, 0, 0, 0);
                }
            }
        }

        if (HasLoadedModel(m_weaponModelHandle) && (m_displayFlags & 1) != 0 && m_weaponAttachNode >= 0) {
            PSMTXCopy(ModelNodeMtx(m_charaModelHandle->m_model, m_weaponAttachNode), ecScratch);
            PSMTXTransApply(ecScratch, ecScratch, m_worldPosition.x, m_worldPosition.y, m_worldPosition.z);
            m_weaponModelHandle->m_model->SetMatrix(ecScratch);
            m_weaponModelHandle->m_model->CalcMatrix();
            if (static_cast<s32>(static_cast<u32>(weaponFlagsLo) << 26 | static_cast<u32>(weaponFlagsLo) >> 6) < 0) {
                m_weaponModelHandle->m_model->CalcSkin();
            }

            ModelLightAlpha(m_weaponModelHandle->m_model) = m_lookAtTimer;
            m_weaponModelHandle->m_model->m_flagsA0Bits.m_flagA0_20 =
                static_cast<s32>(static_cast<s32>(weaponFlagsLo) << 26 | static_cast<u32>(weaponFlagsLo) >> 6) < 0;
            m_weaponModelHandle->m_model->m_flagsA0Bits.m_flagA0_80 = (m_displayFlags & 0x20) != 0;
        }

        if (HasLoadedModel(m_shieldModelHandle) && (m_displayFlags & 1) != 0 && m_shieldAttachNodeIndex >= 0) {
            PSMTXCopy(ModelNodeMtx(m_charaModelHandle->m_model, m_shieldAttachNodeIndex), ecScratch);
            PSMTXTransApply(ecScratch, ecScratch, m_worldPosition.x, m_worldPosition.y, m_worldPosition.z);
            m_shieldModelHandle->m_model->SetMatrix(ecScratch);
            m_shieldModelHandle->m_model->CalcMatrix();

            ModelLightAlpha(m_shieldModelHandle->m_model) = m_lookAtTimer;
            m_shieldModelHandle->m_model->m_flagsA0Bits.m_flagA0_20 =
                static_cast<s32>(static_cast<s32>(weaponFlagsLo) << 26 | static_cast<u32>(weaponFlagsLo) >> 6) < 0;
            m_shieldModelHandle->m_model->m_flagsA0Bits.m_flagA0_80 = (m_displayFlags & 0x20) != 0;
            if (static_cast<s32>(static_cast<u32>(weaponFlagsLo) << 26 | static_cast<u32>(weaponFlagsLo) >> 6) < 0) {
                m_shieldModelHandle->m_model->CalcSkin();
            }
        }
    }

    m_groundHitOffset.x *= m_moveOffset.x;
    m_groundHitOffset.y *= m_moveOffset.y;
    m_groundHitOffset.z *= m_moveOffset.z;
    if (fabs(m_groundHitOffset.x) < DOUBLE_80330400) {
        m_groundHitOffset.x = sZeroFloat;
    }
    if (fabs(m_groundHitOffset.y) < DOUBLE_80330400) {
        m_groundHitOffset.y = sZeroFloat;
    }
    if (fabs(m_groundHitOffset.z) < DOUBLE_80330400) {
        m_groundHitOffset.z = sZeroFloat;
    }

    if ((m_stateFlags0 & 0x80) != 0) {
        m_groundHitOffset.x *= m_bounceFactor;
        m_groundHitOffset.z *= m_bounceFactor;
    }

    if (HasLoadedModel(m_charaModelHandle) && (ModelFlagsA0(m_charaModelHandle->m_model) & 0x40) != 0) {
        m_charaModelHandle->m_model->MogFurFrame(this);
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
    CCharaPcs::CHandle* handle = m_charaModelHandle;
    bool hasModel = false;

    if ((handle != (CCharaPcs::CHandle*)0) && (handle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }
    if (!hasModel) {
        return;
    }

    hasModel = false;
    handle->m_flags = m_displayFlags;
    m_charaModelHandle->m_colorPhase = m_animBlend;
    m_charaModelHandle->m_sortZ = m_screenDepth;
    m_charaModelHandle->m_fogBlend = m_worldParam;

    handle = m_weaponModelHandle;
    if ((handle != (CCharaPcs::CHandle*)0) && (handle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }
    if (hasModel) {
        handle->m_flags = m_displayFlags;
        m_weaponModelHandle->m_colorPhase = m_animBlend;
        m_weaponModelHandle->m_sortZ = m_screenDepth;
        m_weaponModelHandle->m_fogBlend = m_worldParam;
    }

    handle = m_shieldModelHandle;
    hasModel = false;
    if ((handle != (CCharaPcs::CHandle*)0) && (handle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }
    if (hasModel) {
        handle->m_flags = m_displayFlags;
        m_shieldModelHandle->m_colorPhase = m_animBlend;
        m_shieldModelHandle->m_sortZ = m_screenDepth;
        m_shieldModelHandle->m_fogBlend = m_worldParam;
    }

    if (m_weaponNodeFlagBits.m_unk20 == 0) {
        hasModel = false;
        m_charaModelHandle->m_flags &= 0xFFFFFFFE;

        handle = m_weaponModelHandle;
        if ((handle != (CCharaPcs::CHandle*)0) && (handle->m_model != (CChara::CModel*)0)) {
            hasModel = true;
        }
        if (hasModel) {
            handle->m_flags &= 0xFFFFFFFE;
        }

        handle = m_shieldModelHandle;
        hasModel = false;
        if ((handle != (CCharaPcs::CHandle*)0) && (handle->m_model != (CChara::CModel*)0)) {
            hasModel = true;
        }
        if (hasModel) {
            handle->m_flags &= 0xFFFFFFFE;
        }
    }

    if (m_shieldNodeFlagBits.m_bit20 == 0) {
        hasModel = false;
        m_charaModelHandle->m_flags &= 0xFFFFFFFB;

        handle = m_weaponModelHandle;
        if ((handle != (CCharaPcs::CHandle*)0) && (handle->m_model != (CChara::CModel*)0)) {
            hasModel = true;
        }
        if (hasModel) {
            handle->m_flags &= 0xFFFFFFFB;
        }

        handle = m_shieldModelHandle;
        hasModel = false;
        if ((handle != (CCharaPcs::CHandle*)0) && (handle->m_model != (CChara::CModel*)0)) {
            hasModel = true;
        }
        if (!hasModel) {
            return;
        }

        handle->m_flags &= 0xFFFFFFFB;
        return;
    }

    hasModel = false;
    m_charaModelHandle->m_bgCharmPlaneY = m_bgCharmFactor;
    m_charaModelHandle->m_worldPosY = m_worldPosition.y;

    handle = m_weaponModelHandle;
    if ((handle != (CCharaPcs::CHandle*)0) && (handle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }
    if (hasModel) {
        handle->m_bgCharmPlaneY = m_bgCharmFactor;
        m_weaponModelHandle->m_worldPosY = m_worldPosition.y;
    }

    handle = m_shieldModelHandle;
    hasModel = false;
    if ((handle != (CCharaPcs::CHandle*)0) && (handle->m_model != (CChara::CModel*)0)) {
        hasModel = true;
    }
    if (!hasModel) {
        return;
    }

    handle->m_bgCharmPlaneY = m_bgCharmFactor;
    m_shieldModelHandle->m_worldPosY = m_worldPosition.y;
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
        CColor color(0xFF, 0x00, 0x00, 0xFF);
        CVector pos(m_worldPosition.x, m_worldPosition.y + m_capsuleHalfHeight, m_worldPosition.z);
        Graphic.DrawSphere(posMtx, pos, m_capsuleHalfHeight, &color.color);
    }

    if (((CFlat.m_debugFlags & 0x2) != 0) && ((m_bgColMask & 0x2) != 0)) {
        CVector capsuleOffset;
        if (sZeroFloat != m_bodyEllipsoidOffset) {
            capsuleOffset.y = sZeroFloat;
            capsuleOffset.x = m_bodyEllipsoidOffset * -sinf(m_rotBaseY);
            capsuleOffset.z = m_bodyEllipsoidOffset * -cosf(m_rotBaseY);
        } else {
            capsuleOffset.z = sZeroFloat;
            capsuleOffset.y = sZeroFloat;
            capsuleOffset.x = sZeroFloat;
        }

        Mtx scaleMtx;
        Mtx rotMtx;
        const float r = m_bodyEllipsoidRadius;
        PSMTXScale(scaleMtx, r * m_bodyEllipsoidAspect, r, r);
        PSMTXRotRad(rotMtx, 'y', m_rotBaseY);
        PSMTXConcat(rotMtx, scaleMtx, scaleMtx);

        CVector spherePos(m_worldPosition.x, m_worldPosition.y + m_bodyEllipsoidRadius, m_worldPosition.z);
        PSVECAdd(spherePos, capsuleOffset, spherePos);

        scaleMtx[0][3] = spherePos.x;
        scaleMtx[1][3] = spherePos.y;
        scaleMtx[2][3] = spherePos.z;
        PSMTXConcat(posMtx, scaleMtx, scaleMtx);
        GXLoadPosMtxImm(scaleMtx, GX_PNMTX0);

        CColor color(0x00, 0xFF, 0x00, 0xFF);
        GXSetChanMatColor(GX_COLOR0A0, color.color);
        Graphic.DrawSphere();
    }

    if (((CFlat.m_debugFlags & 0x4) != 0) && ((m_bgColMask & 0x4) != 0)) {
        CColor color(0x00, 0x00, 0xFF, 0xFF);
        CVector pos(m_worldPosition.x, m_worldPosition.y + m_bodyColRadius, m_worldPosition.z);
        Graphic.DrawSphere(posMtx, pos, m_bodyColRadius, &color.color);
    }

    if (((CFlat.m_debugFlags & 0x8) != 0) && ((m_bgColMask & 0x8) != 0)) {
        CColor color(0xFF, 0xFF, 0x00, 0xFF);
        CVector pos(m_worldPosition.x, m_worldPosition.y + m_attackColRadius, m_worldPosition.z);
        Graphic.DrawSphere(posMtx, pos, m_attackColRadius, &color.color);
    }

    if (((CFlat.m_debugFlags & 0x10) != 0) && ((m_bgColMask & 0x10) != 0)) {
        CColor color(0x40, 0xFF, 0x40, 0xFF);
        Graphic.DrawSphere(posMtx, &m_worldPosition, m_nearColRadius, &color.color);
    }

    if (((CFlat.m_debugFlags & 0x40000) != 0) && ((m_bgColMask & 0x40000) != 0)) {
        for (unsigned int i = 0; i < 8; i++) {
            AttackCol* collider = &m_attackColliders[i];
            if (*reinterpret_cast<int*>(&collider->m_localStart.x) == 0) {
                continue;
            }

            CColor color(0xFF, 0x80, 0x80, 0xFF);
            Graphic.DrawSphere(posMtx, &collider->m_worldPosition, collider->m_radius, &color.color);

            GXLoadPosMtxImm(posMtx, GX_PNMTX0);
            GXBegin(GX_LINES, GX_VTXFMT0, 2);
            GXPosition3f32(collider->m_localEnd.y, collider->m_localEnd.z, collider->m_worldPosition.x);
            GXPosition3f32(collider->m_worldPosition.y, collider->m_worldPosition.z, collider->m_radius);
        }
    }

    if (((CFlat.m_debugFlags & 0x80000) != 0) && ((m_bgColMask & 0x80000) != 0)) {
        for (int i = 0; i < 8; i++) {
            DamageCol* collider = &m_damageColliders[i];
            if (*reinterpret_cast<int*>(&collider->m_localPosition.x) == 0) {
                continue;
            }

            CColor color(0x80, 0x80, 0xFF, 0xFF);
            CVector scale(collider->m_innerRadius, collider->m_outerRadius, collider->m_innerRadius);
            Graphic.DrawSphere(posMtx, &collider->m_worldPosition, scale, &color.color);
        }
    }
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
    if (static_cast<double>(sZeroFloat) == static_cast<double>(maxDist)) {
        return 0;
    }

    PSVECNormalize(&toTarget, &targetDir);
    const float maxAngle = static_cast<float>(atan2(static_cast<double>(radius), static_cast<double>(maxDist)));
    float bestDist = sLargeDistance;
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
        const float dist = PSVECMag(&toOther);
        if ((sZeroFloat < dist) && (dist < maxDist)) {
            float extraAngle = sZeroFloat;
            if (useBodyRadius != 0) {
                extraAngle = static_cast<float>(atan(static_cast<double>(other->m_bodyEllipsoidRadius / maxDist)));
            }
            PSVECScale(&toOther, &toOther, sAnimFrameOffset / dist);
            const float angle = static_cast<float>(acos(static_cast<double>(PSVECDotProduct(&toOther, &targetDir))));
            if ((static_cast<double>(angle) < static_cast<double>(maxAngle + extraAngle)) && (dist < bestDist)) {
                best = other;
                bestDist = dist;
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

    u8* const weaponFlagsHi = &m_weaponNodeFlagBytes.m_flags1;
    *weaponFlagsHi = static_cast<u8>(__rlwimi(*weaponFlagsHi, 1, 5, 26, 26));
    *weaponFlagsHi = static_cast<u8>(__rlwimi(*weaponFlagsHi, 1, 4, 27, 27));
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveTarget.x = sinX * cosY0;
    m_moveTarget.y = sinY;
    m_moveTarget.z = cosX * cosY1;
    m_moveTimer = moveTimer;
    *weaponFlagsHi = static_cast<u8>(__rlwimi(*weaponFlagsHi, 0, 3, 28, 28));
    *weaponFlagsHi = static_cast<u8>(__rlwimi(*weaponFlagsHi, 0, 1, 30, 30));
    *weaponFlagsHi = static_cast<u8>(__rlwimi(*weaponFlagsHi, 0, 2, 29, 29));
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
    if (sZeroFloat == mag) {
        unitVec.x = sZeroFloat;
        unitVec.y = sZeroFloat;
        unitVec.z = sZeroFloat;
    } else {
        PSVECScale(moveVec, &unitVec, sAnimFrameOffset / mag);
    }

    u8* const weaponFlagsHi = reinterpret_cast<u8*>(&m_weaponNodeFlags) + 1;
    *weaponFlagsHi = static_cast<u8>(__rlwimi(*weaponFlagsHi, 1, 5, 26, 26));
    *weaponFlagsHi = static_cast<u8>(__rlwimi(*weaponFlagsHi, 1, 4, 27, 27));
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveTarget = unitVec;
    m_moveTimer = moveTimer;
    *weaponFlagsHi = static_cast<u8>(__rlwimi(*weaponFlagsHi, 0, 3, 28, 28));
    *weaponFlagsHi = static_cast<u8>(__rlwimi(*weaponFlagsHi, 0, 1, 30, 30));
    *weaponFlagsHi = static_cast<u8>(__rlwimi(*weaponFlagsHi, 0, 2, 29, 29));
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
    if (sZeroFloat == mag) {
        unitVec.x = sZeroFloat;
        unitVec.y = sZeroFloat;
        unitVec.z = sZeroFloat;
    } else {
        PSVECScale(moveVec, &unitVec, sAnimFrameOffset / mag);
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
 * Address:	TODO
 * Size:	TODO
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
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0x98) = showParts;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetAttackCol(int hitIndex, char* nodeName, float hitMask, Vec* position)
{
    CCharaPcs::CHandle* handle = m_charaModelHandle;
    bool hasModel = false;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (hasModel) {
        int nodeIndex = handle->m_model->SearchNode(nodeName);

        m_attackColliders[hitIndex].m_nodeIndex = nodeIndex;
        m_attackColliders[hitIndex].m_hitRadius = hitMask;
        m_attackColliders[hitIndex].m_localStart.y = position->x;
        m_attackColliders[hitIndex].m_localStart.z = position->y;
        m_attackColliders[hitIndex].m_localEnd.x = position->z;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetDamageCol(int colliderIndex, char* nodeName, float hitMask, float active, Vec* position)
{
    CCharaPcs::CHandle* handle = m_charaModelHandle;
    bool hasModel = false;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (hasModel) {
        int nodeIndex = handle->m_model->SearchNode(nodeName);

        m_damageColliders[colliderIndex].m_nodeIndex = nodeIndex;
        m_damageColliders[colliderIndex].m_hitInnerRadius = hitMask;
        m_damageColliders[colliderIndex].m_hitOuterRadius = active;
        m_damageColliders[colliderIndex].m_localPosition.y = position->x;
        m_damageColliders[colliderIndex].m_localPosition.z = position->y;
        m_damageColliders[colliderIndex].m_worldPosition.x = position->z;
    }
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
    clipMtx[3][2] = sZeroFloat;
    clipMtx[3][1] = sZeroFloat;
    clipMtx[3][0] = sZeroFloat;
    clipMtx[3][3] = sAnimFrameOffset;

    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    PSMTX44Concat(screenMtx, clipMtx, screenMtx);

    if ((m_charaModelHandle != 0) && (m_charaModelHandle->m_model != 0)) {
        const float zero = sZeroFloat;
        const float oneF = sAnimFrameOffset;
        const float clipLimit = -1.0f;

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

        m_weaponNodeFlagBits.m_unk20 = static_cast<signed char>(static_cast<u32>(__cntlzw(clipMask)) >> 5);
    }

    Math.MTX44MultVec4(screenMtx, &m_worldPosition, reinterpret_cast<Vec4d*>(&m_projection.y));
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
    *reinterpret_cast<int*>(&m_attackColliders[0].m_localStart.x) = turnFrames;

    const int animSlot = (m_turnBaseSpeed < sZeroFloat) ? 2 : 3;

    m_currentAnimSlot = m_animQueue[animSlot - 0x41];
    m_weaponNodeFlagAll.m_bits1.m_bit01 = 0;
    m_animExtraIndex = -1;
    m_collisionPushTimer = -1;
    m_shieldNodeFlagBits.m_bit02 = 0;
    m_shieldNodeFlagBits.m_bit80 = 0;
    m_shieldNodeFlagBits.m_bit08 = 1;
    const float& zero = sZeroFloat;
    m_turnSpeed = zero;
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
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::SetClassWork(int ownerType, int workIndex)
{
    m_ownerType = (char)ownerType;
    m_classWorkIndex = (unsigned char)workIndex;

    switch (ownerType) {
    case 0: {
        m_scriptHandle = reinterpret_cast<void**>(&Game.m_caravanWorkArr[Game.m_gameWork.m_wmBackupParams[workIndex]]);
        m_scriptHandle[2] = reinterpret_cast<void*>(Game.m_gameWork.m_wmBackupParams[workIndex]);
        m_scriptHandle[3] = this;
        Game.m_scriptFoodBase[workIndex] = reinterpret_cast<u32>(m_scriptHandle);
        return;
    }

    case 1:
        m_scriptHandle = reinterpret_cast<void**>(&Game.m_monWorkArr[workIndex]);
        m_scriptHandle[3] = this;
        m_scriptHandle[2] = reinterpret_cast<void*>(workIndex);
        Game.m_scriptWork[0][0][workIndex] = reinterpret_cast<u32>(this);
        Game.m_scriptWork[4][0][workIndex] = reinterpret_cast<u32>(m_scriptHandle);
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
        texAnimSet = *reinterpret_cast<CTexAnimSet**>(reinterpret_cast<unsigned char*>(handle->m_model) + 0xD4);
        if (texAnimSet != (CTexAnimSet*)0) {
            const float& zero = sZeroFloat;
            texAnimSet->Change(name, zero, (CTexAnimSet::ANIM_TYPE)-2);
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
 * Address:	TODO
 * Size:	TODO
 */
#pragma push
#pragma opt_propagation off
void CGObject::InitWork(int index)
{
    typedef void (*InitWorkFn)(void**, int, unsigned int, int);
    char ownerType;

    ownerType = m_ownerType;
    switch (ownerType) {
    case 0: {
        InitWorkFn initWork = reinterpret_cast<InitWorkFn>(reinterpret_cast<void**>(*m_scriptHandle)[3]);
        initWork(m_scriptHandle, index, Game.unkCFlatData0[0] + index * 0x1D0, 0);
        break;
    }
    case 1: {
        InitWorkFn initWork = reinterpret_cast<InitWorkFn>(reinterpret_cast<void**>(*m_scriptHandle)[3]);
        initWork(m_scriptHandle, index, Game.unkCFlatData0[1] + index * 0x1D0, 0);
        break;
    }
    }
}
#pragma pop

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
            ? *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2)
            : 0;

        m_weaponModelHandle->LoadModel(
            4, static_cast<unsigned long>(itemId), static_cast<unsigned long>(itemVariant), textureVariant, -1, 0, 1);
        m_weaponAttachNode =
            m_charaModelHandle->m_model->SearchNode(const_cast<char*>(s_r_item));
    }
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
            ? *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2)
            : 0;

        m_shieldModelHandle->LoadModel(4, static_cast<unsigned long>(itemId), 0, textureVariant, -1, 0, 1);
        m_shieldAttachNodeIndex =
            m_charaModelHandle->m_model->SearchNode(const_cast<char*>(s_l_item2));
    }
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
#pragma push
#pragma opt_common_subs off
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

    CModelAnimState& model = ModelAnimState(handle->m_model);
    if (model.m_anim != 0) {
        const float span = sAnimFrameOffset + (model.m_animEnd - model.m_animStart);

        if (sAnimFrameOffset == span) {
            return 1;
        }

        float base;
        if (mode != 0) {
            base = m_turnSpeed;
        } else {
            base = model.m_time;
        }

        double threshold = static_cast<double>(base);

        if (mode == 2) {
            threshold = static_cast<double>(static_cast<float>(threshold + sLoopBias));
        }

        const float lastAttr = m_lastBgAttr;

        if (static_cast<double>(lastAttr) < static_cast<double>(sZeroFloat)) {
            return (static_cast<u32>(static_cast<u8>(
                        (static_cast<double>(sZeroFloat) >= threshold) << 1))
                    << 0x1C)
                   >> 0x1D;
        }

        const double diff = static_cast<double>(span - sAnimFrameOffset);
        return (static_cast<u32>(static_cast<u8>((diff < threshold) << 3)) << 0x1C) >> 0x1F;
    }

    return 1;
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x8007c808
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_common_subs off
int CGObject::IsAnimFinished(int mode)
{
    float frame;
    float animSpan;
    bool hasModel = false;
    u32 result;
    u32 shieldFlagClz;
    signed char shieldFlag;
    CCharaPcs::CHandle* handle;
    double threshold;

    char slot;

    handle = m_charaModelHandle;
    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (hasModel) {
        slot = m_currentAnimSlot;
        if (slot == -1) {
            return 1;
        }
        {
            shieldFlag = static_cast<signed char>(m_shieldNodeFlagBits.m_bit08);
            shieldFlagClz = static_cast<u32>(__cntlzw(static_cast<u32>(shieldFlag)));
            result = shieldFlagClz >> 5;

            if (((shieldFlagClz >> 5) & 0xFF) != 0) {
                hasModel = false;
                if ((handle != 0) && (handle->m_model != 0)) {
                    hasModel = true;
                }

                if (!hasModel || (slot == -1)) {
                    result = 1;
                } else {
                    CModelAnimState& model = ModelAnimState(handle->m_model);
                    if (model.m_anim != 0) {
                        animSpan = sAnimFrameOffset + (model.m_animEnd - model.m_animStart);
                        if (sAnimFrameOffset == animSpan) {
                            result = 1;
                        } else {
                            if (mode != 0) {
                                frame = m_turnSpeed;
                            } else {
                                frame = model.m_time;
                            }

                            threshold = static_cast<double>(frame);
                            if (mode == 2) {
                                threshold = static_cast<double>(static_cast<float>(threshold + sLoopBias));
                            }

                            const float lastAttr = m_lastBgAttr;
                            if (static_cast<double>(lastAttr)
                                < static_cast<double>(sZeroFloat)) {
                                result =
                                    (static_cast<u32>(static_cast<u8>(
                                         (static_cast<double>(sZeroFloat) >= threshold) << 1))
                                     << 0x1C)
                                    >> 0x1D;
                            } else {
                                result =
                                    (static_cast<u32>(static_cast<u8>(
                                         (static_cast<double>(animSpan - sAnimFrameOffset) < threshold) << 3))
                                     << 0x1C)
                                    >> 0x1F;
                            }
                        }
                    } else {
                        result = 1;
                    }
                }

                result = static_cast<u32>(-static_cast<int>(result)) >> 0x1F;
            }

            return result & 0xFF;
        }
    }

    return 1;
}
#pragma pop

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
	struct ShieldNodeFlagBits {
	    unsigned char unk0 : 1;
	    unsigned char unk1 : 1;
	    unsigned char unk2 : 1;
	    unsigned char unk3 : 1;
	    unsigned char unk4 : 1;
	    unsigned char unk5 : 1;
	    unsigned char unk6 : 1;
	    unsigned char unk7 : 1;
	};

	m_currentAnimSlot = -1;

	reinterpret_cast<ShieldNodeFlagBits*>(&m_shieldNodeFlags)->unk1 = 0;

	const float& zero = sZeroFloat;
	m_turnSpeed = zero;

	if (keepFacing != 0)
	{
		m_rotTargetY = m_rotBaseY;
	}

	*((u8*)&m_shieldNodeFlags) =
	    static_cast<u8>(__rlwimi(*((u8*)&m_shieldNodeFlags), 0, 3, 28, 28));

	*((u8*)&m_shieldNodeFlags) =
	    static_cast<u8>(__rlwimi(*((u8*)&m_shieldNodeFlags), 0, 7, 24, 24));
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
    const float& zero = sZeroFloat;
    m_turnSpeed = zero;
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
    struct ShieldNodeFlagBits {
        signed char unk0 : 1;
        signed char unk1 : 1;
        signed char unk2 : 1;
        signed char dispItemName : 1;
        signed char unk4 : 1;
        signed char unk5 : 1;
        signed char unk6 : 1;
        signed char unk7 : 1;
    };

    reinterpret_cast<ShieldNodeFlagBits*>(&m_shieldNodeFlags)->dispItemName = showName;
    m_dispItemTimer = 13;
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
    if (m_weaponNodeFlagBits.m_unk20 && (sZeroFloat < m_screenDepth)) {
        float invDepth = sAnimFrameOffset / m_screenDepth;
        float xProd = sDebugScreenX * m_projection.z;
        float yProd = sDebugScreenY * m_projection.y;
        float screenX[2];
        screenX[0] = -(xProd * invDepth - sDebugScreenX);

        onDrawDebug(font,
                    yProd * invDepth + sDebugScreenY,
                    screenX[0],
                    m_projection.w * invDepth);
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
#pragma push
#pragma optimization_level 1
#pragma opt_common_subs on
void CGObject::SetPosBG(Vec* position, int useCapsuleOffset)
{
    m_worldPosition = *position;

    if (m_weaponNodeFlagBits.m_unk10 && (Game.m_currentMapId != 0x21)) {
        {
            Vec bottom = m_worldPosition;
            bottom.y += useCapsuleOffset != 0 ? m_capsuleHalfHeight : sPushDistance;
            Vec direction;
            direction.x = sZeroFloat;
            direction.y = sDownUnitY;
            direction.z = sZeroFloat;
            CMapCylinder bodyCylinder(sHugeCylinderExtent, sNegHugeCylinderExtent);
            bodyCylinder.m_bottom = bottom;
            bodyCylinder.m_axis = direction;
            bodyCylinder.m_radius = sZeroFloat;

            if (MapMng.CheckHitCylinderNear(
                    &bodyCylinder, &direction,
                    m_bgHitMask) != 0) {
                MapMng.m_hitMapObj->CalcHitPosition(&m_worldPosition);
            }
        }

        bool hasModel = false;
        if ((m_charaModelHandle != 0) && (m_charaModelHandle->m_model != 0)) {
            hasModel = true;
        }
        if (hasModel) {
            CVector attrDirection(sZeroFloat, sDownProbeDistance, sZeroFloat);
            CVector attrBottom(m_worldPosition.x, m_worldPosition.y + sStepProbeHeight, m_worldPosition.z);
            CMapCylinder attrCylinder(sHugeCylinderExtent, sNegHugeCylinderExtent);

            attrCylinder.m_bottom = attrBottom;
            attrCylinder.m_axis.x = attrDirection.x;
            attrCylinder.m_axis.y = attrDirection.y;
            attrCylinder.m_axis.z = attrDirection.z;
            attrCylinder.m_radius = sZeroFloat;

            if (MapMng.CheckHitCylinderNear(
                    &attrCylinder,
                    reinterpret_cast<Vec*>(&attrDirection), 0x78000000) != 0) {
                switch (gMapHitFace->m_groupIndex - 0x28) {
                case 0:
                    m_bgAttrValue = sBgAttrSlow;
                    break;
                case 1:
                    m_bgAttrValue = sBgAttrNormal;
                    break;
                case 2:
                    m_bgAttrValue = sBgAttrFast;
                    break;
                case 3:
                    m_bgAttrValue = sZeroFloat;
                    break;
                default:
                    break;
                }
            } else {
                m_bgAttrValue = sAnimFrameOffset;
            }
        }
        m_animBlend = m_bgAttrValue;
    }
}
#pragma pop

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
    struct ModelFlagBits {
        signed char m_dynamics : 1;
        signed char m_unused : 7;
    };
    bool hasModel = false;
    CCharaPcs::CHandle* handle = m_charaModelHandle;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (hasModel) {
        u8* modelBytes = reinterpret_cast<u8*>(handle->m_model);
        reinterpret_cast<ModelFlagBits*>(modelBytes + 0x10C)->m_dynamics = true;
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

    *reinterpret_cast<u16*>(reinterpret_cast<u8*>(handle->m_animSlot[slot]) + 0x2C) = 0;
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
    bool hasModel = false;
    CCharaPcs::CHandle* handle = m_charaModelHandle;

    if ((handle != 0) && (handle->m_model != 0)) {
        hasModel = true;
    }

    if (!hasModel) {
        return;
    }

    CRef* animRef = handle->m_animSlot[slot];
    if (animRef == 0) {
        return;
    }

    u8* animRefBytes = reinterpret_cast<u8*>(animRef);
    u16* count = reinterpret_cast<u16*>(animRefBytes + 0x2C);

    reinterpret_cast<u16*>(animRefBytes + 0x2E)[*count * 2] = static_cast<u16>(pointFrame);
    reinterpret_cast<u16*>(animRefBytes + 0x30)[*count * 2] = static_cast<u16>(pointType);
    *count = static_cast<u16>(*count + 1);
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
 * PAL Address: 0x8007bf34
 * PAL Size: 644b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CGObject::CalcSafePos(int hitMask, CGObject* other, Vec* outSafePos)
{
    Vec centerPos;
    Vec hitMove;
    float safeDistance = sZeroFloat;

    centerPos.x = other->m_worldPosition.x;
    if (other->m_worldPosition.y > m_worldPosition.y) {
        centerPos.y = other->m_worldPosition.y;
    } else {
        centerPos.y = m_worldPosition.y;
    }
    centerPos.y += m_capsuleHalfHeight;
    centerPos.z = other->m_worldPosition.z;

    PSVECSubtract(&m_worldPosition, &centerPos, &hitMove);
    hitMove.y = sZeroFloat;

    CMapCylinder hitCylinder(sHugeCylinderExtent, sNegHugeCylinderExtent);
    hitCylinder.m_bottom = centerPos;
    hitCylinder.m_axis = hitMove;
    hitCylinder.m_radius = m_capsuleHalfHeight;

    if (MapMng.CheckHitCylinderNear(&hitCylinder, &hitMove, hitMask) != 0) {
        MapMng.m_hitMapObj->CalcHitPosition(&centerPos);
        centerPos.y -= m_capsuleHalfHeight;
        *outSafePos = centerPos;
        safeDistance = PSVECDistance(&m_worldPosition, &centerPos);
    } else {
        *outSafePos = m_worldPosition;
        hitMove.y = sZeroFloat;
        hitMove.x = (m_capsuleHalfHeight + other->m_capsuleHalfHeight) * (float)sin((double)other->m_rotBaseY);
        hitMove.z = (m_capsuleHalfHeight + other->m_capsuleHalfHeight) * (float)cos((double)other->m_rotBaseY);

        CMapCylinder safeCylinder(sHugeCylinderExtent, sNegHugeCylinderExtent);
        safeCylinder.m_bottom = centerPos;
        safeCylinder.m_axis = hitMove;
        safeCylinder.m_radius = m_capsuleHalfHeight;

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
        s16 rawDropCode = *reinterpret_cast<s16*>(&m_dropItemCodes[i]);
        if (rawDropCode > 0) {
            s32 dropCode = rawDropCode;
            int createMode;
            if ((dropCode & 0xC000) == 0x4000) {
                dropCode &= ~0xC000;
                createMode = 2;
            } else {
                createMode = 0;
            }

            CGItemObj::CreateFromScript(createMode, 4, dropCode, this, sQuarterTurn * (float)dropCount, 0);
            dropCount++;
        }
    }
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
 * Address:	TODO
 * Size:	TODO
 */
float CGObject::onAlphaUpdate()
{
	return sAnimFrameOffset;
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
int CGObject::GetCID()
{
	return 5;
}

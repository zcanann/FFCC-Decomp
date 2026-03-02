#include "ffcc/gobject.h"

#include "ffcc/cflat_runtime.h"
#include "ffcc/color.h"
#include "ffcc/graphic.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/p_minigame.h"
#include "ffcc/pad.h"
#include "ffcc/partMng.h"
#include "ffcc/quadobj.h"
#include "ffcc/sound.h"

#include <dolphin/gx.h>
#include <math.h>
#include <string.h>

extern CPartMng PartMng;
extern CMath Math;
extern CMiniGamePcs MiniGamePcs;
extern unsigned char CFlat[];
extern u32 CFlatFlags;
extern Mtx gFlatPosMtx;
extern "C" int __cntlzw(unsigned int);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, CGBaseObj*, int, int, int, CFlatRuntime::CStack*, CFlatRuntime::CStack*);
extern "C" int SearchNode__Q26CChara6CModelFPc(CChara::CModel*, char*);
extern "C" CGObject* FindGObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGObject* FindGObjNext__13CFlatRuntime2FP8CGObject(void*, CGObject*);
extern "C" CGQuadObj* FindGQuadObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGQuadObj* FindGQuadObjNext__13CFlatRuntime2FP9CGQuadObj(void*, CGQuadObj*);
extern "C" int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, u32);
extern "C" int CalcHitSlide__7CMapObjFP3Vecf(void*, Vec*);
extern "C" void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
extern "C" void GetHitFaceNormal__7CMapObjFP3Vec(void*, Vec*);
extern "C" int PlaySe3D__6CSoundFiP3Vecffi(CSound*, int, Vec*, float, float, int);
extern "C" void* CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS(
    int, int, int, CGObject*, float, void*);
extern unsigned char DAT_8032ec90[];
extern float FLOAT_8033033c;
extern float FLOAT_80330354;
extern float FLOAT_80330340;
extern float FLOAT_80330344;
extern float FLOAT_8033035c;
extern float FLOAT_80330368;
extern float FLOAT_80330364;
extern float FLOAT_8033036c;
extern float FLOAT_80330360;
extern double DOUBLE_80330348;
extern double DOUBLE_803303e8;
extern double DOUBLE_80330400;
extern float FLOAT_80330410;
extern float FLOAT_80330414;
extern float FLOAT_80330418;
extern float FLOAT_8033041c;
extern float FLOAT_80330420;
extern float FLOAT_80330424;
extern float FLOAT_80330428;
extern float FLOAT_8033042c;
extern float FLOAT_80330430;
extern float DAT_801d9b70;
extern float DAT_801d9b74;
extern float DAT_801d9b78;
extern float DAT_801d9b7c;
extern float DAT_801d9b80;
extern float DAT_801d9b84;

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
 * PAL Address: 0x80081318
 * PAL Size: 2752b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::move()
{
    if ((m_charaModelHandle == 0) || (m_charaModelHandle->m_model == 0)) {
        return;
    }

    u8 weaponFlags = *reinterpret_cast<u8*>(&m_weaponNodeFlags);
    if (Game.game.m_currentMapId == 0x21) {
        if (static_cast<int>((static_cast<u32>(weaponFlags) << 0x1D) | (weaponFlags >> 3)) < 0) {
            m_groundHitOffset.y = sZeroFloat;
        }
    } else {
        if ((static_cast<int>((static_cast<u32>(weaponFlags) << 0x1B) | (weaponFlags >> 5)) < 0)
            && (static_cast<int>((static_cast<u32>(weaponFlags) << 0x1C) | (weaponFlags >> 4)) >= 0)) {
            PSVECAdd(&m_groundHitOffset, &m_bodyOffset, &m_groundHitOffset);
            if (m_groundHitOffset.y < FLOAT_80330428) {
                m_groundHitOffset.y = FLOAT_80330428;
            }
        } else if (static_cast<int>((static_cast<u32>(weaponFlags) << 0x1D) | (weaponFlags >> 3)) < 0) {
            m_groundHitOffset.y = sZeroFloat;
        }
    }

    bool movingWithScript = false;
    bool hasStickInput = false;
    Vec moveVec;
    moveVec.x = sZeroFloat;
    moveVec.y = sZeroFloat;
    moveVec.z = sZeroFloat;
    m_groundHitOffset.y += m_gravityY;

    u8 weaponFlagsHi = *(reinterpret_cast<u8*>(&m_weaponNodeFlags) + 1);
    if (static_cast<int>((static_cast<u32>(weaponFlagsHi) << 0x1A) | (weaponFlagsHi >> 6)) < 0) {
        int scriptMoveEnd = 0;
        if (static_cast<int>((static_cast<u32>(weaponFlagsHi) << 0x1B) | (weaponFlagsHi >> 5)) < 0) {
            moveVec.x = m_moveVec.y;
            moveVec.y = m_moveVec.z;
            moveVec.z = m_moveSpeed;
        } else {
            PSVECSubtract(reinterpret_cast<Vec*>(&m_moveVec.y), &m_worldPosition, &moveVec);
        }

        if ((Game.game.m_currentMapId != 0x21)
            && (static_cast<int>((static_cast<u32>(weaponFlagsHi) << 0x1E) | (weaponFlagsHi >> 2)) >= 0)) {
            moveVec.y = sZeroFloat;
        }

        const double moveMag = static_cast<double>(PSVECMag(&moveVec));
        if (moveMag == static_cast<double>(sZeroFloat)) {
            scriptMoveEnd = 1;
        } else if ((static_cast<int>((static_cast<u32>(weaponFlagsHi) << 0x1B) | (weaponFlagsHi >> 5)) < 0)
                   || (static_cast<double>(m_moveTimer) <= moveMag)) {
            PSVECNormalize(&moveVec, &moveVec);
            PSVECScale(&moveVec, &moveVec, static_cast<float>(m_moveTimer));
        } else {
            scriptMoveEnd = 1;
        }

        m_turnFrames -= 1;
        if (static_cast<int>(m_turnFrames) < 1) {
            scriptMoveEnd = 2;
        }

        weaponFlagsHi = *(reinterpret_cast<u8*>(&m_weaponNodeFlags) + 1);
        const u32 scriptMoveFlag = (static_cast<u32>(weaponFlagsHi) << 0x1B) | (weaponFlagsHi >> 5);
        if (((static_cast<int>(scriptMoveFlag) >= 0) && (scriptMoveEnd != 0))
            || ((static_cast<int>(scriptMoveFlag) < 0) && (scriptMoveEnd == 2))) {
            *(reinterpret_cast<u8*>(&m_weaponNodeFlags) + 1) &= 0xDF;
            u32 stackWord = static_cast<u32>(__cntlzw(static_cast<u32>(2 - scriptMoveEnd))) >> 5;
            SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
                CFlat,
                this,
                2,
                7,
                1,
                reinterpret_cast<CFlatRuntime::CStack*>(&stackWord),
                0);
        }

        movingWithScript = true;
    } else {
        const u8 player = m_animStateMisc;
        const bool canReadPad = (static_cast<char>(player) >= 0)
            && (static_cast<char>(player) <= 3)
            && (static_cast<int>((static_cast<u32>(weaponFlagsHi) << 0x18) | (weaponFlagsHi >> 8)) < 0)
            && (static_cast<int>((static_cast<u32>(weaponFlagsHi) << 0x19) | (weaponFlagsHi >> 7)) < 0)
            && ((Game.game.m_gameWork.m_menuStageMode == 0) || (player == 0));

        if (canReadPad) {
            const bool useDebugPad = (Pad._452_4_ != 0) || ((player == 0) && (Pad._448_4_ != -1));
            const u32 playerIndex = static_cast<u32>(player)
                & ~((static_cast<int>(~(Pad._448_4_ - static_cast<int>(player)
                                        | static_cast<int>(player) - Pad._448_4_))
                     >> 31));
            const u8* padBytes = reinterpret_cast<u8*>(&Pad);

            u16 buttons = 0;
            u16 buttonsDown = 0;
            u16 buttonsRepeat = 0;
            if (!useDebugPad) {
                buttons = *reinterpret_cast<const u16*>(padBytes + 0x4 + (playerIndex * 0x54));
                buttonsDown = *reinterpret_cast<const u16*>(padBytes + 0x8 + (playerIndex * 0x54));
                buttonsRepeat = *reinterpret_cast<const u16*>(padBytes + 0x12 + (playerIndex * 0x54));
            }

            if ((buttons != 0) && (buttonsRepeat != 0)) {
                buttons |= buttonsRepeat;
            }

            u32 miniGameFlags = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(&MiniGamePcs) + 0x6484);
            if ((miniGameFlags & 0x100) != 0) {
                float stickX = sZeroFloat;
                float stickY = sZeroFloat;
                if (!useDebugPad) {
                    stickX = *reinterpret_cast<const float*>(padBytes + 0x24 + (playerIndex * 0x54));
                    stickY = *reinterpret_cast<const float*>(padBytes + 0x28 + (playerIndex * 0x54));
                }
                moveVec.x = sZeroFloat - stickX;
                moveVec.z = sZeroFloat + stickY;
                if ((moveVec.x != sZeroFloat) || (moveVec.z != sZeroFloat)) {
                    hasStickInput = true;
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
                if (static_cast<int>((static_cast<u32>(*reinterpret_cast<u8*>(&m_weaponNodeFlags)) << 0x1B)
                                         | (*reinterpret_cast<u8*>(&m_weaponNodeFlags) >> 5))
                    < 0) {
                    PSVECAdd(&m_groundHitOffset, &m_jumpOffset, &m_groundHitOffset);
                } else {
                    m_worldPosition.y += FLOAT_80330418;
                }
            }

            if (Game.game.m_currentMapId == 0x21) {
                Mtx cameraWorldMtx;
                PSMTXCopy(reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(&CameraPcs) + 0x64), cameraWorldMtx);
                moveVec.x = -moveVec.x;
                moveVec.z = -moveVec.z;
                moveVec.y = sZeroFloat;
                PSMTXMultVec(cameraWorldMtx, &moveVec, &moveVec);
            }
        }
    }

    if ((moveVec.x != sZeroFloat) || (moveVec.y != sZeroFloat) || (moveVec.z != sZeroFloat)) {
        float cameraYaw = *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs) + 0x248);
        if (movingWithScript) {
            cameraYaw = sZeroFloat;
        }

        const double inputYaw = atan2(static_cast<double>(moveVec.x), static_cast<double>(moveVec.z));
        const float inputYawF = static_cast<float>(inputYaw);

        const double sinYaw = sin(static_cast<double>(cameraYaw));
        const double cosYaw = cos(static_cast<double>(cameraYaw));
        if (Game.game.m_currentMapId != 0x21) {
            const double mz = static_cast<double>(moveVec.z);
            const float oldX = moveVec.x;
            moveVec.z = static_cast<float>(static_cast<double>(oldX) * static_cast<float>(sinYaw)
                                           + static_cast<float>(mz * static_cast<float>(cosYaw)));
            moveVec.x = static_cast<float>(static_cast<double>(oldX) * static_cast<float>(cosYaw)
                                           - static_cast<float>(mz * static_cast<float>(sinYaw)));
        }

        if (!movingWithScript) {
            double speed = static_cast<double>(m_moveBaseSpeed);
            if (hasStickInput && ((*reinterpret_cast<u32*>(reinterpret_cast<u8*>(&MiniGamePcs) + 0x6484) & 0x200) != 0)) {
                const double mag = static_cast<double>(PSVECMag(&moveVec));
                speed *= static_cast<double>(FLOAT_8033042c) * mag;
            }

            PSVECNormalize(&moveVec, &moveVec);

            weaponFlagsHi = *(reinterpret_cast<u8*>(&m_weaponNodeFlags) + 1);
            if ((static_cast<int>(static_cast<u32>(weaponFlagsHi) << 0x18) < 0)
                && (static_cast<int>((static_cast<u32>(weaponFlagsHi) << 0x19) | (weaponFlagsHi >> 7)) < 0)
                && (m_ownerType == 0)) {
                if ((*reinterpret_cast<u32*>(reinterpret_cast<u8*>(&MiniGamePcs) + 0x6484) & 2) != 0) {
                    speed *= static_cast<double>(FLOAT_8033042c);
                }

                const u32 cflatCenterState = *reinterpret_cast<u32*>(CFlat + 0x12AC);
                if (cflatCenterState == 1) {
                    Vec partyCenter;
                    partyCenter.x = (Game.game.m_partyMinX + Game.game.m_partyMaxX) * FLOAT_80330368;
                    partyCenter.y = (Game.game.m_partyMinY + Game.game.m_partyMaxY) * FLOAT_80330368;
                    partyCenter.z = (Game.game.m_partyMinZ + Game.game.m_partyMaxZ) * FLOAT_80330368;

                    Vec centerDelta;
                    PSVECSubtract(&m_worldPosition, &partyCenter, &centerDelta);
                    double centerDist = static_cast<double>(PSVECMag(&centerDelta));
                    PSVECNormalize(&centerDelta, &centerDelta);

                    const double dirDot = static_cast<double>(PSVECDotProduct(&moveVec, &centerDelta));
                    if (static_cast<double>(sZeroFloat) < dirDot) {
                        centerDist /= static_cast<double>(*reinterpret_cast<float*>(CFlat + 0x12B0));
                        double clampDist = centerDist;
                        if (static_cast<double>(sZeroFloat) <= clampDist) {
                            if (static_cast<double>(sAnimFrameOffset) < clampDist) {
                                clampDist = static_cast<double>(sAnimFrameOffset);
                            }
                            speed *= -((clampDist * clampDist) - static_cast<double>(sAnimFrameOffset));
                        }
                    }
                }
            }

            if ((*reinterpret_cast<u32*>(&m_radiusCtrl.x) & 0x400000) != 0) {
                speed *= static_cast<double>(FLOAT_80330344);
            }

            PSVECScale(&moveVec, &moveVec, static_cast<float>(speed));
        }

        PSVECAdd(&m_groundHitOffset, &moveVec, &m_groundHitOffset);

        if (!movingWithScript
            || (static_cast<int>((static_cast<u32>(*(reinterpret_cast<u8*>(&m_weaponNodeFlags) + 1)) << 0x1C)
                                     | (*(reinterpret_cast<u8*>(&m_weaponNodeFlags) + 1) >> 4))
                < 0)) {
            if (Game.game.m_currentMapId == 0x21) {
                const double slideSq = static_cast<double>(PSVECSquareMag(&m_groundHitOffset));
                if (static_cast<double>(FLOAT_80330430) < slideSq) {
                    Mtx yawMtx;
                    Mtx pitchMtx;
                    Vec worldUp;
                    Vec tangent;
                    Vec worldPosNorm;
                    Vec moveNorm;
                    Vec cross;

                    PSMTXRotRad(yawMtx, 'y', static_cast<float>(atan2(static_cast<double>(m_worldPosition.x),
                                                                      static_cast<double>(m_worldPosition.z))));
                    worldUp.x = DAT_801d9b70;
                    worldUp.y = DAT_801d9b74;
                    worldUp.z = DAT_801d9b78;
                    tangent.x = DAT_801d9b7c;
                    tangent.y = DAT_801d9b80;
                    tangent.z = DAT_801d9b84;
                    PSVECNormalize(&m_worldPosition, &worldPosNorm);
                    float upDot = PSVECDotProduct(&worldUp, &worldPosNorm);
                    if (upDot > 1.0f) {
                        upDot = 1.0f;
                    } else if (upDot < -1.0f) {
                        upDot = -1.0f;
                    }
                    PSMTXRotRad(pitchMtx, 'x', acosf(upDot));
                    PSMTXConcat(yawMtx, pitchMtx, yawMtx);

                    PSVECNormalize(&m_groundHitOffset, &moveNorm);
                    PSMTXMultVec(yawMtx, &tangent, &tangent);
                    float tanDot = PSVECDotProduct(&tangent, &moveNorm);
                    if (tanDot > 1.0f) {
                        tanDot = 1.0f;
                    } else if (tanDot < -1.0f) {
                        tanDot = -1.0f;
                    }
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

        if (movingWithScript
            && (static_cast<int>((static_cast<u32>(*(reinterpret_cast<u8*>(&m_weaponNodeFlags) + 1)) << 0x1D)
                                     | (*(reinterpret_cast<u8*>(&m_weaponNodeFlags) + 1) >> 3))
                >= 0)) {
            m_animSlotSel = *(reinterpret_cast<s8*>(&m_shieldNodeFlags) + 1);
        } else {
            m_animSlotSel = *reinterpret_cast<s8*>(&m_animStartFrame);
        }
        return;
    }

    const double rotDelta = static_cast<double>(Math.DstRot(m_rotTargetY, m_rotBaseY));
    m_animSlotSel = (DOUBLE_803303e8 < fabs(rotDelta))
        ? *reinterpret_cast<s8*>(&m_animStartFrame)
        : *(reinterpret_cast<s8*>(&m_shieldNodeFlags) + 1);
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
 * PAL Address: 0x800804a4
 * PAL Size: 560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::bgWorldCollision()
{
    Vec radial = m_worldPosition;
    PSVECAdd(&radial, &m_groundHitOffset, &radial);

    if (PSVECMag(&radial) > sZeroFloat) {
        PSVECNormalize(&radial, &radial);
    }
    PSVECScale(&radial, &radial, FLOAT_80330354);

    Vec hitMove;
    hitMove.x = -radial.x * FLOAT_80330414;
    hitMove.y = -radial.y * FLOAT_80330414;
    hitMove.z = -radial.z * FLOAT_80330414;

    CMapCylinder bodyCylinder;
    bodyCylinder.m_bottom = radial;
    bodyCylinder.m_direction = hitMove;
    bodyCylinder.m_radius = FLOAT_8033033c;
    bodyCylinder.m_height = FLOAT_8033033c;
    bodyCylinder.m_top = hitMove;
    bodyCylinder.m_direction2.x = FLOAT_80330340;
    bodyCylinder.m_direction2.y = FLOAT_80330340;
    bodyCylinder.m_direction2.z = FLOAT_80330340;
    bodyCylinder.m_radius2 = sZeroFloat;
    bodyCylinder.m_height2 = sZeroFloat;

    const u32 hitMask = *reinterpret_cast<u32*>(&m_moveVec.x);
    if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &bodyCylinder, &hitMove, hitMask) == 0) {
        return;
    }

    CalcHitPosition__7CMapObjFP3Vec(*reinterpret_cast<void**>(reinterpret_cast<u8*>(&MapMng) + 0x22A88), &radial);
    PSVECSubtract(&radial, &m_worldPosition, &m_groundHitOffset);

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
    const bool hasModel =
        (m_charaModelHandle != (CCharaPcs::CHandle*)0) &&
        (m_charaModelHandle->m_model != (CChara::CModel*)0);
    if (!hasModel) {
        return;
    }

    *(reinterpret_cast<u8*>(&m_shieldNodeFlags)) &= 0xDF;

    if ((m_displayFlags & 4) != 0) {
        Vec probePos;
        Vec probeMove;
        probePos.x = m_worldPosition.x;
        probePos.y = m_worldPosition.y + FLOAT_80330410;
        probePos.z = m_worldPosition.z;
        probeMove.x = sZeroFloat;
        probeMove.y = FLOAT_8033035c;
        probeMove.z = sZeroFloat;

        CMapCylinder charmCylinder;
        charmCylinder.m_bottom = probePos;
        charmCylinder.m_direction = probeMove;
        charmCylinder.m_radius = FLOAT_8033033c;
        charmCylinder.m_height = FLOAT_8033033c;
        charmCylinder.m_top = probeMove;
        charmCylinder.m_direction2.x = FLOAT_80330340;
        charmCylinder.m_direction2.y = FLOAT_80330340;
        charmCylinder.m_direction2.z = FLOAT_80330340;
        charmCylinder.m_radius2 = sZeroFloat;
        charmCylinder.m_height2 = sZeroFloat;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &charmCylinder, &probeMove, 0x80000000) != 0) {
            Vec hitPos;
            CalcHitPosition__7CMapObjFP3Vec(*reinterpret_cast<void**>(reinterpret_cast<u8*>(&MapMng) + 0x22A88), &hitPos);
            m_bgCharmFactor = m_worldPosition.y - hitPos.y;
            *(reinterpret_cast<u8*>(&m_shieldNodeFlags)) |= 0x20;
        }
    }

    if ((m_weaponNodeFlags & 1) == 0) {
        if ((m_groundHitOffset.x != sZeroFloat) || (m_groundHitOffset.z != sZeroFloat)) {
            Vec probePos;
            Vec probeMove;
            probePos.x = m_worldPosition.x;
            probePos.y = m_worldPosition.y + FLOAT_80330360;
            probePos.z = m_worldPosition.z;
            probeMove.x = sZeroFloat;
            probeMove.y = FLOAT_8033035c;
            probeMove.z = sZeroFloat;

            CMapCylinder attrCylinder;
            attrCylinder.m_bottom = probePos;
            attrCylinder.m_direction = probeMove;
            attrCylinder.m_radius = FLOAT_8033033c;
            attrCylinder.m_height = FLOAT_8033033c;
            attrCylinder.m_top = probeMove;
            attrCylinder.m_direction2.x = FLOAT_80330340;
            attrCylinder.m_direction2.y = FLOAT_80330340;
            attrCylinder.m_direction2.z = FLOAT_80330340;
            attrCylinder.m_radius2 = sZeroFloat;
            attrCylinder.m_height2 = sZeroFloat;

            if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &attrCylinder, &probeMove, 0x78000000) == 0) {
                m_bgAttrValue = sAnimFrameOffset;
            } else {
                switch (DAT_8032ec90[0x47]) {
                case 0x28:
                    m_bgAttrValue = FLOAT_80330364;
                    break;
                case 0x29:
                    m_bgAttrValue = FLOAT_80330368;
                    break;
                case 0x2A:
                    m_bgAttrValue = FLOAT_8033036c;
                    break;
                case 0x2B:
                    m_bgAttrValue = sZeroFloat;
                    break;
                default:
                    break;
                }
            }
        }
    } else if (m_attachOwner != 0) {
        m_bgAttrValue = m_attachOwner->m_bgAttrValue;
    }
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
    u8* const modelBytes = reinterpret_cast<u8*>(m_charaModelHandle->m_model);
    u8* const modelNodes = *reinterpret_cast<u8**>(modelBytes + 0xA8);

    for (int i = 0; i < 8; i++) {
        AttackCol* attack = &m_attackColliders[i];
        const int node = static_cast<int>(attack->m_radius2);
        PSMTXMultVec(reinterpret_cast<const float (*)[4]>(modelNodes + node * 0xC0 + 0xC),
                     &attack->m_localStart, &attack->m_worldPosition);
        PSVECAdd(&attack->m_worldPosition, &m_worldPosition, &attack->m_worldPosition);
    }

    for (int i = 0; i < 8; i++) {
        DamageCol* damage = &m_damageColliders[i];
        const int node = static_cast<int>(damage->m_outerRadius);
        PSMTXMultVec(reinterpret_cast<const float (*)[4]>(modelNodes + node * 0xC0 + 0xC),
                     &damage->m_localPosition, &damage->m_worldPosition);
        PSVECAdd(&damage->m_worldPosition, &m_worldPosition, &damage->m_worldPosition);
    }

    if ((m_bgColMask & 0x40000) == 0) {
        return;
    }

    for (CGObject* other = FindGObjFirst__13CFlatRuntime2Fv(CFlat); other != 0;
         other = FindGObjNext__13CFlatRuntime2FP8CGObject(CFlat, other)) {
        if ((other == this) || ((other->m_bgColMask & 0x80000) == 0)) {
            continue;
        }

        Vec delta;
        PSVECSubtract(&m_worldPosition, &other->m_worldPosition, &delta);
        const float nearRadius = m_nearColRadius + other->m_nearColRadius;
        if (PSVECDotProduct(&delta, &delta) > (nearRadius * nearRadius)) {
            continue;
        }

        for (int attackIndex = 0; attackIndex < 8; attackIndex++) {
            AttackCol* attack = &m_attackColliders[attackIndex];
            if (attack->m_hitMask == 0) {
                continue;
            }

            for (int damageIndex = 0; damageIndex < 8; damageIndex++) {
                DamageCol* damage = &other->m_damageColliders[damageIndex];
                if (((attack->m_hitMask & damage->m_hitMask) == 0) ||
                    (damage->m_innerRadius == sZeroFloat) ||
                    (damage->m_outerRadius == sZeroFloat)) {
                    continue;
                }

                Vec attackVec;
                Vec hitPos;
                PSVECSubtract(&attack->m_worldPosition, &attack->m_localEnd, &attackVec);
                if (Math.CrossCheckSphereVector(&hitPos, 0, &attack->m_localEnd, &attackVec,
                                                reinterpret_cast<Vec*>(&damage->m_worldPosition.y),
                                                damage->m_innerRadius) == 0) {
                    continue;
                }

                if ((GetCID() & 0x2D) == 0x2D) {
                    CFlatRuntime::CStack stackIn[7];
                    stackIn[0].m_word = static_cast<u32>(attackIndex);
                    stackIn[1].m_word = static_cast<u32>(other->m_particleId);
                    stackIn[2].m_word = static_cast<u32>(damageIndex);
                    *reinterpret_cast<float*>(&stackIn[3].m_word) = hitPos.x;
                    *reinterpret_cast<float*>(&stackIn[4].m_word) = hitPos.y;
                    *reinterpret_cast<float*>(&stackIn[5].m_word) = hitPos.z;
                    stackIn[6].m_word = reinterpret_cast<u32>(m_scriptHandle);
                    CFlatRuntime::CStack stackOut;
                    SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
                        CFlat, this, 2, 0x13, 7, stackIn, &stackOut);
                    onHit(attackIndex, other, damageIndex, &hitPos);
                }
            }
        }
    }
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

    if ((*reinterpret_cast<u8*>(&m_weaponNodeFlags) & 0x20) == 0) {
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

    if ((*reinterpret_cast<u8*>(&m_shieldNodeFlags) & 0x20) == 0) {
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
    if ((m_weaponNodeFlags & 0x20) == 0) {
        return;
    }

    const bool hasModel =
        (m_charaModelHandle != (CCharaPcs::CHandle*)0) &&
        (m_charaModelHandle->m_model != (CChara::CModel*)0);
    if (!hasModel) {
        return;
    }

    if (((CFlatFlags & 0x1) != 0) && ((m_bgColMask & 0x1) != 0)) {
        CColor color(0xFF, 0x00, 0x00, 0xFF);
        Vec pos;
        pos.x = m_worldPosition.x;
        pos.y = m_worldPosition.y + m_capsuleHalfHeight;
        pos.z = m_worldPosition.z;
        Graphic.DrawSphere(gFlatPosMtx, &pos, m_capsuleHalfHeight, &color.color);
    }

    if (((CFlatFlags & 0x2) != 0) && ((m_bgColMask & 0x2) != 0)) {
        Vec capsuleOffset;
        capsuleOffset.x = sZeroFloat;
        capsuleOffset.y = sZeroFloat;
        capsuleOffset.z = sZeroFloat;
        if (m_bodyEllipsoidOffset == sZeroFloat) {
        } else {
            capsuleOffset.y = sZeroFloat;
            capsuleOffset.x = m_bodyEllipsoidOffset * -sinf(m_rotBaseY);
            capsuleOffset.z = m_bodyEllipsoidOffset * -cosf(m_rotBaseY);
        }

        Mtx scaleMtx;
        Mtx rotMtx;
        const float r = m_bodyEllipsoidRadius;
        PSMTXScale(scaleMtx, r * m_bodyEllipsoidAspect, r, r);
        PSMTXRotRad(rotMtx, 'y', m_rotBaseY);
        PSMTXConcat(rotMtx, scaleMtx, scaleMtx);

        Vec spherePos;
        spherePos.x = m_worldPosition.x;
        spherePos.y = m_worldPosition.y + m_bodyEllipsoidRadius;
        spherePos.z = m_worldPosition.z;
        PSVECAdd(&spherePos, &capsuleOffset, &spherePos);

        scaleMtx[0][3] = spherePos.x;
        scaleMtx[1][3] = spherePos.y;
        scaleMtx[2][3] = spherePos.z;
        PSMTXConcat(gFlatPosMtx, scaleMtx, scaleMtx);
        GXLoadPosMtxImm(scaleMtx, GX_PNMTX0);

        CColor color(0x00, 0xFF, 0x00, 0xFF);
        GXSetChanMatColor(GX_COLOR0A0, color.color);
        Graphic.DrawSphere();
    }

    if (((CFlatFlags & 0x4) != 0) && ((m_bgColMask & 0x4) != 0)) {
        CColor color(0x00, 0x00, 0xFF, 0xFF);
        Vec pos;
        pos.x = m_worldPosition.x;
        pos.y = m_worldPosition.y + m_bodyColRadius;
        pos.z = m_worldPosition.z;
        Graphic.DrawSphere(gFlatPosMtx, &pos, m_bodyColRadius, &color.color);
    }

    if (((CFlatFlags & 0x8) != 0) && ((m_bgColMask & 0x8) != 0)) {
        CColor color(0xFF, 0xFF, 0x00, 0xFF);
        Vec pos;
        pos.x = m_worldPosition.x;
        pos.y = m_worldPosition.y + m_attackColRadius;
        pos.z = m_worldPosition.z;
        Graphic.DrawSphere(gFlatPosMtx, &pos, m_attackColRadius, &color.color);
    }

    if (((CFlatFlags & 0x10) != 0) && ((m_bgColMask & 0x10) != 0)) {
        CColor color(0x40, 0xFF, 0x40, 0xFF);
        Graphic.DrawSphere(gFlatPosMtx, &m_worldPosition, m_nearColRadius, &color.color);
    }

    if (((CFlatFlags & 0x40000) != 0) && ((m_bgColMask & 0x40000) != 0)) {
        for (int i = 0; i < 8; i++) {
            AttackCol* collider = &m_attackColliders[i];
            if (collider->m_localStart.x == sZeroFloat) {
                continue;
            }

            CColor color(0xFF, 0x80, 0x80, 0xFF);
            Graphic.DrawSphere(gFlatPosMtx, &collider->m_worldPosition, collider->m_radius, &color.color);

            GXLoadPosMtxImm(gFlatPosMtx, GX_PNMTX0);
            GXBegin(GX_LINES, GX_VTXFMT0, 2);
            GXPosition3f32(collider->m_localEnd.y, collider->m_localEnd.z, collider->m_worldPosition.x);
            GXPosition3f32(collider->m_worldPosition.y, collider->m_worldPosition.z, collider->m_radius);
        }
    }

    if (((CFlatFlags & 0x80000) != 0) && ((m_bgColMask & 0x80000) != 0)) {
        for (int i = 0; i < 8; i++) {
            DamageCol* collider = &m_damageColliders[i];
            if (collider->m_localPosition.x == sZeroFloat) {
                continue;
            }

            CColor color(0x80, 0x80, 0xFF, 0xFF);
            Vec scale;
            scale.x = collider->m_innerRadius;
            scale.y = collider->m_outerRadius;
            scale.z = collider->m_innerRadius;
            Graphic.DrawSphere(gFlatPosMtx, &collider->m_worldPosition, &scale, &color.color);
        }
    }
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
 * PAL Address: 0x8007de74
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::Move(Vec* moveVec, float moveTimer, int turnFrames, int moveMode, int useFacing, int flagA, int flagB)
{
    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xDF) | 0x20;
    *((u8*)&m_weaponNodeFlags + 1) &= 0xEF;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveVec.y = moveVec->x;
    m_moveVec.z = moveVec->y;
    m_moveSpeed = moveVec->z;
    m_moveTimer = static_cast<s32>(moveTimer);
    *((u8*)&m_weaponNodeFlags) = (static_cast<u8>(moveMode << 1) & 2) | (*((u8*)&m_weaponNodeFlags) & 0xFD);
    *((u8*)&m_weaponNodeFlags + 1) =
        (static_cast<u8>(useFacing << 3) & 8) | (*((u8*)&m_weaponNodeFlags + 1) & 0xF7);
    *((u8*)&m_weaponNodeFlags + 1) =
        (static_cast<u8>(flagA << 1) & 2) | (*((u8*)&m_weaponNodeFlags + 1) & 0xFD);
    *((u8*)&m_weaponNodeFlags + 1) =
        (static_cast<u8>(flagB << 2) & 4) | (*((u8*)&m_weaponNodeFlags + 1) & 0xFB);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObject::MoveVector(Vec* moveVec, float moveTimer, int turnFrames, int useFacing, int flagA, int flagB)
{
	// TODO
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
    const double mag = static_cast<double>(PSVECMag(moveVec));
    if (static_cast<double>(sZeroFloat) == mag) {
        unitVec.x = sZeroFloat;
        unitVec.y = sZeroFloat;
        unitVec.z = sZeroFloat;
    } else {
        PSVECScale(moveVec, &unitVec, static_cast<float>(static_cast<double>(sAnimFrameOffset) / mag));
    }

    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xDF) | 0x20;
    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xEF) | 0x10;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveVec.y = unitVec.x;
    m_moveVec.z = unitVec.y;
    m_moveSpeed = unitVec.z;
    m_moveTimer = static_cast<s32>(moveTimer);
    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xF7) | 8;
    *((u8*)&m_weaponNodeFlags + 1) &= 0xFD;
    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xFB) | 4;
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
    const double mag = static_cast<double>(PSVECMag(moveVec));
    if (static_cast<double>(sZeroFloat) == mag) {
        unitVec.x = sZeroFloat;
        unitVec.y = sZeroFloat;
        unitVec.z = sZeroFloat;
    } else {
        PSVECScale(moveVec, &unitVec, static_cast<float>(static_cast<double>(sAnimFrameOffset) / mag));
    }

    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xDF) | 0x20;
    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xEF) | 0x10;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveVec.y = unitVec.x;
    m_moveVec.z = unitVec.y;
    m_moveSpeed = unitVec.z;
    m_moveTimer = static_cast<s32>(moveTimer);
    *((u8*)&m_weaponNodeFlags + 1) &= 0xF7;
    *((u8*)&m_weaponNodeFlags + 1) &= 0xFD;
    *((u8*)&m_weaponNodeFlags + 1) &= 0xFB;
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
    const double cosY0 = static_cast<double>(static_cast<float>(cos(rotY)));
    const double sinX = static_cast<double>(static_cast<float>(sin(rotX)));
    const double sinY = static_cast<double>(static_cast<float>(sin(rotY)));
    const double cosY1 = static_cast<double>(static_cast<float>(cos(rotY)));
    const double cosX = static_cast<double>(static_cast<float>(cos(rotX)));

    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xDF) | 0x20;
    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xEF) | 0x10;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveVec.y = static_cast<float>(sinX * cosY0);
    m_moveVec.z = static_cast<float>(sinY);
    m_moveSpeed = static_cast<float>(cosX * cosY1);
    m_moveTimer = static_cast<s32>(moveTimer);
    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xF7) | 8;
    *((u8*)&m_weaponNodeFlags + 1) &= 0xFD;
    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xFB) | 4;
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
    const double cosY0 = static_cast<double>(static_cast<float>(cos(rotY)));
    const double sinX = static_cast<double>(static_cast<float>(sin(rotX)));
    const double sinY = static_cast<double>(static_cast<float>(sin(rotY)));
    const double cosY1 = static_cast<double>(static_cast<float>(cos(rotY)));
    const double cosX = static_cast<double>(static_cast<float>(cos(rotX)));

    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xDF) | 0x20;
    *((u8*)&m_weaponNodeFlags + 1) = (*((u8*)&m_weaponNodeFlags + 1) & 0xEF) | 0x10;
    m_turnFrames = static_cast<u32>(turnFrames);
    m_moveVec.y = static_cast<float>(sinX * cosY0);
    m_moveVec.z = static_cast<float>(sinY);
    m_moveSpeed = static_cast<float>(cosX * cosY1);
    m_moveTimer = static_cast<s32>(moveTimer);
    *((u8*)&m_weaponNodeFlags + 1) &= 0xF7;
    *((u8*)&m_weaponNodeFlags + 1) &= 0xFD;
    *((u8*)&m_weaponNodeFlags + 1) &= 0xFB;
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
    CMapCylinder hitCylinder;
    float safeDistance = sZeroFloat;
    void* hitObject = *reinterpret_cast<void**>(reinterpret_cast<u8*>(&MapMng) + 0x22A88);

    centerPos.x = other->m_worldPosition.x;
    centerPos.y = m_worldPosition.y;
    if (centerPos.y < other->m_worldPosition.y) {
        centerPos.y = other->m_worldPosition.y;
    }
    centerPos.y += m_capsuleHalfHeight;
    centerPos.z = other->m_worldPosition.z;

    PSVECSubtract(&m_worldPosition, &centerPos, &hitMove);
    hitMove.y = sZeroFloat;

    hitCylinder.m_bottom = centerPos;
    hitCylinder.m_direction = hitMove;
    hitCylinder.m_radius = FLOAT_8033033c;
    hitCylinder.m_height = FLOAT_8033033c;
    hitCylinder.m_top = hitMove;
    hitCylinder.m_direction2.x = FLOAT_80330340;
    hitCylinder.m_direction2.y = FLOAT_80330340;
    hitCylinder.m_direction2.z = FLOAT_80330340;
    hitCylinder.m_radius2 = m_capsuleHalfHeight;
    hitCylinder.m_height2 = sZeroFloat;

    if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &hitCylinder, &hitMove, hitMask) == 0) {
        *outSafePos = m_worldPosition;
        hitMove.y = sZeroFloat;
        hitMove.x = (m_capsuleHalfHeight + other->m_capsuleHalfHeight) * (float)sin((double)other->m_rotBaseY);
        hitMove.z = (m_capsuleHalfHeight + other->m_capsuleHalfHeight) * (float)cos((double)other->m_rotBaseY);

        hitCylinder.m_bottom = centerPos;
        hitCylinder.m_direction = hitMove;
        hitCylinder.m_radius = FLOAT_8033033c;
        hitCylinder.m_height = FLOAT_8033033c;
        hitCylinder.m_top = hitMove;
        hitCylinder.m_direction2.x = FLOAT_80330340;
        hitCylinder.m_direction2.y = FLOAT_80330340;
        hitCylinder.m_direction2.z = FLOAT_80330340;
        hitCylinder.m_radius2 = m_capsuleHalfHeight;
        hitCylinder.m_height2 = sZeroFloat;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &hitCylinder, &hitMove, hitMask) != 0) {
            CalcHitPosition__7CMapObjFP3Vec(hitObject, &centerPos);
            safeDistance = (m_capsuleHalfHeight + other->m_capsuleHalfHeight) -
                           PSVECDistance(&m_worldPosition, &centerPos);
        }
    } else {
        CalcHitPosition__7CMapObjFP3Vec(hitObject, &centerPos);
        centerPos.y -= m_capsuleHalfHeight;
        *outSafePos = centerPos;
        safeDistance = PSVECDistance(&m_worldPosition, &centerPos);
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
    u32 dropCount = 0;

    for (int i = 0; i < 4; i++) {
        u32 dropCode = static_cast<u16>(m_dropItemCodes[i]);
        if ((short)m_dropItemCodes[i] > 0) {
            int createMode;
            if ((dropCode & 0xC000) == 0x4000) {
                dropCode &= 0x3FFF;
                createMode = 2;
            } else {
                createMode = 0;
            }

            CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS(
                createMode,
                4,
                dropCode,
                this,
                FLOAT_80330344 * (float)dropCount,
                0);
            dropCount++;
        }
    }
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
	return 5;
}

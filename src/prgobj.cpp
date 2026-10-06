#include "ffcc/prgobj.h"
#include "ffcc/charaobj.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/math.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_tina.h"
#include "ffcc/linkage.h"
#include "ffcc/sound.h"
#include "ffcc/vector.h"

#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/math.h>

STATIC_ASSERT(offsetof(CGCharaObj, m_itemId) == 0x560);

/*
 * --INFO--
 * PAL Address: 0x80127AF0
 * PAL Size: 100b
 * EN Address: 0x80126E20
 * EN Size: 100b
 * JP Address: 0x801239D4
 * JP Size: 100b
 */
void CGPrgObj::onCreate()
{
	CGObject::onCreate();
	m_lastStateId = 0;
	m_stateArg = 0;
	m_animFlagBits.bits.m_animRequested = 0;
	m_animFlagBits.bits.m_animLoop = 0;
	m_animFlagBits.bits.m_animDirect = 0;
	m_reqAnimId = -1;
}

/*
 * --INFO--
 * PAL Address: 0x80127AD0
 * PAL Size: 32b
 * EN Address: 0x80126E00
 * EN Size: 32b
 * JP Address: 0x801239B4
 * JP Size: 32b
 */
void CGPrgObj::onDestroy()
{
	CGObject::onDestroy();
}

/*
 * --INFO--
 * PAL Address: 0x801278DC
 * PAL Size: 500b
 * EN Address: 0x80126C0C
 * EN Size: 500b
 * JP Address: 0x801237C0
 * JP Size: 500b
 */
void CGPrgObj::onFrame()
{
    onFrameAlways();

	if (m_weaponNodeFlagBits.m_prg != 0) {
		if ((static_cast<unsigned short>(GetCID()) & 0x2d) == 0x2d &&
		    static_cast<int>(PartPcs.m_usbStreamState.m_blockOnFrame) != 0) {
			return;
		}

		m_animFlagBits.bits.m_animRequested = 0;
		onFramePreCalc();

		if (m_stateFrameGate != 0) {
			m_stateFrameGate = 0;
		} else {
			m_stateFrame++;
		}

		if (m_subFrameGate != 0) {
			m_subFrameGate = 0;
		} else {
			m_subFrame++;
		}

		onFrameStat();
		onFramePostCalc();

		if (m_animFlagBits.bits.m_animRequested != 0) {
			if (m_reqAnimId == -1) {
				if (static_cast<int>(m_currentAnimSlot) >= 0) {
					m_lastBgAttr = 1.0f;
					CancelAnim(0);
				}
			} else if (m_animFlagBits.bits.m_animDirect != 0) {
				m_lastBgAttr = -1.0f;
				PlayAnim(m_reqAnimId, m_animFlagBits.bits.m_animLoop, 0, -1, -1, 0);
			} else {
				m_lastBgAttr = 1.0f;
				PlayAnim(m_reqAnimId, m_animFlagBits.bits.m_animLoop, 0, -1, -1, 0);
			}

			m_animFlagBits.bits.m_animRequested = 0;
		}
	}

    onFrameAlwaysAfter();
}

/*
 * --INFO--
 * PAL Address: 0x80127838
 * PAL Size: 164b
 * EN Address: 0x80126B68
 * EN Size: 164b
 * JP Address: 0x8012371C
 * JP Size: 164b
 */
void CGPrgObj::changeStat(int state, int subState, int stateArg)
{
	int oldState = getReplaceStat(state);
	if (oldState != -1) {
		onCancelStat(state);
		m_stateArg = stateArg;
		onChangeStat(state);
		m_lastStateId = oldState;
		m_stateFrame = 0;
		m_stateFrameGate = 1;
		m_subState = subState;
		m_subFrame = 0;
		m_subFrameGate = 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80127820
 * PAL Size: 24b
 * EN Address: 0x80126B50
 * EN Size: 24b
 * JP Address: 0x80123704
 * JP Size: 24b
 */
void CGPrgObj::changeSubStat(int subState)
{
	m_subState = subState;
	m_subFrame = 0;
	m_subFrameGate = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80127800
 * PAL Size: 32b
 * EN Address: 0x80126B30
 * EN Size: 32b
 * JP Address: 0x801236E4
 * JP Size: 32b
 */
void CGPrgObj::addSubStat()
{
	m_subState = m_subState + 1;
	m_subFrame = 0;
	m_subFrameGate = 1;
}

/*
 * --INFO--
 * PAL Address: 0x801277C8
 * PAL Size: 56b
 * EN Address: 0x80126AF8
 * EN Size: 56b
 * JP Address: 0x801236AC
 * JP Size: 56b
 */
void CGPrgObj::reqAnim(int animId, int loop, int direct)
{
	signed char loopFlag = loop;
	signed char directFlag = direct;

	m_animFlagBits.bits.m_animRequested = 1;
	m_reqAnimId = animId;
	m_animFlagBits.bits.m_animLoop = loopFlag;
	m_animFlagBits.bits.m_animDirect = directFlag;
}

/*
 * --INFO--
 * PAL Address: 0x8012776C
 * PAL Size: 92b
 * EN Address: 0x80126A9C
 * EN Size: 92b
 * JP Address: 0x80123650
 * JP Size: 92b
 */
int CGPrgObj::isLoopAnim()
{
	if (m_animFlagBits.bits.m_animLoop != 0 ||
	    m_animFlagBits.bits.m_animRequested != 0 || (IsLoopAnim(2) == 0)) {
		return 0;
	}

	return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80127720
 * PAL Size: 76b
 * EN Address: 0x80126A50
 * EN Size: 76b
 * JP Address: 0x80123604
 * JP Size: 76b
 */
int CGPrgObj::isLoopAnimDirect()
{
	signed char requestedFlag = m_animFlagBits.bits.m_animRequested;

	if ((requestedFlag != 0) || (IsLoopAnim(2) == 0)) {
		return 0;
	}

	return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80127650
 * PAL Size: 208b
 * EN Address: 0x80126980
 * EN Size: 208b
 * JP Address: 0x80123534
 * JP Size: 208b
 */
int CGPrgObj::playSe3D(int seNo, int volume, int dist, int pitch, Vec* pos)
{
	if (seNo == 0 || seNo == 0xffff) {
		return -1;
	}

	int handle = Sound.PlaySe3D(seNo, pos != nullptr ? pos : &m_worldPosition,
	                            static_cast<float>(volume), static_cast<float>(dist), 0);

	if (pitch != 0) {
		Sound.ChangeSe3DPitch(handle, pitch, 0);
	}

	return handle;
}

/*
 * --INFO--
 * PAL Address: 0x801275AC
 * PAL Size: 164b
 * EN Address: 0x801268DC
 * EN Size: 164b
 * JP Address: 0x80123490
 * JP Size: 164b
 */
void CGPrgObj::putParticle(int no, int dataNo, Vec* pos, float scale, int seNo)
{
	CFlatRuntime2Storage().ResetParticleWork(no, dataNo);
	CFlatRuntime2Storage().SetParticleWorkScale(scale);
	CFlatRuntime2Storage().SetParticleWorkPos(*pos, 0.0f);
	if (seNo != 0) {
		CFlatRuntime2Storage().SetParticleWorkSe(seNo, 2, 0);
	}
	CFlatRuntime2Storage().PutParticleWork();
}

/*
 * --INFO--
 * PAL Address: 0x80127510
 * PAL Size: 156b
 * EN Address: 0x80126840
 * EN Size: 156b
 * JP Address: 0x801233F4
 * JP Size: 156b
 */
void CGPrgObj::putParticle(int no, int dataNo, CGObject* traceObj, float scale, int seNo)
{
	CFlatRuntime2Storage().ResetParticleWork(no, dataNo);
	CFlatRuntime2Storage().SetParticleWorkScale(scale);
	CFlatRuntime2Storage().SetParticleWorkBind(this);
	if (seNo != 0) {
		CFlatRuntime2Storage().SetParticleWorkSe(seNo, 2, 0);
	}
	CFlatRuntime2Storage().PutParticleWork();
}

/*
 * --INFO--
 * PAL Address: 0x80127474
 * PAL Size: 156b
 * EN Address: 0x801267A4
 * EN Size: 156b
 * JP Address: 0x80123358
 * JP Size: 156b
 */
void CGPrgObj::putParticleTrace(int no, int dataNo, CGObject* obj, float scale, int seNo)
{
	CFlatRuntime2Storage().ResetParticleWork(no, dataNo);
	CFlatRuntime2Storage().SetParticleWorkScale(scale);
	CFlatRuntime2Storage().SetParticleWorkTrace(this);
	CFlatRuntime2Storage().PutParticleWork();
	if (seNo != 0) {
		CFlatRuntime2Storage().SetParticleWorkSe(seNo, 2, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801273BC
 * PAL Size: 184b
 * EN Address: 0x801266EC
 * EN Size: 184b
 * JP Address: 0x801232A0
 * JP Size: 184b
 */
void CGPrgObj::putParticleBindTrace(int no, int dataNo, CGObject* obj, float scale, int seNo)
{
	CFlatRuntime2Storage().ResetParticleWork(no, dataNo);
	CFlatRuntime2Storage().SetParticleWorkScale(scale);
	CFlatRuntime2Storage().SetParticleWorkBind(this);
	CFlatRuntime2Storage().SetParticleWorkTrace(obj);
	CFlatRuntime2Storage().PutParticleWork();
	if (seNo != 0) {
		CFlatRuntime2Storage().SetParticleWorkSe(seNo, 2, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012732C
 * PAL Size: 144b
 * EN Address: 0x8012665C
 * EN Size: 144b
 * JP Address: 0x80123210
 * JP Size: 144b
 */
float CGPrgObj::getTargetRot(CGPrgObj* target)
{
	float targetRot;
	float deltaX;
	float deltaZ;
	CVector deltaPos = CVector(m_worldPosition) - target->m_worldPosition;
	deltaX = deltaPos.x;
	deltaZ = deltaPos.z;
	if ((0.0f == deltaX) || (0.0f == deltaZ)) {
		targetRot = 0.0f;
	} else {
		targetRot = (float)atan2(-(double)deltaX, -(double)deltaZ);
	}

	return targetRot;
}

/*
 * --INFO--
 * PAL Address: 0x80127290
 * PAL Size: 156b
 * EN Address: 0x801265C0
 * EN Size: 156b
 * JP Address: 0x80123174
 * JP Size: 156b
 */
void CGPrgObj::rotTarget(CGPrgObj* target)
{
	m_rotTargetY = getTargetRot(target);
}

/*
 * --INFO--
 * PAL Address: 0x801271E0
 * PAL Size: 176b
 * EN Address: 0x80126510
 * EN Size: 176b
 * JP Address: 0x801230C4
 * JP Size: 176b
 */
float CGPrgObj::dstTargetRot(CGPrgObj* target)
{
	return Math.DstRot(m_rotBaseY, 3.1415927f + getTargetRot(target));
}

/*
 * --INFO--
 * PAL Address: 0x80127084
 * PAL Size: 348b
 * EN Address: 0x801263B4
 * EN Size: 348b
 * JP Address: 0x80122F68
 * JP Size: 348b
 */
void CGPrgObj::ClassControl(int classControl, int value)
{
	switch (classControl) {
	case 0:
		static_cast<CGPartyObj*>(this)->ChangeCommandMode(value);
		break;
	case 1:
		static_cast<CGPartyObj*>(this)->changeMotionMode(value);
		break;
	case 2:
		if (m_weaponNodeFlagBits.m_prg != value) {
			onChangePrg(value);
			m_weaponNodeFlagBits.m_prg = value;
		}
		break;
	case 3:
		static_cast<CGPartyObj*>(this)->m_partyData.flags.flag08 = static_cast<signed char>(value);
		break;
	case 4:
		changeStat(value, 0, 0);
		break;
	case 5:
		static_cast<CGCharaObj*>(this)->ClearAllSta();
		break;
	case 6:
		static_cast<CGCharaObj*>(this)->m_itemId = value;
		break;
	case 7:
		static_cast<CGPartyObj*>(this)->setAlive(1, 0);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80127028
 * PAL Size: 92b
 * EN Address: 0x80126358
 * EN Size: 92b
 * JP Address: 0x80122F0C
 * JP Size: 92b
 */
int CGPrgObj::GetClassControl(int classControl)
{
	switch (classControl) {
	case 8:
		return static_cast<CGPartyObj*>(this)->isDispTarget();
	case 9:
		return static_cast<CGPartyObj*>(this)->isRideTarget();
	case 10:
		return static_cast<CGCharaObj*>(this)->m_itemId;
	default:
		return 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80127024
 * PAL Size: 4b
 * EN Address: 0x80126354
 * EN Size: 4b
 * JP Address: 0x80122F08
 * JP Size: 4b
 */
void CGPrgObj::onChangePrg(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80127020
 * PAL Size: 4b
 * EN Address: 0x80126350
 * EN Size: 4b
 * JP Address: 0x80122F04
 * JP Size: 4b
 */
void CGPrgObj::onFrameStat()
{
}

/*
 * --INFO--
 * PAL Address: 0x8012701C
 * PAL Size: 4b
 * EN Address: 0x8012634C
 * EN Size: 4b
 * JP Address: 0x80122F00
 * JP Size: 4b
 */
void CGPrgObj::onFramePostCalc()
{
}

/*
 * --INFO--
 * PAL Address: 0x80127018
 * PAL Size: 4b
 * EN Address: 0x80126348
 * EN Size: 4b
 * JP Address: 0x80122EFC
 * JP Size: 4b
 */
void CGPrgObj::onFramePreCalc()
{
}

/*
 * --INFO--
 * PAL Address: 0x80127014
 * PAL Size: 4b
 * EN Address: 0x80126344
 * EN Size: 4b
 * JP Address: 0x80122EF8
 * JP Size: 4b
 */
void CGPrgObj::onChangeStat(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80127010
 * PAL Size: 4b
 * EN Address: 0x80126340
 * EN Size: 4b
 * JP Address: 0x80122EF4
 * JP Size: 4b
 */
void CGPrgObj::onCancelStat(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80127008
 * PAL Size: 8b
 * EN Address: 0x80126338
 * EN Size: 8b
 * JP Address: 0x80122EEC
 * JP Size: 8b
 */
int CGPrgObj::GetCID()
{
	return 13;
}

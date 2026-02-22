#include "ffcc/prgobj.h"
#include "ffcc/charaobj.h"
#include "ffcc/math.h"
#include "ffcc/partyobj.h"
#include "ffcc/sound.h"
#include "ffcc/vector.h"

#include <math.h>

extern "C" int PlaySe3D__6CSoundFiP3Vecffi(CSound*, int, Vec*, float, float, int);
extern "C" void ResetParticleWork__13CFlatRuntime2Fii(void*, int, int);
extern "C" void SetParticleWorkScale__13CFlatRuntime2Ff(void*, float);
extern "C" void SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject(void*, void*);
extern "C" void SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject(void*, void*);
extern "C" void SetParticleWorkPos__13CFlatRuntime2FR3Vecf(void*, Vec&, float);
extern "C" void SetParticleWorkSe__13CFlatRuntime2Fiii(void*, int, int, int);
extern "C" void PutParticleWork__13CFlatRuntime2Fv(void*);
extern CMath Math;
extern unsigned char CFlat[];

/*
 * --INFO--
 * PAL Address: 0x80127AF0
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onCreate()
{
	CGObject::onCreate();
	m_lastStateId = 0;
	m_stateArg = 0;
	m_animFlags &= 0x7F;
	m_animFlags &= 0xBF;
	m_animFlags &= 0xDF;
	m_reqAnimId = -1;
}

/*
 * --INFO--
 * PAL Address: 0x80127AD0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onDestroy()
{
	CGObject::onDestroy();
}

/*
 * --INFO--
 * PAL Address: 0x801278DC
 * PAL Size: 500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onFrame()
{
    onFrameAlways();

	if ((m_weaponNodeFlags & 0x8000) != 0) {
		m_animFlags &= 0x7f;
		onFramePreCalc();

		if (m_stateFrameGate == 0) {
			m_stateFrame++;
		} else {
			m_stateFrameGate = 0;
		}

		if (m_subFrameGate == 0) {
			m_subFrame++;
		} else {
			m_subFrameGate = 0;
		}

		onFrameStat();
		onFramePostCalc();

		if ((m_animFlags & 0x80) != 0) {
			if (m_reqAnimId == -1) {
				if (m_currentAnimSlot > -1) {
					*reinterpret_cast<float*>(m_lastBgAttr) = 0.0f;
					CancelAnim(0);
				}
			} else {
				if ((m_animFlags & 0x20) != 0) {
					*reinterpret_cast<float*>(m_lastBgAttr) = 1.0f;
				} else {
					*reinterpret_cast<float*>(m_lastBgAttr) = 0.0f;
				}

				PlayAnim(m_reqAnimId, (m_animFlags & 0x40) ? -1 : 0, 0, -1, -1, 0);
			}

			m_animFlags &= 0x7f;
		}
	}

    onFrameAlwaysAfter();
}

/*
 * --INFO--
 * PAL Address: 0x80127010
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onCancelStat(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80127014
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onChangeStat(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80127018
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onFramePreCalc()
{
}

/*
 * --INFO--
 * PAL Address: 0x8012701C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onFramePostCalc()
{
}

/*
 * --INFO--
 * PAL Address: 0x80127020
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onFrameStat()
{
}

/*
 * --INFO--
 * PAL Address: 0x80127024
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onChangePrg(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80127838
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::changeSubStat(int subState)
{
	m_subState = subState;
	m_subFrame = 0;
	m_subFrameGate = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::reqAnim(int animId, int loop, int direct)
{
	m_animFlags = (m_animFlags & 0x7f) | 0x80;
	m_reqAnimId = animId;
	m_animFlags = ((u8)loop << 6) | (m_animFlags & 0xbf);
	m_animFlags = ((u8)direct << 5) | (m_animFlags & 0xdf);
}

/*
 * --INFO--
 * PAL Address: 0x8012776C
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPrgObj::isLoopAnim()
{
	if ((m_animFlags & 0x80) != 0 || (m_animFlags & 0x40) != 0 || !IsLoopAnim(2)) {
		return 0;
	}

	return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80127720
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPrgObj::isLoopAnimDirect()
{
	if ((m_animFlags & 0x40) != 0 || !IsLoopAnim(2)) {
		return 0;
	}

	return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80127650
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPrgObj::playSe3D(int seNo, int volume, int dist, int pitch, Vec* pos)
{
	int handle;

	if (seNo == 0 || seNo == 0xFFFF) {
		return -1;
	}

	if (pos == nullptr) {
		pos = &m_worldPosition;
	}

	handle = PlaySe3D__6CSoundFiP3Vecffi(&Sound, seNo, pos, (float)volume, (float)dist, 0);

	if (pitch != 0) {
		Sound.ChangeSe3DPitch(handle, pitch, 0);
	}

	return handle;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::changePrg(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801275AC
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::putParticle(int no, int dataNo, Vec* pos, float scale, int seNo)
{
	ResetParticleWork__13CFlatRuntime2Fii(CFlat, no, dataNo);
	SetParticleWorkScale__13CFlatRuntime2Ff(CFlat, scale);
	SetParticleWorkPos__13CFlatRuntime2FR3Vecf(CFlat, *pos, 0.0f);
	if (seNo != 0) {
		SetParticleWorkSe__13CFlatRuntime2Fiii(CFlat, seNo, 2, 0);
	}
	PutParticleWork__13CFlatRuntime2Fv(CFlat);
}

/*
 * --INFO--
 * PAL Address: 0x80127510
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::putParticle(int no, int dataNo, CGObject* traceObj, float scale, int seNo)
{
	ResetParticleWork__13CFlatRuntime2Fii(CFlat, no, dataNo);
	SetParticleWorkScale__13CFlatRuntime2Ff(CFlat, scale);
	SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject(CFlat, this);
	if (seNo != 0) {
		SetParticleWorkSe__13CFlatRuntime2Fiii(CFlat, seNo, 2, 0);
	}
	PutParticleWork__13CFlatRuntime2Fv(CFlat);
}

/*
 * --INFO--
 * PAL Address: 0x80127474
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::putParticleTrace(int no, int dataNo, CGObject* obj, float scale, int seNo)
{
	ResetParticleWork__13CFlatRuntime2Fii(CFlat, no, dataNo);
	SetParticleWorkScale__13CFlatRuntime2Ff(CFlat, scale);
	SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject(CFlat, this);
	PutParticleWork__13CFlatRuntime2Fv(CFlat);
	if (seNo != 0) {
		SetParticleWorkSe__13CFlatRuntime2Fiii(CFlat, seNo, 2, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801273BC
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::putParticleBindTrace(int no, int dataNo, CGObject* obj, float scale, int seNo)
{
	ResetParticleWork__13CFlatRuntime2Fii(CFlat, no, dataNo);
	SetParticleWorkScale__13CFlatRuntime2Ff(CFlat, scale);
	SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject(CFlat, this);
	SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject(CFlat, obj);
	PutParticleWork__13CFlatRuntime2Fv(CFlat);
	if (seNo != 0) {
		SetParticleWorkSe__13CFlatRuntime2Fiii(CFlat, seNo, 2, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012732C
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CGPrgObj::getTargetRot(CGPrgObj* target)
{
	float targetRot;
	CVector targetPos(target->m_worldPosition);
	CVector basePos(m_worldPosition);
	CVector deltaPos;

	PSVECSubtract(reinterpret_cast<Vec*>(&basePos), reinterpret_cast<Vec*>(&targetPos), reinterpret_cast<Vec*>(&deltaPos));
	targetRot = 0.0f;
	if (deltaPos.x != 0.0f && deltaPos.z != 0.0f) {
		targetRot = (float)atan2(-(double)deltaPos.x, -(double)deltaPos.z);
	}

	return targetRot;
}

/*
 * --INFO--
 * PAL Address: 0x80127290
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::rotTarget(CGPrgObj* target)
{
	float targetRot;
	CVector targetPos(target->m_worldPosition);
	CVector basePos(m_worldPosition);
	CVector deltaPos;

	PSVECSubtract(reinterpret_cast<Vec*>(&basePos), reinterpret_cast<Vec*>(&targetPos), reinterpret_cast<Vec*>(&deltaPos));
	targetRot = 0.0f;
	if (deltaPos.x != 0.0f && deltaPos.z != 0.0f) {
		targetRot = (float)atan2(-(double)deltaPos.x, -(double)deltaPos.z);
	}

	m_rotTargetY = targetRot;
}

/*
 * --INFO--
 * PAL Address: 0x801271E0
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::dstTargetRot(CGPrgObj* target)
{
	float targetRot;
	CVector targetPos(target->m_worldPosition);
	CVector basePos(m_worldPosition);
	CVector deltaPos;

	PSVECSubtract(reinterpret_cast<Vec*>(&basePos), reinterpret_cast<Vec*>(&targetPos), reinterpret_cast<Vec*>(&deltaPos));
	targetRot = 0.0f;
	if (deltaPos.x != 0.0f && deltaPos.z != 0.0f) {
		targetRot = (float)atan2(-(double)deltaPos.x, -(double)deltaPos.z);
	}

	Math.DstRot(m_rotBaseY, 3.1415927f + targetRot);
}

/*
 * --INFO--
 * PAL Address: 0x80127084
 * PAL Size: 348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::ClassControl(int classControl, int value)
{
	switch (classControl) {
	case 0:
		reinterpret_cast<CGPartyObj*>(this)->ChangeCommandMode(value);
		break;
	case 1:
		reinterpret_cast<CGPartyObj*>(this)->changeMotionMode(value);
		break;
	case 2:
		if ((((char)m_weaponNodeFlags) >> 7) != value) {
			onChangePrg(value);
			m_weaponNodeFlags = (m_weaponNodeFlags & 0x7FFF) | ((value & 1) << 15);
		}
		break;
	case 3:
	{
		unsigned char* classFlags = reinterpret_cast<unsigned char*>(this) + 0x6B8;
		*classFlags = (*classFlags & 0xF7) | ((value & 1) << 3);
		break;
	}
	case 4:
	{
		int oldState = getReplaceStat(value);
		if (oldState != -1) {
			onCancelStat(value);
			m_stateArg = 0;
			onChangeStat(value);
			m_lastStateId = oldState;
			m_stateFrame = 0;
			m_stateFrameGate = 1;
			m_subState = 0;
			m_subFrame = 0;
			m_subFrameGate = 1;
		}
		break;
	}
	case 5:
		reinterpret_cast<CGCharaObj*>(this)->ClearAllSta();
		break;
	case 6:
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x560) = value;
		break;
	case 7:
		reinterpret_cast<CGPartyObj*>(this)->setAlive(1, 0);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80127028
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPrgObj::GetClassControl(int classControl)
{
	if (classControl == 9) {
		return reinterpret_cast<CGPartyObj*>(this)->isRideTarget();
	}

	if (classControl == 8) {
		return reinterpret_cast<CGPartyObj*>(this)->isDispTarget();
	}

	if (classControl == 10) {
		return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x560);
	}

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGPrgObj::GetCID()
{
	return 13;
}

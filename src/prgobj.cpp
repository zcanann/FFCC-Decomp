#include "ffcc/prgobj.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::onCreate()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::onDestroy()
{
	// TODO
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
	m_animFlags = ((loop << 6) & 0x40) | (m_animFlags & 0xbf);
	m_animFlags = ((direct << 5) & 0x20) | (m_animFlags & 0xdf);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::isLoopAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::isLoopAnimDirect()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::playSe3D(int, int, int, int, Vec*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::putParticle(int, int, Vec*, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::putParticle(int, int, CGObject*, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::putParticleTrace(int, int, CGObject*, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::putParticleBindTrace(int, int, CGObject*, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::getTargetRot(CGPrgObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::rotTarget(CGPrgObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::dstTargetRot(CGPrgObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::ClassControl(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::GetClassControl(int)
{
	// TODO
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

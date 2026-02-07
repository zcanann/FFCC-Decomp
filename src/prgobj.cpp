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
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::onFrame()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::changeStat(int, int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGPrgObj::reqAnim(int, int, int)
{
	// TODO
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

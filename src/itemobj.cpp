#include "ffcc/itemobj.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onCreate()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onDestroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onFramePreCalc()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80126f08
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onFramePostCalc()
{
	unsigned char* self = (unsigned char*)this;
	unsigned int stateBits = ((unsigned int)self[0x50] << 0x1c) | ((unsigned int)self[0x50] >> 4);

	if ((int)stateBits < 0 && *(int*)(self + 0x550) == 0) {
		*(int*)(self + 0x94) = *(int*)(self + 0x94) - 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80126ee0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onChangeStat(int state)
{
	unsigned char* self = (unsigned char*)this;

	if (state >= 0x26 && state <= 0x27) {
		*(unsigned int*)(self + 0x1c0) = *(unsigned int*)(self + 0x1c0) & 0xfff7fffe;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80126eb4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onCancelStat(int)
{
	extern float FLOAT_80331b18;
	unsigned char* self = (unsigned char*)this;

	if (*(int*)(self + 0x520) == 0x1b) {
		*(unsigned int*)(self + 0x1c0) = *(unsigned int*)(self + 0x1c0) | 2;
		*(float*)(self + 0x17c) = FLOAT_80331b18;
		*(float*)(self + 0x178) = FLOAT_80331b18;
		*(float*)(self + 0x174) = FLOAT_80331b18;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onFrameStat()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::DeleteOld(int, int, CFlatRuntime::CObject*, CFlatRuntime::CObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::CanCreateFromScript()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::CreateFromScript(int, int, int, CGObject*, float, CGItemObj::CCFS*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::safeDetach(int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::carry(CGPartyObj*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onChangePrg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::statPot()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onFrameAlways()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onHitParticle(int, int, int, int, Vec*, PPPIFPARAM*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::loadModel()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80124fac
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onNewFinished()
{
	extern int DAT_8032ee90;
	unsigned char* self = (unsigned char*)this;

	*(int*)(self + 0x568) = *(int*)(self + 0x144);
	*(unsigned short*)(self + 0x560) = (unsigned short)((DAT_8032ee90 >> 3) & 1);
	loadModel();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::DrawOmoideName(CFont*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::ItemJump(int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::DeleteAllFieldItem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::DispAllFieldItem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGItemObj::GetCID()
{
	return 0;
}

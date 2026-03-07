#include "ffcc/baseobj.h"

extern unsigned char CFlat[];

void CGBaseObj::onCreate()
{
}

void CGBaseObj::onDestroy()
{
}

void CGBaseObj::onDraw()
{
}

void CGBaseObj::onFrame()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::onTalk(CGBaseObj* other, int param_3)
{
	CFlatRuntime::CStack stack[2];
	stack[0].m_word = (u32)other->m_particleId;
	stack[1].m_word = (u32)param_3;
	reinterpret_cast<CFlatRuntime*>(CFlat)->SystemCall(this, 2, 6, 2, stack, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::onPush(CGBaseObj* other, int param_3)
{
	CFlatRuntime::CStack stack[2];
	stack[0].m_word = (u32)other->m_particleId;
	stack[1].m_word = (u32)param_3;
	reinterpret_cast<CFlatRuntime*>(CFlat)->SystemCall(this, 2, 4, 2, stack, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::Draw()
{
	onDraw();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::Frame()
{
	onFrame();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::Destroy()
{
	onDestroy();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::Create()
{
	onCreate();
}

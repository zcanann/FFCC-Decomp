#include "ffcc/baseobj.h"

#include "global.h"

extern __declspec(section ".data") CFlatRuntime CFlat;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::onPush(CGBaseObj* other, int param_3)
{
	u32 stack[2];
	stack[0] = (u32)other->m_particleId;
	stack[1] = (u32)param_3;
	CFlat.SystemCall(this, 2, 4, 2, (CFlatRuntime::CStack*)stack, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::onTalk(CGBaseObj* other, int param_3)
{
	u32 stack[2];
	stack[0] = (u32)other->m_particleId;
	stack[1] = (u32)param_3;
	CFlat.SystemCall(this, 2, 6, 2, (CFlatRuntime::CStack*)stack, 0);
}

void CGBaseObj::onCreate()
{
}

void CGBaseObj::onDestroy()
{
}

void CGBaseObj::onFrame()
{
}

void CGBaseObj::onDraw()
{
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
void CGBaseObj::Frame()
{
	onFrame();
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

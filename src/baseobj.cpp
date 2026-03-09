#include "ffcc/baseobj.h"
#include "ffcc/cflat_runtime2.h"

extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    CFlatRuntime*, CFlatRuntime::CObject*, int, int, int, CFlatRuntime::CStack*, CFlatRuntime::CStack*);

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
 * PAL Address: 0x8010b15c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGBaseObj::onTalk(CGBaseObj* other, int param_3)
{
	CFlatRuntime::CStack stack[2];
	stack[0].m_word = (u32)other->m_particleId;
	stack[1].m_word = (u32)param_3;
	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	    reinterpret_cast<CFlatRuntime*>(CFlat), this, 2, 6, 2, stack, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8010b1a8
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGBaseObj::onPush(CGBaseObj* other, int param_3)
{
	CFlatRuntime::CStack stack[2];
	stack[0].m_word = (u32)other->m_particleId;
	stack[1].m_word = (u32)param_3;
	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	    reinterpret_cast<CFlatRuntime*>(CFlat), this, 2, 4, 2, stack, 0);
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

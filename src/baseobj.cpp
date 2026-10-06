#include "ffcc/baseobj.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/linkage.h"

/*
 * --INFO--
 * PAL Address: 0x8010B150
 * PAL Size: 4b
 * EN Address: 0x8010A4C8
 * EN Size: 4b
 * JP Address: 0x801071C8
 * JP Size: 4b
 */
void CGBaseObj::onCreate()
{
}

/*
 * --INFO--
 * PAL Address: 0x8010B154
 * PAL Size: 4b
 * EN Address: 0x8010A4CC
 * EN Size: 4b
 * JP Address: 0x801071CC
 * JP Size: 4b
 */
void CGBaseObj::onDestroy()
{
}

/*
 * --INFO--
 * PAL Address: 0x8010B158
 * PAL Size: 4b
 * EN Address: 0x8010A4D0
 * EN Size: 4b
 * JP Address: 0x801071D0
 * JP Size: 4b
 */
void CGBaseObj::onDraw()
{
}

/*
 * --INFO--
 * PAL Address: 0x8010B15C
 * PAL Size: 76b
 * EN Address: 0x8010A4D4
 * EN Size: 76b
 * JP Address: 0x801071D4
 * JP Size: 76b
 */
void CGBaseObj::onTalk(CGBaseObj* other, int talkType)
{
	CFlatRuntime::CStack stack[2];
	stack[0].m_word = (u32)other->m_particleId;
	stack[1].m_word = (u32)talkType;
	gCFlatRuntime().SystemCall(this, 2, 6, 2, stack, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8010B1A8
 * PAL Size: 76b
 * EN Address: 0x8010A520
 * EN Size: 76b
 * JP Address: 0x80107220
 * JP Size: 76b
 */
void CGBaseObj::onPush(CGBaseObj* other, int pushType)
{
	CFlatRuntime::CStack stack[2];
	stack[0].m_word = (u32)other->m_particleId;
	stack[1].m_word = (u32)pushType;
	gCFlatRuntime().SystemCall(this, 2, 4, 2, stack, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8010B1F4
 * PAL Size: 44b
 * EN Address: 0x8010A56C
 * EN Size: 44b
 * JP Address: 0x8010726C
 * JP Size: 44b
 */
void CGBaseObj::Draw()
{
	onDraw();
}

/*
 * --INFO--
 * PAL Address: 0x8010B220
 * PAL Size: 44b
 * EN Address: 0x8010A598
 * EN Size: 44b
 * JP Address: 0x80107298
 * JP Size: 44b
 */
void CGBaseObj::Frame()
{
	onFrame();
}

/*
 * --INFO--
 * PAL Address: 0x8010B24C
 * PAL Size: 44b
 * EN Address: 0x8010A5C4
 * EN Size: 44b
 * JP Address: 0x801072C4
 * JP Size: 44b
 */
void CGBaseObj::Destroy()
{
	onDestroy();
}

/*
 * --INFO--
 * PAL Address: 0x8010B278
 * PAL Size: 44b
 * EN Address: 0x8010A5F0
 * EN Size: 44b
 * JP Address: 0x801072F0
 * JP Size: 44b
 */
void CGBaseObj::Create()
{
	onCreate();
}

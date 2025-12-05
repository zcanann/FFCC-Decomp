#include "ffcc/baseobj.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::onPush(CGBaseObj* other, int)
{
	/*
	int particle_id = (int)(other->object).m_particleId;
	CFlat.SystemCall(this, 2, 4, 2, &particle_id, 0);
	*/
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGBaseObj::onTalk(CGBaseObj* other, int param_3)
{
	/*
	int particle_id = (int)(other->object).m_particleId;
	CFlat.SystemCall(this, 2, 6, 2, &particle_id, 0);
	*/
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

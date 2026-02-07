#include "ffcc/cflat_r2system.h"
#include "ffcc/game.h"

/*
 * --INFO--
 * PAL Address: 0x800B8F80
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::SetNextScriptNewGame()
{
    m_nextScript.m_flags = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onSystemFunc(CFlatRuntime::CObject*, int, int, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onSystemVal(CFlatRuntime::CObject*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onSetSystemVal(int, CFlatRuntime::CStack*, int)
{
	// TODO
}

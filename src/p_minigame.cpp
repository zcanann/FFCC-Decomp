#include "ffcc/p_minigame.h"

extern CMiniGamePcs MiniGamePcs;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ChgHL16(unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MiniGameFileRead(char*, void*, unsigned long&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalcCrc(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void AdjustGbaImageRegistry(char*, char*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8012b09c
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _OpenCallback(MgGbaThreadParam* param, void* context)
{
    MiniGamePcs.OpenCallback(param, context);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void getKoubutsuList(unsigned char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaThreadAlarmHandler(OSAlarm*, OSContext*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaThreadSleep(long long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaThreadReadInitialCode(MgGbaThreadParam*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801290a0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GbaThreadMain(void* param)
{
    MiniGamePcs.GbaThreadMain(param);
}

/*
 * --INFO--
 * PAL Address: 0x80128574
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _MngThreadMain(void* param)
{
    MiniGamePcs.MngThreadMain(param);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMiniGamePcs::CMiniGamePcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::MiniGameGo(char*, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GbaThreadInitGbaContext(MgGbaThreadParam*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GbaThreadWriteInitialCode(MgGbaThreadParam*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GbaThreadReadContext(MgGbaThreadParam*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GbaThreadMain(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GbaThreadInit(long, MgGbaThreadParam*, OSThread*, unsigned char*, unsigned long, long, void (*) (MgGbaThreadParam*, void*), unsigned char*, long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::OpenCallback(MgGbaThreadParam*, void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::PadCodeProc(int, unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::EndThread()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::MngThreadMain(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::MiniGameEnd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::CallMiniGameParam(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::SetNumPlayer()
{
	// TODO
}

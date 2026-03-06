#include "ffcc/p_gba.h"
#include "ffcc/joybus.h"
#include "ffcc/gbaque.h"
#include "ffcc/memory.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/system.h"
#include <dolphin/gba/GBA.h>

CGbaPcs GbaPcs;
extern char __vt__8CManager[];
extern char PTR_PTR_s_CGbaPcs_8020f4a4[];
extern char s_CGbaPcs_80330870[];
extern char s_JoyBus__LoadBin___error_801d9de0[];

/*
 * --INFO--
 * PAL Address: 0x800979f4
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_gba_cpp(void)
{
	*reinterpret_cast<void**>(&GbaPcs) = __vt__8CManager;
	*reinterpret_cast<void**>(&GbaPcs) = __vt__8CProcess;
	*reinterpret_cast<void**>(&GbaPcs) = PTR_PTR_s_CGbaPcs_8020f4a4;

	unsigned int* table = gGbaStatusWordTable;
	table[1] = gGbaStatusWordTriplet0[0];
	table[2] = gGbaStatusWordTriplet0[1];
	table[3] = gGbaStatusWordTriplet0[2];
	table[4] = gGbaStatusWordTriplet1[0];
	table[5] = gGbaStatusWordTriplet1[1];
	table[6] = gGbaStatusWordTriplet1[2];
	table[7] = gGbaStatusWordTriplet2[0];
	table[8] = gGbaStatusWordTriplet2[1];
	table[9] = gGbaStatusWordTriplet2[2];
	table[12] = gGbaStatusWordTriplet3[0];
	table[13] = gGbaStatusWordTriplet3[1];
	table[14] = gGbaStatusWordTriplet3[2];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGbaPcs::CGbaPcs() : CProcess()
{
}

/*
 * --INFO--
 * PAL Address: 0x800979cc
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::Init()
{
	m_stage = (CMemory::CStage*)0;
	GBAInit();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGbaPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800979b4
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CGbaPcs::GetTable(unsigned long tableIndex)
{
	unsigned long offset = tableIndex;
	offset *= 0x15c;
	return reinterpret_cast<unsigned char*>(gGbaStatusWordTable) + offset;
}

/*
 * --INFO--
 * PAL Address: 0x80097918
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::create()
{
	m_stage = Memory.CreateStage(0x56000, s_CGbaPcs_80330870, 0);
	Joybus.CreateInit();
	int result = Joybus.LoadBin();
	if ((result != 0) && (2 <= (unsigned int)System.m_execParam)) {
		System.Printf(s_JoyBus__LoadBin___error_801d9de0);
	}
	Joybus.ThreadInit();
}

/*
 * --INFO--
 * PAL Address: 0x800978d4
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::destroy()
{
	Joybus.Destroy();
	Memory.DestroyStage(m_stage);
}

/*
 * --INFO--
 * PAL Address: 0x8009788c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::calc()
{
	if (Joybus.IsThreadRunning()) {
		GbaQue.ExecutQueue();
		GbaQue.LoadAll();
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGbaPcs::draw()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009782c
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::onMapChanging(int stageNo1, int stageNo2)
{
	if (Joybus.IsThreadRunning()) {
		GbaQue.SetStageNo(stageNo1, stageNo2);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGbaPcs::onMapChanged(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80097800
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::onScriptChanging(char*)
{
	GbaQue.ClrScrInitEnd();
}

/*
 * --INFO--
 * PAL Address: 0x800977d8
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::SetFirstZone()
{
	GbaQue.ClrRadarTypeFlg();
}


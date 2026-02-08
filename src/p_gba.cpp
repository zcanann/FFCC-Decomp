#include "ffcc/p_gba.h"
#include "ffcc/joybus.h"
#include "ffcc/gbaque.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#include <dolphin/gba/GBA.h>

CGbaPcs GbaPcs;

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
	extern unsigned char lbl_8020F328[];
	unsigned long offset = tableIndex;
	offset *= 0x15c;
	return lbl_8020F328 + offset;
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
	m_stage = Memory.CreateStage(0x56000, "CGbaPcs", 0);
	Joybus.CreateInit();
	int result = Joybus.LoadBin();
	if (result != 0 && System.m_execParam > 1) {
		System.Printf("JoyBus::LoadBin() error");
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

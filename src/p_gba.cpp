#include "ffcc/p_gba.h"
#include "ffcc/joybus.h"
#include "ffcc/gbaque.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#include <dolphin/gba/GBA.h>

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CGbaPcs::CGbaPcs()
{
}

CGbaPcs GbaPcs;

CProcessCallbackTable CGbaPcs::m_table = {
    "CGbaPcs",
    static_cast<CProcessCallback>(&CGbaPcs::create),
    static_cast<CProcessCallback>(&CGbaPcs::destroy),
    {
        {static_cast<CProcessCallback>(&CGbaPcs::calc), 0x23, 0},
        {static_cast<CProcessCallback>(&CGbaPcs::draw), 0x45, 1},
    },
};

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
 * PAL Address: 0x800979c8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::Quit()
{
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
int CGbaPcs::GetTable(unsigned long tableIndex)
{
	return reinterpret_cast<int>(&m_table + tableIndex);
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
	if ((result != 0) && (2 <= (unsigned int)System.m_execParam)) {
		System.Printf("JoyBus::LoadBin() error\n");
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
 * PAL Address: 0x80097888
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::draw()
{
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
 * PAL Address: 0x80097828
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::onMapChanged(int, int, int)
{
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

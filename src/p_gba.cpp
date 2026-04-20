#include "ffcc/p_gba.h"
#include "ffcc/joybus.h"
#include "ffcc/gbaque.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#include <dolphin/gba/GBA.h>

extern "C" void create__7CGbaPcsFv(CGbaPcs*);
extern "C" void destroy__7CGbaPcsFv(CGbaPcs*);
extern "C" void calc__7CGbaPcsFv(CGbaPcs*);
extern "C" void draw__7CGbaPcsFv(CGbaPcs*);
extern const char s_CGbaPcs_80330870[];
extern const char s_JoyBus__LoadBin___error_801d9de0[];

const char s_CGbaPcs_80330870[] = "CGbaPcs";
const char s_JoyBus__LoadBin___error_801d9de0[] = "JoyBus::LoadBin() error\n";

CGbaPcsTable m_table__7CGbaPcs = {
    const_cast<char*>(s_CGbaPcs_80330870),
    {
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000023,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000045,
        0x00000001,
    },
};

CGbaPcs GbaPcs;

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
 * Address:	TODO
 * Size:	TODO
 */
void CGbaPcs::onMapChanged(int, int, int)
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
void CGbaPcs::draw()
{
	// TODO
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
 * PAL Address: 0x80097918
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGbaPcs::create()
{
	m_stage = Memory.CreateStage(0x56000, const_cast<char*>(s_CGbaPcs_80330870), 0);
	Joybus.CreateInit();
	int result = Joybus.LoadBin();
	if ((result != 0) && (2 <= (unsigned int)System.m_execParam)) {
		System.Printf(const_cast<char*>(s_JoyBus__LoadBin___error_801d9de0));
	}
	Joybus.ThreadInit();
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
	unsigned long offset = tableIndex;
	offset *= 0x15c;
	return (int)(reinterpret_cast<unsigned char*>(&m_table__7CGbaPcs) + offset);
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
 * PAL Address: 0x800979f4
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CGbaPcs::CGbaPcs()
{
	unsigned int* table = reinterpret_cast<unsigned int*>(&m_table__7CGbaPcs);
	const unsigned int* desc0 = m_table_desc0__7CGbaPcs;
	const unsigned int* desc1 = m_table_desc1__7CGbaPcs;
	const unsigned int* desc2 = m_table_desc2__7CGbaPcs;
	const unsigned int* desc3 = m_table_desc3__7CGbaPcs;

	table[1] = desc0[0];
	table[2] = desc0[1];
	table[3] = desc0[2];
	table[4] = desc1[0];
	table[5] = desc1[1];
	table[6] = desc1[2];
	table[7] = desc2[0];
	table[8] = desc2[1];
	table[9] = desc2[2];
	table[12] = desc3[0];
	table[13] = desc3[1];
	table[14] = desc3[2];
}

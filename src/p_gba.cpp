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

unsigned int gGbaStatusWordTriplet0[] = {0x00000000, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__7CGbaPcsFv)};
unsigned int gGbaStatusWordTriplet1[] = {0x00000000, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CGbaPcsFv)};
unsigned int gGbaStatusWordTriplet2[] = {0x00000000, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__7CGbaPcsFv)};
unsigned int gGbaStatusWordTriplet3[] = {0x00000000, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__7CGbaPcsFv)};
unsigned int gGbaStatusWordTable[0x57] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(s_CGbaPcs_80330870)), 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000023, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000045, 0x00000001,
};

const char s_CGbaPcs_80330870[] = "CGbaPcs";
const char s_JoyBus__LoadBin___error_801d9de0[] = "JoyBus::LoadBin() error\n";

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
	return (int)(reinterpret_cast<unsigned char*>(gGbaStatusWordTable) + offset);
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
CGbaPcs::CGbaPcs()
{
	unsigned int* table = &gGbaStatusWordTable[1];
	table[0] = gGbaStatusWordTriplet0[0];
	table[1] = gGbaStatusWordTriplet0[1];
	table[2] = gGbaStatusWordTriplet0[2];
	table[3] = gGbaStatusWordTriplet1[0];
	table[4] = gGbaStatusWordTriplet1[1];
	table[5] = gGbaStatusWordTriplet1[2];
	table[6] = gGbaStatusWordTriplet2[0];
	table[7] = gGbaStatusWordTriplet2[1];
	table[8] = gGbaStatusWordTriplet2[2];
	table[11] = gGbaStatusWordTriplet3[0];
	table[12] = gGbaStatusWordTriplet3[1];
	table[13] = gGbaStatusWordTriplet3[2];
}

CGbaPcs GbaPcs;

#include "ffcc/pppYmMelt.h"
#include "ffcc/pppPart.h"

extern float lbl_80330AF0;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void InitPolygonData(PYmMelt*, VERTEX_DATA*, short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalcPolygonHeight(PYmMelt*, VERTEX_DATA*, _GXColor*, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800A5D20
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMelt(PYmMelt* pppYmMelt, PYmMeltDataOffsets* param_2)
{
    f32 value = lbl_80330AF0;
    u8* work = (u8*)pppYmMelt + *param_2->m_serializedDataOffsets + 0x80;

    *(u32*)(work + 0x0) = 0;
    *(u16*)(work + 0x4) = 0;
    *(u16*)(work + 0xA) = 0;
    *(u16*)(work + 0x8) = 0;
    *(u16*)(work + 0x6) = 0;

    *(f32*)(work + 0x14) = value;
    *(f32*)(work + 0x10) = value;
    *(f32*)(work + 0xC) = value;
}

/*
 * --INFO--
 * PAL Address: 0x800A5CE8
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMelt(PYmMelt* pppYmMelt, PYmMeltDataOffsets* param_2)
{
    CMemory::CStage* stage =
        *(CMemory::CStage**)((u8*)pppYmMelt + *param_2->m_serializedDataOffsets + 0x80);
    if (stage != nullptr) {
        pppHeapUseRate(stage);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameYmMelt(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderYmMelt(void)
{
	// TODO
}

#include "ffcc/pppYmMegaBirthShpTail2.h"
#include "ffcc/pppPart.h"

extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern "C" void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
extern float lbl_80330560;
extern pppFMATRIX g_matUnit2;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void get_rand()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void U8ToF32(pppFVECTOR4*, unsigned char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void alloc_check(VYmMegaBirthShpTail2* vdata, PYmMegaBirthShpTail2* param)
{
	vdata->m_maxParticles = *(unsigned short*)((char*)&param->m_matrix + 0xe);
	// TODO: Proper memory allocation
	vdata->m_particles = (_PARTICLE_DATA*)0;
	vdata->m_wmats = (_PARTICLE_WMAT*)0;
	vdata->m_colors = (_PARTICLE_COLOR*)0;
}

/*
 * --INFO--
 * PAL Address: 0x8008ca1c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, UnkC* param2)
{
    pppFMATRIX* work = (pppFMATRIX*)((u8*)param1 + 0x80 + param2->m_serializedDataOffsets[2]);
    float initVal;

    pppUnitMatrix__FR10pppFMATRIX(work);
    initVal = lbl_80330560;

    work[1].value[0][2] = initVal;
    work[1].value[0][1] = initVal;
    work[1].value[0][0] = initVal;
    work[1].value[0][3] = 0.0f;
    work[1].value[1][0] = 0.0f;
    work[1].value[1][1] = 0.0f;
    work[1].value[1][2] = 0.0f;
    *(u16*)(work[1].value[1] + 3) = 0;
    *(u16*)((u8*)work[1].value[1] + 0xe) = 0;
    *(u16*)(work[1].value[1] + 3) = 10000;
    pppUnitMatrix__FR10pppFMATRIX(&g_matUnit2);
}

/*
 * --INFO--
 * PAL Address: 0x8008c9a0
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, UnkC* param2)
{
    u8* work = (u8*)param1 + 0x80 + param2->m_serializedDataOffsets[2];
    void** ptrBc = (void**)(work + 0x3c);
    void** ptrC0 = (void**)(work + 0x40);
    void** ptrC4 = (void**)(work + 0x44);

    if (*ptrBc != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*ptrBc);
        *ptrBc = 0;
    }
    if (*ptrC0 != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*ptrC0);
        *ptrC0 = 0;
    }
    if (*ptrC4 != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*ptrC4);
        *ptrC4 = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void birth(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calc(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calc_particle(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8008b3f4
 * PAL Size: 1072b
 */
void pppFrameYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, UnkC*)
{
	// TODO: Implement frame processing
}

/*
 * --INFO--
 * PAL Address: 0x8008acc4
 * PAL Size: 1840b
 */
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, UnkB*, UnkC*)
{
	// TODO: Implement rendering
}

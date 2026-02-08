#include "ffcc/pppColum.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

extern int lbl_8032ED70;
extern CMath Math;
extern void* DAT_8032ec70;

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
float RandF__5CMathFf(float, CMath*);
unsigned char GetNoise__5CUtilFUc(void*, unsigned int);
void pppCalcFrameShape__FPlRsRsRss(long*, short&, short&, short&, short);
}

/*
 * --INFO--
 * PAL Address: 0x800df2f8
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructColum(pppColum *column, UnkC *param_2)
{
    unsigned short *puVar1 = (unsigned short *)((char*)column + 0x80 + param_2->m_serializedDataOffsets[3]);
    puVar1[2] = 0;
    puVar1[1] = 0;
    *puVar1 = 0;
    *(unsigned int *)(puVar1 + 4) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800df2ac
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructColum(pppColum *column, UnkC *param_2)
{
    char* work = (char*)column + 0x80 + param_2->m_serializedDataOffsets[3];

    if (*(CMemory::CStage**)(work + 8) != 0) {
        pppHeapUseRate(*(CMemory::CStage**)(work + 8));
        *(void**)(work + 8) = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800df168
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameColum(pppColum *column, UnkB *param_2, UnkC *param_3)
{
    if (lbl_8032ED70 == 0) {
        unsigned char* work = (unsigned char*)((char*)column + 0x80 + param_3->m_serializedDataOffsets[3]);

        if (*(void**)(work + 8) == 0) {
            float* values = (float*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                (unsigned long)(*((unsigned char*)&param_2->m_arg3 + 1) * 0xc),
                pppEnvStPtr->m_stagePtr, (char*)"pppColum.cpp", 0x7d);
            int i;
            unsigned char count = *((unsigned char*)&param_2->m_arg3 + 1);

            *(void**)(work + 8) = values;
            for (i = 0; i < count; i++) {
                values[0] = RandF__5CMathFf(*(float*)(param_2->m_payload + 4), &Math);
                values[0] += *(float*)param_2->m_payload;
                values[1] = RandF__5CMathFf(*(float*)(param_2->m_payload + 0xc), &Math);
                values[1] += *(float*)(param_2->m_payload + 8);
                ((unsigned char*)values)[8] =
                    GetNoise__5CUtilFUc(&DAT_8032ec70, (unsigned char)param_2->m_payload[0x16]);
                ((unsigned char*)values)[9] =
                    GetNoise__5CUtilFUc(&DAT_8032ec70, (unsigned char)param_2->m_payload[0x17]);
                ((unsigned char*)values)[10] =
                    GetNoise__5CUtilFUc(&DAT_8032ec70, (unsigned char)param_2->m_payload[0x18]);
                values += 3;
            }
        }

        if (param_2->m_dataValIndex != 0xffff) {
            long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + param_2->m_dataValIndex * 4);
            pppCalcFrameShape__FPlRsRsRss(shapeTable, *(short*)(work + 0), *(short*)(work + 2),
                                          *(short*)(work + 4), (short)param_2->m_initWOrk);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800dec5c
 * PAL Size: 1292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderColum(pppColum *column, UnkB *param_2, UnkC *param_3)
{
    int iVar7 = param_3->m_serializedDataOffsets[3];
    int iVar5 = param_3->m_serializedDataOffsets[2];
    
    if (param_2->m_dataValIndex != 0xffff) {
        // TODO: Get texture and shape data
        // pppShapeSt *shapeSt = ...;
        
        // TODO: Check if column data is active
        // if (column->field_0xb2[iVar5] != 0) {
            // TODO: Complex rendering logic
            // - Matrix setup
            // - Vector calculations
            // - Blending setup
            // - Quad rendering loop
        // }
    }
}

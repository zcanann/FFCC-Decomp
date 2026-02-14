#include "ffcc/pppKeShpTail3X.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/pppShape.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>

extern "C" int rand(void);
extern int DAT_8032ed70;

struct KeShpTail3XStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    s32 m_arg3;
    u8* m_payload;
};

struct KeShpTail3XOffsets {
    u8 _pad0[0xc];
    s32* m_serializedDataOffsets;
};

extern "C" {
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
void pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*);
void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*, pppFMATRIX*);
}
extern Mtx ppvWorldMatrix;
extern _pppEnvSt* pppEnvStPtr;

/*
 * --INFO--
 * PAL Address: 0x80089da0
 * PAL Size: 1516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3X(struct pppKeShpTail3X* obj, struct UnkB* param_2, struct UnkC* param_3)
{
    KeShpTail3XStep* step;
    s16* work;
    Vec pos;

    if (DAT_8032ed70 != 0) {
        return;
    }

    step = (KeShpTail3XStep*)param_2;
    work = (s16*)((u8*)&obj->pppPObject + 8 + ((KeShpTail3XOffsets*)param_3)->m_serializedDataOffsets[0]);

    if ((obj->pppPObject.m_graphId == 0) && (obj->field_0x7d != 0)) {
        ((u8*)work)[0x1c3] = 1;

        pos.x = obj->pppPObject.m_localMatrix.value[0][3];
        pos.y = obj->pppPObject.m_localMatrix.value[1][3];
        pos.z = obj->pppPObject.m_localMatrix.value[2][3];

        if (step->m_payload[0x3f] == 1) {
            pppFMATRIX ownerMatrix;
            pppFMATRIX partMatrix;
            pppFMATRIX outMatrix;

            partMatrix = obj->pppPObject.m_localMatrix;
            ownerMatrix = pppMngStPtr->m_matrix;
            pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&outMatrix, &ownerMatrix, &partMatrix);
            pos.x = outMatrix.value[0][3];
            pos.y = outMatrix.value[1][3];
            pos.z = outMatrix.value[2][3];
        }

        Vec* history = (Vec*)(work + 0x18);
        for (s32 i = 0; i < 0x1c; i++) {
            pppCopyVector__FR3Vec3Vec(history, &pos);
            history++;
        }
    }

    if (((u8*)work)[0x1c2] == 0) {
        ((u8*)work)[0x1c2] = 0x1c;
    }
    ((u8*)work)[0x1c2]--;

    pos.x = obj->pppPObject.m_localMatrix.value[0][3];
    pos.y = obj->pppPObject.m_localMatrix.value[1][3];
    pos.z = obj->pppPObject.m_localMatrix.value[2][3];

    if (step->m_payload[0x3f] == 1) {
        pppFMATRIX ownerMatrix;
        pppFMATRIX partMatrix;
        pppFMATRIX outMatrix;

        partMatrix = obj->pppPObject.m_localMatrix;
        ownerMatrix = pppMngStPtr->m_matrix;
        pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&outMatrix, &ownerMatrix, &partMatrix);
        pos.x = outMatrix.value[0][3];
        pos.y = outMatrix.value[1][3];
        pos.z = outMatrix.value[2][3];
    }

    pppCopyVector__FR3Vec3Vec((Vec*)(work + ((u32)((u8*)work)[0x1c2] * 6) + 0x18), &pos);

    work[8] += work[0xc];
    work[0] += work[8];
    work[9] += work[0xd];
    work[1] += work[9];
    work[10] += work[0xe];
    work[2] += work[10];
    work[0xb] += work[0xf];
    work[3] += work[0xb];
    work[0x10] += work[0x14];
    work[4] += work[0x10];
    work[0x11] += work[0x15];
    work[5] += work[0x11];
    work[0x12] += work[0x16];
    work[6] += work[0x12];
    work[0x13] += work[0x17];
    work[7] += work[0x13];

    if (obj->pppPObject.m_graphId == step->m_graphId) {
        work[0] += *(s16*)(step->m_payload + 0xc);
        work[1] += *(s16*)(step->m_payload + 0xe);
        work[2] += *(s16*)(step->m_payload + 0x10);
        work[3] += *(s16*)(step->m_payload + 0x12);
        work[8] += *(s16*)(step->m_payload + 0x1c);
        work[9] += *(s16*)(step->m_payload + 0x1e);
        work[10] += *(s16*)(step->m_payload + 0x20);
        work[0xb] += *(s16*)(step->m_payload + 0x22);
        work[0xc] += *(s16*)(step->m_payload + 0x24);
        work[0xd] += *(s16*)(step->m_payload + 0x26);
        work[0xe] += *(s16*)(step->m_payload + 0x28);
        work[0xf] += *(s16*)(step->m_payload + 0x2a);
        work[4] += *(s16*)(step->m_payload + 0x14);
        work[5] += *(s16*)(step->m_payload + 0x16);
        work[6] += *(s16*)(step->m_payload + 0x18);
        work[7] += *(s16*)(step->m_payload + 0x1a);
        work[0x10] += *(s16*)(step->m_payload + 0x2c);
        work[0x11] += *(s16*)(step->m_payload + 0x2e);
        work[0x12] += *(s16*)(step->m_payload + 0x30);
        work[0x13] += *(s16*)(step->m_payload + 0x32);
        work[0x14] += *(s16*)(step->m_payload + 0x34);
        work[0x15] += *(s16*)(step->m_payload + 0x36);
        work[0x16] += *(s16*)(step->m_payload + 0x38);
        work[0x17] += *(s16*)(step->m_payload + 0x3a);
    }

    *(u32*)(work + 0xdc) += (u32)step->m_initWOrk;
}

/*
 * --INFO--
 * PAL Address: 0x80089360
 * PAL Size: 2624b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3XDraw(struct pppKeShpTail3X* obj, struct UnkB* param_2, struct UnkC* param_3)
{
    KeShpTail3XStep* step;
    s16* work;
    long* shape;
    u8 count;
    u8 blendMode;
    pppFMATRIX local;
    pppFMATRIX world;
    pppFMATRIX out;
    u8 headIndex;
    s32 i;

    step = (KeShpTail3XStep*)param_2;
    if (step->m_dataValIndex == -1) {
        return;
    }

    work = (s16*)((u8*)&obj->pppPObject + 8 + ((KeShpTail3XOffsets*)param_3)->m_serializedDataOffsets[0]);
    shape = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + step->m_dataValIndex * 4);
    if (shape == NULL) {
        return;
    }

    count = step->m_payload[8];
    if (count == 0) {
        return;
    }

    blendMode = step->m_payload[10];
    pppSetBlendMode(blendMode);
    pppSetDrawEnv((pppCVECTOR*)((u8*)obj + 0x88 + ((KeShpTail3XOffsets*)param_3)->m_serializedDataOffsets[1]),
                  (pppFMATRIX*)0, 1.0f, step->m_payload[0xc], step->m_payload[0xb], blendMode, (u8)0, (u8)1, (u8)1,
                  (u8)0);

    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(&local, &obj->pppPObject.m_localMatrix);
    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(&world, (pppFMATRIX*)&ppvWorldMatrix);

    headIndex = ((u8*)work)[0x1c2];
    for (i = 0; i < count; i++) {
        u8 index = headIndex + i;
        s16 shapeFrame = 0;
        Vec* pos;

        if (index >= 0x1c) {
            index -= 0x1c;
        }

        pos = (Vec*)(work + (index * 6) + 0x18);
        if (step->m_payload[0x3f] == 1) {
            pppUnitMatrix__FR10pppFMATRIX(&out);
            out.value[0][3] = pos->x;
            out.value[1][3] = pos->y;
            out.value[2][3] = pos->z;
            pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&out, &world, &out);
        } else {
            out = local;
            out.value[0][3] = pos->x;
            out.value[1][3] = pos->y;
            out.value[2][3] = pos->z;
        }

        GXLoadPosMtxImm(out.value, 0);
        pppDrawShp(shape, shapeFrame, pppEnvStPtr->m_materialSetPtr, blendMode);
    }

    pppSetBlendMode(3);
}

/*
 * --INFO--
 * PAL Address: 0x80089230
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3XCon(struct pppKeShpTail3X* obj, struct UnkC* param_2)
{
    unsigned char* anglePtr;
    unsigned char* work;
    int i;
    float one;

    work = (unsigned char*)((u8*)&obj->pppPObject + 8 + ((KeShpTail3XOffsets*)param_2)->m_serializedDataOffsets[0]);
    work[0x1c3] = 0;
    work[0x1c2] = 0;
    *(u16*)(work + 0x1bc) = 0;
    *(u32*)(work + 0x1b8) = 0;
    *(u16*)(work + 0x1c0) = (u16)rand();
    memset(work, 0, 8);
    memset(work + 8, 0, 8);
    memset(work + 0x10, 0, 8);
    memset(work + 0x18, 0, 8);
    memset(work + 0x20, 0, 8);
    memset(work + 0x28, 0, 8);

    one = 1.0f;
    i = 0;
    anglePtr = work;
    do {
        s32 rnd = rand();
        *(s16*)(anglePtr + 0x180) = (s16)(rnd - (rnd / 0x168) * 0x168);
        anglePtr += 2;
        *(float*)(work + 0x38) = one;
        *(float*)(work + 0x34) = one;
        *(float*)(work + 0x30) = one;
        work += 0xc;
        i++;
    } while (i < 0x1c);
}

/*
 * --INFO--
 * PAL Address: 0x8008922c
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3XDes(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void S4ToF32(pppFVECTOR4*, short*)
{
	// TODO
}

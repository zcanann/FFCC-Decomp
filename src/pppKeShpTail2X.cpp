#include "ffcc/pppKeShpTail2X.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include <dolphin/types.h>
#include <string.h>

extern int lbl_8032ED70;
extern _pppMngSt* pppMngStPtr;
extern _pppEnvSt* lbl_8032ED54;
extern _pppEnvSt* pppEnvStPtr;

extern "C" {
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*, pppFMATRIX*);
}

struct KeShpTail2XStep {
    u8 _pad0[4];
    s32 m_dataValIndex;
    s32 m_frameStep;
    u8 _padC[0x1A];
    u8 m_worldSpaceMode;
};

struct KeShpTail2XOffsets {
    u8 _pad0[0xc];
    s32* m_serializedDataOffsets;
};

struct KeShpTail2XWork {
    u8 m_count;
    u8 m_head;
    u16 m_frameAcc;
    u16 m_shapeFrame;
    u16 m_shapePrevFrame;
    Vec m_posHistory[31];
};

/*
 * --INFO--
 * PAL Address: 0x80088e4c
 * PAL Size: 992b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2X(_pppPObject* obj, UnkB* param_2, UnkC* param_3)
{
    KeShpTail2XStep* step;
    KeShpTail2XWork* work;
    Vec pos;

    if (lbl_8032ED70 != 0) {
        return;
    }

    step = (KeShpTail2XStep*)param_2;
    work = (KeShpTail2XWork*)((u8*)obj + 0x80 + ((KeShpTail2XOffsets*)param_3)->m_serializedDataOffsets[0]);

    if (obj->m_graphId == 0) {
        if (step->m_worldSpaceMode == 0) {
            pos.x = obj->m_localMatrix.value[0][3];
            pos.y = obj->m_localMatrix.value[1][3];
            pos.z = obj->m_localMatrix.value[2][3];
        } else if (step->m_worldSpaceMode == 1) {
            pppFMATRIX ownerMatrix;
            pppFMATRIX partMatrix;
            pppFMATRIX outMatrix;

            partMatrix = obj->m_localMatrix;
            ownerMatrix = pppMngStPtr->m_matrix;
            pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&outMatrix, &ownerMatrix, &partMatrix);
            pos.x = outMatrix.value[0][3];
            pos.y = outMatrix.value[1][3];
            pos.z = outMatrix.value[2][3];
        }

        u8 count = work->m_count;
        Vec* history = work->m_posHistory;
        if (count != 0) {
            do {
                pppCopyVector__FR3Vec3Vec(history, &pos);
                history++;
                count--;
            } while (count != 0);
        }
    }

    if (work->m_head == 0) {
        work->m_head = work->m_count;
    }
    work->m_head--;

    if (step->m_worldSpaceMode == 0) {
        pos.x = obj->m_localMatrix.value[0][3];
        pos.y = obj->m_localMatrix.value[1][3];
        pos.z = obj->m_localMatrix.value[2][3];
    } else if (step->m_worldSpaceMode == 1) {
        pppFMATRIX ownerMatrix;
        pppFMATRIX partMatrix;
        pppFMATRIX outMatrix;

        partMatrix = obj->m_localMatrix;
        ownerMatrix = pppMngStPtr->m_matrix;
        pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&outMatrix, &ownerMatrix, &partMatrix);
        pos.x = outMatrix.value[0][3];
        pos.y = outMatrix.value[1][3];
        pos.z = outMatrix.value[2][3];
    }

    pppCopyVector__FR3Vec3Vec((Vec*)((u8*)work + (u32)work->m_head * 0xc + 8), &pos);

    {
        long* shape = *(long**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + step->m_dataValIndex * 4);
        u8* frameEntry;
        s16 frameDuration;

        work->m_shapePrevFrame = work->m_shapeFrame;
        frameEntry = (u8*)shape + ((u32)work->m_shapeFrame << 3) + 0x10;

        work->m_frameAcc += step->m_frameStep;
        frameDuration = *(s16*)(frameEntry + 2);
        if (work->m_frameAcc >= frameDuration) {
            work->m_frameAcc -= frameDuration;
            work->m_shapeFrame++;
            if (work->m_shapeFrame >= (u16)*(s16*)((u8*)shape + 6)) {
                if ((frameEntry[4] & 0x80) != 0) {
                    work->m_shapeFrame = 0;
                    work->m_frameAcc = 0;
                } else {
                    work->m_frameAcc = 0;
                    work->m_shapeFrame--;
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80088748
 * PAL Size: 1796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XDraw(_pppPObject*, UnkB*, UnkC*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800886f0
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XCon(void* obj, void* param_2)
{
	u32 serializedOffset = **(u32**)((u8*)param_2 + 0xc);
	u8* tail = (u8*)obj + serializedOffset + 0x80;

	*(u16*)(tail + 2) = 0;
	*(u16*)(tail + 4) = 0;
	*(u16*)(tail + 6) = 0;
	tail[1] = 0;
	tail[0] = 0x1f;
	memset(tail + 8, 0, 0x174);
}

/*
 * --INFO--
 * PAL Address: 0x80088698
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XDes(void* obj, void* param_2)
{
	u32 serializedOffset = **(u32**)((u8*)param_2 + 0xc);
	u8* tail = (u8*)obj + serializedOffset + 0x80;

	*(u16*)(tail + 2) = 0;
	*(u16*)(tail + 4) = 0;
	*(u16*)(tail + 6) = 0;
	tail[1] = 0;
	tail[0] = 0x1f;
	memset(tail + 8, 0, 0x174);
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void U8ToF32(pppFVECTOR4*, unsigned char*)
{
	// TODO
}

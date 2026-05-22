#include "ffcc/pppDrawMdl.h"
#include "ffcc/pppPart.h"
#include "dolphin/types.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawMdl0(_pppPObject*, PDrawMdl*, _pppCtrlTable*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80065384
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMdl(_pppPObject* pObject, PDrawMdl* drawMdl, _pppCtrlTable* ctrlTable)
{
    _pppPObject* obj = pObject;
    PDrawMdl* mdl = drawMdl;

    if ((s32)*(u32*)((u8*)mdl + 4) == 0xFFFF) {
        return;
    }

    pppSetDrawEnv(
        reinterpret_cast<pppCVECTOR*>((u8*)obj + *(int*)*(int**)((u8*)ctrlTable + 0xC) + 0x88),
        reinterpret_cast<pppFMATRIX*>((u8*)obj + 0x40),
        *(float*)((u8*)mdl + 0x10),
        *(u8*)((u8*)mdl + 0x14),
        *(u8*)((u8*)mdl + 0xA),
        *(u8*)((u8*)mdl + 0x9),
        *(u8*)((u8*)mdl + 0xB),
        *(u8*)((u8*)mdl + 0xC),
        *(u8*)((u8*)mdl + 0xD),
        *(u8*)((u8*)mdl + 0xE));

    pppSetBlendMode(*(u8*)((u8*)mdl + 0x9));

    pppDrawMesh((pppModelSt*)pppEnvStPtr->m_mapMeshPtr[*(u32*)((u8*)mdl + 0x4)], obj->m_drawMatrixPtr, 1);
}

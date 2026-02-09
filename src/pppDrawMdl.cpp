#include "ffcc/pppDrawMdl.h"
#include "ffcc/pppPart.h"
#include "dolphin/types.h"

extern "C" {
extern void* lbl_8032ED54;
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void pppSetBlendMode__FUc(unsigned char);
void pppDrawMesh__FP10pppModelStP3Veci(void*, void*, int);
}

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

    if ((*(u32*)((u8*)mdl + 4) >> 16) == 0xFFFF) {
        return;
    }

    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (u8*)obj + *(int*)*(int**)((u8*)ctrlTable + 0xC) + 0x88,
        (u8*)obj + 0x40,
        *(float*)((u8*)mdl + 0x10),
        *(u8*)((u8*)mdl + 0x14),
        *(u8*)((u8*)mdl + 0xA),
        *(u8*)((u8*)mdl + 0x9),
        *(u8*)((u8*)mdl + 0xB),
        *(u8*)((u8*)mdl + 0xC),
        *(u8*)((u8*)mdl + 0xD),
        *(u8*)((u8*)mdl + 0xE));

    pppSetBlendMode__FUc(*(u8*)((u8*)mdl + 0x9));

    void** modelsArray = *(void***)((u8*)lbl_8032ED54 + 0x8);
    pppDrawMesh__FP10pppModelStP3Veci(modelsArray[*(u32*)((u8*)mdl + 0x4)], *(void**)((u8*)obj + 0x70), 1);
}

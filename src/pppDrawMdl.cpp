#include "ffcc/pppDrawMdl.h"
#include "ffcc/pppPart.h"

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
    unsigned int value = *(unsigned int*)((char*)mdl + 0x4);
    if ((value >> 16) == 0xFFFF) {
        return;
    }

    typedef void (*SetDrawEnvFn)(pppFMATRIX*, pppCVECTOR*, float, unsigned char, unsigned char,
                                 unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
    SetDrawEnvFn setDrawEnv = (SetDrawEnvFn)pppSetDrawEnv;
    setDrawEnv((pppFMATRIX*)((char*)obj + *(int*)*(int**)((char*)ctrlTable + 0xC) + 0x88),
               (pppCVECTOR*)((char*)obj + 0x40),
               *(float*)((char*)mdl + 0x10),
               *(unsigned char*)((char*)mdl + 0x14),
               *(unsigned char*)((char*)mdl + 0xA),
               *(unsigned char*)((char*)mdl + 0x9),
               *(unsigned char*)((char*)mdl + 0xB),
               *(unsigned char*)((char*)mdl + 0xC),
               *(unsigned char*)((char*)mdl + 0xD),
               *(unsigned char*)((char*)mdl + 0xE));

    pppSetBlendMode(*(unsigned char*)((char*)mdl + 0x9));

    extern void* lbl_8032ED54;
    void** modelsArray = (void**)*(void**)((char*)&lbl_8032ED54 + 0x8);
    pppDrawMesh((pppModelSt*)modelsArray[*(unsigned int*)((char*)mdl + 0x4)],
                *(Vec**)((char*)obj + 0x70), 1);
}

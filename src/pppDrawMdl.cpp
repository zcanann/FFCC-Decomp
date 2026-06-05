#include "ffcc/pppDrawMdl.h"
#include "global.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_linkage.h"
#include "dolphin/types.h"
#include <stddef.h>

STATIC_ASSERT(offsetof(PDrawMdl, m_modelIndex) == 0x04);
STATIC_ASSERT(offsetof(PDrawMdl, m_blendMode) == 0x09);
STATIC_ASSERT(offsetof(PDrawMdl, m_texScale) == 0x10);
STATIC_ASSERT(offsetof(PDrawMdl, m_drawA) == 0x14);

static inline pppCVECTOR* PppDrawMdlColor(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<pppCVECTOR*>(obj->m_workArea + ctrl->m_serializedDataOffsets[0] + 8);
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

    if ((s32)mdl->m_modelIndex == 0xFFFF) {
        return;
    }

    pppSetDrawEnv(
        PppDrawMdlColor(obj, ctrlTable),
        &obj->m_drawMatrix,
        mdl->m_texScale,
        mdl->m_drawA,
        mdl->m_drawB,
        mdl->m_blendMode,
        mdl->m_drawD,
        mdl->m_drawE,
        mdl->m_drawF,
        mdl->m_drawG);

    pppSetBlendMode(mdl->m_blendMode);

    pppDrawMesh((pppModelSt*)ppvEnv->m_mapMeshPtr[mdl->m_modelIndex], obj->m_drawMatrixPtr, 1);
}

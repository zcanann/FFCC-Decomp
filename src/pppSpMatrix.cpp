#include "ffcc/pppSpMatrix.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800d3818
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSpMatrix(_pppPObject* mtx, void* src, _pppCtrlTable* data)
{
    int offset = *data->m_serializedDataOffsets;
    Mtx* mtxSrc = (Mtx*)(mtx->m_workArea + offset);
    Mtx* mtxOut = &mtx->m_localMatrix.value;

    (void)src;
    PSMTXConcat(*mtxSrc, *mtxOut, *mtxOut);
}

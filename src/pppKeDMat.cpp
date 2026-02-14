#include "ffcc/pppKeDMat.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"

/*
 * --INFO--
 * PAL Address: 0x80095854
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeDMatDraw(_pppPObject* pObject, void*, _pppCtrlTable* ctrlTable)
{
    unsigned int targetOffset = *(unsigned int*)(*(char**)((char*)ctrlTable + 0xC) + 4) + 0x80;
    pppFMATRIX* targetMatrix = (pppFMATRIX*)((char*)pObject + targetOffset);
    pppFMATRIX* resultMatrix = (pppFMATRIX*)((char*)pObject + 0x40);

    pppMulMatrix(*resultMatrix, *(pppFMATRIX*)&ppvWorldMatrix, *(pppFMATRIX*)((char*)pObject + 0x10));
    pppCopyMatrix(*targetMatrix, *resultMatrix);
}

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
    int targetOffset = *(int*)(*(char**)((char*)ctrlTable + 0xC) + 4);
    char* object = (char*)pObject;
    pppFMATRIX* resultMatrix = (pppFMATRIX*)(object + 0x40);
    pppFMATRIX* targetMatrix = (pppFMATRIX*)(object + targetOffset + 0x80);

    pppMulMatrix(*resultMatrix, *(pppFMATRIX*)&ppvWorldMatrix, *(pppFMATRIX*)(object + 0x10));
    pppCopyMatrix(*targetMatrix, *resultMatrix);
}

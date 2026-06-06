#ifndef _PPP_VTMIME_H_
#define _PPP_VTMIME_H_

#include "ffcc/partMng.h"

struct VtMimeData
{
    int id;
    int sourceA;
    int sourceB;
    float addX;
    float addY;
    float addZ;
};

struct VtMimeDataOffsets {
    s32 m_stateOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppVtMime(_pppPObject* object, VtMimeData* step, _pppCtrlTable* ctrl);
void pppDrawVtMime(_pppPObject* object, VtMimeData* step, _pppCtrlTable* ctrl);
void pppVtMimeCon(_pppPObjLink* object, _pppCtrlTable* ctrl);
void pppVtMimeCon2(_pppPObjLink* object, _pppCtrlTable* ctrl);
void pppVtMimeDes(_pppPObjLink* object, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_VTMIME_H_

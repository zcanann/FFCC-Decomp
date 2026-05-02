#ifndef _PPP_POBJPOINT_H_
#define _PPP_POBJPOINT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct pppPObjPointStep {
    s32 m_graphId;              // 0x0
    s32 m_createProgramIndex;   // 0x4
    u8* m_sourceObject;         // 0x8
    u32 m_objectId;             // 0xc
};

struct pppPObjPointWork {
    float m_x;         // 0x0
    float m_y;         // 0x4
    float m_z;         // 0x8
    u8 m_pad[4];       // 0xc
    u8* m_source;      // 0x10
};

#ifdef __cplusplus
extern "C" {
#endif

void pppPObjPoint(_pppPObject* pObject, pppPObjPointStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POBJPOINT_H_

#ifndef _FFCC_PPPCALLBACKDISTANCE_H_
#define _FFCC_PPPCALLBACKDISTANCE_H_

#include <dolphin/types.h>

struct _pppPObject;

struct pppCallBackDistanceUnkB {
    u32 m_unk0;
    f32 m_dataValIndex;
    s16 m_initWOrk;
};

struct pppCallBackDistanceUnkC {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCallBackDistance(_pppPObject* object, pppCallBackDistanceUnkC* ctrlTable);
void pppDestructCallBackDistance(_pppPObject* object, pppCallBackDistanceUnkC* ctrlTable);
void pppFrameCallBackDistance(_pppPObject* object, pppCallBackDistanceUnkB* step, pppCallBackDistanceUnkC* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCALLBACKDISTANCE_H_

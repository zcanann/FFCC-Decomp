#ifndef _FFCC_PPPCALLBACKDISTANCE_H_
#define _FFCC_PPPCALLBACKDISTANCE_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct CallBackDistanceDataOffsets {
    s32 m_distanceOffset;
};

struct pppCallBackDistanceStep {
    u32 m_unk0;
    f32 m_dataValIndex;
    s16 m_initWOrk;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCallBackDistance(_pppPObject* object, _pppCtrlTable* ctrlTable);
void pppDestructCallBackDistance(_pppPObject* object, _pppCtrlTable* ctrlTable);
void pppFrameCallBackDistance(_pppPObject* object, pppCallBackDistanceStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCALLBACKDISTANCE_H_

#ifndef _PPP_ERASECHARAPARTS_H_
#define _PPP_ERASECHARAPARTS_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppEraseCharaParts;

struct EraseCharaPartsDataOffsets {
    s32 m_sourceColorOffset;
    s32 m_callbackColorOffset;
};

struct pppEraseCharaPartsStep {
    u8 m_pad0[4];
    s8 m_meshIndex;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructEraseCharaParts(pppEraseCharaParts*, _pppCtrlTable*);
void pppDestructEraseCharaParts(pppEraseCharaParts*, _pppCtrlTable*);
void pppFrameEraseCharaParts(pppEraseCharaParts*, pppEraseCharaPartsStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_ERASECHARAPARTS_H_

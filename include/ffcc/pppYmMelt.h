#ifndef _FFCC_PPP_YMMELT_H_
#define _FFCC_PPP_YMMELT_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;
struct YmMeltCtrl;

typedef _pppCtrlTable PYmMeltDataOffsets;
typedef _pppPObject PYmMelt;

struct YmMeltDataOffsets {
    s32 m_workOffset;
    s32 m_colorWorkOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMelt(PYmMelt*, PYmMeltDataOffsets*);
void pppDestructYmMelt(PYmMelt*, PYmMeltDataOffsets*);
void pppFrameYmMelt(PYmMelt*, YmMeltCtrl*, PYmMeltDataOffsets*);
void pppRenderYmMelt(PYmMelt*, YmMeltCtrl*, PYmMeltDataOffsets*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMELT_H_

#ifndef _PPP_YMLOOKON_H_
#define _PPP_YMLOOKON_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct pppYmLookOnStep {
    s32 m_graphId;
    f32 m_dataValIndex;
};

typedef _pppPObject pppYmLookOn;

struct YmLookOnDataOffsets {
    s32 m_workOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmLookOn(pppYmLookOn* pppYmLookOn, struct _pppCtrlTable* param_2);
void pppFrameYmLookOn(pppYmLookOn* pppYmLookOn, struct pppYmLookOnStep* param_2, struct _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMLOOKON_H_

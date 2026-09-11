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

void pppConstructYmLookOn(pppYmLookOn* lookOn, struct _pppCtrlTable* ctrl);
void pppFrameYmLookOn(pppYmLookOn* lookOn, struct pppYmLookOnStep* step, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMLOOKON_H_

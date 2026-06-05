#ifndef _FFCC_PPPCHANGETEX_H_
#define _FFCC_PPPCHANGETEX_H_

#include "ffcc/pppChangeTexCommon.h"

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppChangeTex;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppConstruct2ChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppDestructChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppFrameChangeTex(pppChangeTex*, ChangeTexStep*, _pppCtrlTable*);
void pppRenderChangeTex(pppChangeTex*, ChangeTexStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHANGETEX_H_

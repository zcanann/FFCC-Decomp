#ifndef _PPP_YMCHANGETEX_H_
#define _PPP_YMCHANGETEX_H_

#include "ffcc/pppChangeTexCommon.h"

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppYmChangeTex;
typedef ChangeTexStep pppYmChangeTexStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmChangeTex(pppYmChangeTex*, _pppCtrlTable*);
void pppDestructYmChangeTex(pppYmChangeTex*, _pppCtrlTable*);
void pppFrameYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep*, _pppCtrlTable*);
void pppRenderYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMCHANGETEX_H_

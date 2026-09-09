#ifndef _PPP_YMCHECKBGHEIGHT_H_
#define _PPP_YMCHECKBGHEIGHT_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppYmCheckBGHeight;

struct pppYmCheckBGHeightStep
{
    s32 m_graphId;
    float m_probeStartOffset;
    float m_hitHeightOffset;
    float m_fallLimit;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmCheckBGHeight(pppYmCheckBGHeight* param1, _pppCtrlTable* param2);
void pppFrameYmCheckBGHeight(pppYmCheckBGHeight* param1, pppYmCheckBGHeightStep* param2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMCHECKBGHEIGHT_H_

#ifndef _FFCC_PPPCOLOR_H_
#define _FFCC_PPPCOLOR_H_

#include <dolphin/types.h>

#include "ffcc/ppp_linkage.h"
#include "ffcc/pppTypes.h"

struct _pppPObject;
struct _pppCtrlTable;

struct PppColorDataOffsets {
    s32 m_workOffset;
};

struct VColor
{
    s16 m_red;          // 0x0
    s16 m_green;        // 0x2
    s16 m_blue;         // 0x4
    s16 m_alpha;        // 0x6
    pppCVECTOR m_color; // 0x8
}; // Size 0xC

struct pppColorStep {
    s32 m_graphId;
    s32 m_padding;
    s16 m_colors[4];
};

struct _pppMngSt;
extern _pppMngSt* ppvMng;

#ifdef __cplusplus
extern "C" {
#endif

void pppColor(struct _pppPObject* param1, pppColorStep* param2, struct _pppCtrlTable* param3);
void pppColorCon(struct _pppPObject* param1, struct _pppCtrlTable* param2);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCOLOR_H_

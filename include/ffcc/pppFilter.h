#ifndef _PPP_FILTER_H_
#define _PPP_FILTER_H_

#include <dolphin/gx/GXStruct.h>

struct pppFilter {
    char padding[0x88];
    _GXColor m_color;
    char padding2[4];
};

struct pppFilterUnkB {
    unsigned int m_unk0;
    unsigned int m_dataValIndex;
};

struct pppFilterUnkC {
    char padding[0x0c];
    int* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructFilter(void);
void pppDestructFilter(void);
void pppFrameFilter(void);
void pppRenderFilter(pppFilter* pppFilter, pppFilterUnkB* param_2, pppFilterUnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_FILTER_H_


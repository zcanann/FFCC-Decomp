#ifndef _PPP_FILTER_H_
#define _PPP_FILTER_H_

struct pppFilter {
    char padding[0x90];
};

struct UnkB {
    unsigned int m_unk0;
    unsigned int m_dataValIndex;
};

struct UnkC {
    char padding[0x0c];
    int* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructFilter(void);
void pppDestructFilter(void);
void pppFrameFilter(void);
void pppRenderFilter(pppFilter* pppFilter, UnkB* param_2, UnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_FILTER_H_

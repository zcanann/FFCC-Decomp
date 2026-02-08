#ifndef _FFCC_PPPALIGNMENTSCALE_H_
#define _FFCC_PPPALIGNMENTSCALE_H_

struct pppAlignmentScale;

struct pppAlignmentScaleData
{
    float m_unk0x0;
    float m_unk0x4;
    float m_unk0x8;
};

#ifdef __cplusplus
extern "C" {
#endif
void pppConstructAlignmentScale(void);
struct pppAlignmentScale* pppFrameAlignmentScale(struct pppAlignmentScale*, struct pppAlignmentScaleData*);

#ifdef __cplusplus
}
#endif

#endif

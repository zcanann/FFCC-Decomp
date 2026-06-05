#ifndef _FFCC_PPPALIGNMENTSCALE_H_
#define _FFCC_PPPALIGNMENTSCALE_H_

struct pppAlignmentScale;
struct pppAlignmentScaleData;

#ifdef __cplusplus
extern "C" {
#endif
void pppConstructAlignmentScale(struct pppAlignmentScale*, struct pppAlignmentScaleData*);
void pppFrameAlignmentScale(struct pppAlignmentScale*, struct pppAlignmentScaleData*);

#ifdef __cplusplus
}
#endif

#endif

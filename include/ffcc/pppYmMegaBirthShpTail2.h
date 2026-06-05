#ifndef _PPP_YMMEGABIRTHSHPTAIL2_H_
#define _PPP_YMMEGABIRTHSHPTAIL2_H_

#include "ffcc/partMng.h"

struct _pppPObject;
struct pppYmMegaBirthShpTail2RenderStep;

typedef _pppPObject pppYmMegaBirthShpTail2;

struct PYmMegaBirthShpTail2
{
    Mtx m_matrix;
    Vec m_directionTail;
    float m_colorDeltaAdd[4];
    float m_sizeStart;
    float m_sizeVal;
    float m_speedRandRange;
    float field_0x58;
    Vec m_speedScale;
    unsigned char m_randType;
    unsigned char m_enableParticleColor;
    unsigned char m_pad0x6a[0x6c - 0x6a];
    short m_tail2PathIndex;
    unsigned char m_pad0x6e[0xb9 - 0x6e];
    unsigned char m_tail2MatrixMode;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, _pppCtrlTable*);
void pppDestructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, _pppCtrlTable*);
void pppFrameYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _pppCtrlTable*);
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, pppYmMegaBirthShpTail2RenderStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMMEGABIRTHSHPTAIL2_H_
